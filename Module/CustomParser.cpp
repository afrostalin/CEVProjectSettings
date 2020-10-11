// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#include "StdAfx.h"
#include "CustomParser.h"

#include <CrySerialization/IArchiveHost.h>
#include <CrySerialization/yasli/JSONOArchive.h>
#include <CrySerialization/yasli/JSONIArchive.h>
#include <CrySerialization/yasli/STL.h>
#include <CrySerialization/StringList.h>

void CCustomParser::FindAndParseCustomSettings()
{
	std::vector<string> files = SHelper::GetAllAssetWithExt(PathUtil::GetProjectFolder(), "settings");

	for (const auto& it : files)
	{
		if (!it.IsEmpty())
		{
			CCryFile file;

			if (file.Open(it.c_str(), "rb", ICryPak::FOPEN_ONDISK))
			{
				std::vector<char> data;
				size_t fileSize = 0;
				
				if (file.GetHandle() != nullptr)
				{
					fileSize = file.GetLength();
					data.resize(fileSize + 1);
					data[fileSize] = 0;
				}
				
				if (file.ReadRaw(data.data(), fileSize) == fileSize)
				{
					SProjectCustomConfig config;
					if (gEnv->pSystem->GetArchiveHost()->LoadJsonBuffer(Serialization::SStruct(config), data.data(), data.size()))
					{
						customConfigs.push_back(config);
					}
				}
			}

			file.Close();
		}
	}

	for (const auto& it : customConfigs)
	{
		for (const auto& config : it.configs)
		{
			CCustomSettingsPage* pPage = new CCustomSettingsPage(config);
			CCEVProjectSettingsPlugin::GetInstance()->GetProjectSettings()->RegisterPage<CCustomSettingsPage>(pPage);
			pages.push_back(pPage);
		}
	}
}

CCustomSettingsPage::CCustomSettingsPage(const SProjectCustomConfig::SConfig& _config) 
	: SProjectSettingsPage(_config.category, _config.path)
	, config(_config)
{
	for (const auto& var : config.variables)
	{
		SConsoleVariable variable;
		variable.name = var.name;

		if (var.type == "Int")
		{
			variable.type = SConsoleVariable::EType::Int;
		}
		else if (var.type == "Float")
		{
			variable.type = SConsoleVariable::EType::Float;
		}
		else if(var.type == "String")
		{
			variable.type = SConsoleVariable::EType::String;
		}
		else if (var.type == "Bool")
		{
			variable.type = SConsoleVariable::EType::Bool;
		}
		else if (var.type == "Enum")
		{
			variable.type = SConsoleVariable::EType::Enum;
		}

		variable.value = var.value.c_str();
		variable.description = var.description;
		variable.bIsRequestRestart = var.requestRestart;

		variables[var.name] = variable;
	}
}

bool CCustomSettingsPage::Serialize(yasli::Archive& ar)
{
	for (auto& it : variables)
	{
		if(it.second.type != SConsoleVariable::EType::Enum)
		{
			ar(it.second, it.second.name, it.second.description);
		}
		else
		{
			auto result = std::find_if(config.variables.begin(), config.variables.end(), [&](const SProjectCustomConfig::SConfig::SVariable& var)
				{
					if (var.name == it.first)
					{
						return true;
					}
					else
					{
						return false;
					}
				});

			if (result != config.variables.end())
			{
				Serialization::StringListStatic stringList;

				for (const auto& varEnum : result->enumDescription)
				{
					stringList.push_back(varEnum.description);
				}		

				Serialization::StringListStaticValue stringListValue(stringList, it.second.value.toInt());

				ar(stringListValue, it.second.name, it.second.description);

				if (ar.isInput())
				{
					it.second.value = stringListValue.index();;
				}
			}
		}
	}

	return true;
}

void CCustomSettingsPage::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	for (auto& it : variables)
	{
		it.second.ParseFromString(helper.GetConsoleVariableValue(it.second.name));
	}
}

void CCustomSettingsPage::SaveToFile(SConsoleVariableHelper& helper)
{
	for (auto& it : variables)
	{
		if (it.second.type != SConsoleVariable::EType::Enum)
		{
			helper.StoreConsoleVariable(it.second.name, it.second.SaveToString(), it.second.bIsRequestRestart);
		}
		else
		{
			auto getEnumKey([&](const string& varName, int value) -> string
				{
					auto result = std::find_if(config.variables.begin(), config.variables.end(), [&](const SProjectCustomConfig::SConfig::SVariable& var)
						{
							if (var.name == it.first)
							{
								return true;
							}
							else
							{
								return false;
							}
						});

					if (result != config.variables.end())
					{
						for (size_t i = 0; i < result->enumDescription.size(); i++)
						{
							if (i == value)
							{
								return result->enumDescription[i].key;
							}
						}
					}

					return string();
				});

			helper.StoreConsoleVariable(it.second.name, getEnumKey(it.first, it.second.value.toInt()), it.second.bIsRequestRestart);
		}
	}
}

void CCustomSettingsPage::CheckPluginAvailable(const string& pluginName)
{
}
