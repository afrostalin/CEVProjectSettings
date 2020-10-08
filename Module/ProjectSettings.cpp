// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#include "StdAfx.h"
#include "ProjectSettings.h"
#include "QtUtil.h"
#include <IEditor.h>

#include <CryString/CryPath.h>
#include <CrySystem/IProjectManager.h>
#include <CrySystem/File/CryFile.h>
#include <CrySerialization/IArchiveHost.h>
#include <CrySerialization/yasli/JSONOArchive.h>
#include <CrySerialization/yasli/JSONIArchive.h>
#include <CrySerialization/yasli/STL.h>

#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>

#include <qapplication.h>
#include <qprocess.h>

#include "Pages/Project.h"
#include "Pages/Game.h"


QString SProjectSettingsPage::GetSerializedProperties()
{
	yasli::JSONOArchive ar;
	ar(*this, m_name, m_name);
	return ar.buffer();
}

void SProjectSettingsPage::FromSerializedProperties(const QByteArray& jsonBlob)
{
	yasli::JSONIArchive ar;
	ar.open(jsonBlob, jsonBlob.length());
	ar(*this, m_name, m_name);
}

CProjectSettings::CProjectSettings()
	: m_bIsLoading(false)
{
	signalSettingsChanged.Connect(this, &CProjectSettings::Save);
}

CProjectSettings::~CProjectSettings()
{
	signalSettingsChanged.DisconnectObject(this);
	Save();
	for (auto ite = m_preferences.begin(); ite != m_preferences.end(); ++ite)
	{
		std::vector<SProjectSettingsPage*> m_preferencePages = ite->second;
		for (auto i = 0; i < m_preferencePages.size(); ++i)
			delete m_preferencePages[i];
	}
}

void CProjectSettings::Init()
{
	Load();
}

void CProjectSettings::Load()
{
	const string projectFilePath = GetIEditor()->GetProjectManager()->GetProjectFilePath();

#ifndef CRY_FORCE_CRYPROJECT_IN_PAK
	int flags = ICryPak::FOPEN_ONDISK;
#else
	int flags = 0;
#endif

	CCryFile file;
	file.Open(projectFilePath.c_str(), "rb", flags);

	std::vector<char> projectFileJson;
	size_t fileSize = 0;
	if (file.GetHandle() != nullptr)
	{
		fileSize = file.GetLength();
		projectFileJson.resize(fileSize + 1);
		projectFileJson[fileSize] = 0;
	}

	Cry::SProject project;

	if (fileSize > 0 && file.ReadRaw(projectFileJson.data(), fileSize) == fileSize &&
		gEnv->pSystem->GetArchiveHost()->LoadJsonBuffer(Serialization::SStruct(project), projectFileJson.data(), projectFileJson.size()))
	{
		// We need backup here, because CRYENGINE love crash after some changes =D
		gEnv->pSystem->GetArchiveHost()->SaveJsonFile(string().Format("%s.backup", GetIEditor()->GetProjectManager()->GetProjectFilePath()), Serialization::SStruct(project));

		gProjectSettings.version = project.version;
		gProjectSettings.type = project.type;
		gProjectSettings.name = project.name;
		gProjectSettings.guid = project.guid.ToString();

		gSettings_Game.assetFolder = project.assetDirectory;
		gSettings_Game.codeFolder = project.codeDirectory;

		SConsoleVariableHelper helper;

		for (const auto& var : project.consoleVariables)
		{
			helper.consoleVariables[var.first] = var.second;
		}

		for (const auto& it : m_preferences)
		{
			for (const auto& page : it.second)
			{
				page->ParseConsoleVars(helper);

				for (const auto& it : project.plugins)
				{
					const string pluginName = PathUtil::GetFileName(it.path);
					page->CheckPluginAvailable(pluginName);
				}
			}
		}
	}
}

void CProjectSettings::Save()
{
	if (m_bIsLoading)
		return;

	const string projectFilePath = GetIEditor()->GetProjectManager()->GetProjectFilePath();

#ifndef CRY_FORCE_CRYPROJECT_IN_PAK
	int flags = ICryPak::FOPEN_ONDISK;
#else
	int flags = 0;
#endif

	CCryFile file;
	file.Open(projectFilePath.c_str(), "rb", flags);

	std::vector<char> projectFileJson;
	size_t fileSize = 0;
	if (file.GetHandle() != nullptr)
	{
		fileSize = file.GetLength();
		projectFileJson.resize(fileSize + 1);
		projectFileJson[fileSize] = 0;
	}

	Cry::SProject project;

	if (fileSize > 0 && file.ReadRaw(projectFileJson.data(), fileSize) == fileSize &&
		gEnv->pSystem->GetArchiveHost()->LoadJsonBuffer(Serialization::SStruct(project), projectFileJson.data(), projectFileJson.size()))
	{
		project.version = gProjectSettings.version;
		project.type = gProjectSettings.type;
		project.name = gProjectSettings.name;
		project.guid = CryGUID::FromString(gProjectSettings.guid);
		project.assetDirectory = gSettings_Game.assetFolder;
		project.codeDirectory = gSettings_Game.codeFolder;

		SConsoleVariableHelper helper;

		for (const auto& var : project.consoleVariables)
		{
			helper.consoleVariables[var.first] = var.second;
		}

		for (const auto& it : m_preferences)
		{
			for (const auto& page : it.second)
			{
				page->SaveToFile(helper);
			}
		}

		project.consoleVariables.clear();

		bool bShowRestartDialog = false;

		for (const auto& var : helper.consoleVariables)
		{
			if (var.second.bIsChanged)
			{
				gEnv->pConsole->ExecuteString(string().Format("%s %s", var.first.c_str(), var.second.value.c_str()));
			}

			if (var.second.bIsChanged && var.second.bIsRequestRestart)
			{
				bShowRestartDialog = true;
			}

			project.consoleVariables[var.first] = var.second.value;
		}

		gEnv->pSystem->GetArchiveHost()->SaveJsonFile(GetIEditor()->GetProjectManager()->GetProjectFilePath(), Serialization::SStruct(project));

		if (bShowRestartDialog)
		{
			if (CQuestionDialog::SQuestion("Restart sandbox?", "Some changes need restart sandbox for apply. Do you need do it now?") == QDialogButtonBox::Yes)
			{
				char szExecFilePath[_MAX_PATH] = "";
				CryGetExecutableFolder(CRY_ARRAY_COUNT(szExecFilePath), szExecFilePath);
				
				const string pathToSandbox = string().Format("%s\\Sandbox.exe", szExecFilePath);

				QStringList args;
				args << "-project" << GetIEditor()->GetProjectManager()->GetProjectFilePath();

				qApp->quit();
				QProcess::startDetached(qApp->arguments()[0], args);
			}
		}
	}
}

void CProjectSettings::Reset(const char* path)
{
	if (m_bIsLoading)
		return;

	auto ite = m_preferences.find(path);
	if (ite == m_preferences.end())
		return;

	std::vector<SProjectSettingsPage*> pages = ite->second;
	for (SProjectSettingsPage* pPage : pages)
		pPage->signalRequestReset();

	Save();
	signalSettingsReset();
}

void CProjectSettings::AddPage(SProjectSettingsPage* pPreferencePage)
{
	std::vector<SProjectSettingsPage*>& preferencePages = m_preferences[pPreferencePage->GetPath()];
	preferencePages.push_back(pPreferencePage);
	std::sort(preferencePages.begin(), preferencePages.end(), [](const SProjectSettingsPage* pFirst, const SProjectSettingsPage* pSecond)
		{
			static const char* szGeneral = "General";

			if (!pFirst->GetName().find(szGeneral))
				return true;
			if (!pSecond->GetName().find(szGeneral))
				return false;

			return pFirst->GetName() < pSecond->GetName();
		});

}

std::vector<SProjectSettingsPage*> CProjectSettings::GetPages(const char* path)
{
	auto ite = m_preferences.find(path);
	if (ite == m_preferences.end())
		return std::vector<SProjectSettingsPage*>();

	return ite->second;
}

bool CProjectSettings::Serialize(yasli::Archive& ar)
{
	for (auto ite = m_preferences.begin(); ite != m_preferences.end(); ++ite)
	{
		std::vector<SProjectSettingsPage*> preferencePages = ite->second;

		for (SProjectSettingsPage* pPreferencePage : preferencePages)
		{
			ar(*pPreferencePage, pPreferencePage->GetName(), pPreferencePage->GetName());
		}
	}
	return true;
}

bool Serialize(Serialization::IArchive& ar, SConsoleVariable& var, const char* szName, const char* szLabel)
{
	switch (var.type)
	{
	case SConsoleVariable::EType::String:
	{
		if (ar.isOutput())
		{
			string _value = QtUtil::ToString(var.value.toString());
			ar(_value, szName, szLabel);
		}
		else
		{
			string _value;
			ar(_value, szName, szLabel);
			var.value = _value.c_str();
		}
	}
	break;
	case SConsoleVariable::EType::Int:
	{
		if (ar.isOutput())
		{
			int _value = var.value.toInt();
			ar(_value, szName, szLabel);
		}
		else
		{
			int _value;
			ar(_value, szName, szLabel);
			var.value = _value;
		}
	}
	break;
	case SConsoleVariable::EType::Float:
	{
		if (ar.isOutput())
		{
			float _value = var.value.toFloat();
			ar(_value, szName, szLabel);
		}
		else
		{
			float _value;
			ar(_value, szName, szLabel);
			var.value = _value;
		}
	}
	break;
	case SConsoleVariable::EType::Bool:
	{
		if (ar.isOutput())
		{
			bool _value = var.value.toInt() ? true : false;
			ar(_value, szName, szLabel);
		}
		else
		{
			bool _value;
			ar(_value, szName, szLabel);

			var.value = _value ? 1 : 0;
		}
	}
	break;
	default:
		break;
	}

	return true;
}