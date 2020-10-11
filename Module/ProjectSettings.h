// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once 

#include <AutoRegister.h>
#include <CrySandbox/CrySignal.h>
#include <CrySystem/IConsole.h>

#include "SandboxPlugin.h"
#include "ProjectSettingsDialog.h"


class CProjectSettings;

typedef CAutoRegister<CProjectSettings> CAutoRegisterProjectSettingsHelper;

#define REGISTER_PROJECT_SETTINGS_PAGE(Type)                                                               \
	namespace Internal                                                                                  \
	{                                                                                                   \
	void RegisterProjectSettingsPage ## Type()                                                              \
	{                                                                                                   \
		CCEVProjectSettingsPlugin::GetInstance()->GetProjectSettings()->RegisterPage<Type>();                                             \
	}                                                                                                   \
	CAutoRegisterProjectSettingsHelper g_AutoRegProjectSettingsHelper ## Type(RegisterProjectSettingsPage ## Type); \
	}

#define REGISTER_PROJECT_SETTINGS_PAGE_PTR(Type, TypePtr)                                                  \
	namespace Internal                                                                                  \
	{                                                                                                   \
	void RegisterProjectSettingsPage ## Type()                                                              \
	{                                                                                                   \
		CCEVProjectSettingsPlugin::GetInstance()->GetProjectSettings()->RegisterPage<Type>(TypePtr);                                      \
	}                                                                                                   \
	CAutoRegisterProjectSettingsHelper g_AutoRegProjectSettingsHelper ## Type(RegisterProjectSettingsPage ## Type); \
	}

#define ADD_PROJECT_SETTINGS_PAGE_PROPERTY(type, accessor, mutator) \
public:                                                       \
	void mutator(const type val)                                \
	{                                                           \
		if (m_ ## accessor != val)                                \
		{                                                         \
			m_ ## accessor = val;                                   \
			accessor ## Changed();                                  \
			signalSettingsChanged();                                \
		}                                                         \
	}                                                           \
	const type& accessor() const { return m_ ## accessor; }     \
	CCrySignal<void()> accessor ## Changed;                     \
private:                                                      \
	type m_ ## accessor;                                        \

struct SConsoleVariableHelper
{
	string GetConsoleVariableValue(const string& szCVarName) const
	{
		for (auto it = consoleVariables.begin(); it != consoleVariables.end(); ++it)
		{
			if (!stricmp(it->first, szCVarName.c_str()))
			{
				 return it->second.value;
			}
		}

		ICVar* pCvar = gEnv->pConsole->GetCVar(szCVarName.c_str());
		if (pCvar)
		{
			return pCvar->GetString();
		}
		
		return string();
	}

	void StoreConsoleVariable(const string& szCVarName, const string& szValue, bool isRequestRestart)
	{
		if (szCVarName.IsEmpty() || szValue.IsEmpty())
			return;

		for (auto it = consoleVariables.begin(); it != consoleVariables.end(); ++it)
		{
			if (!stricmp(it->first, szCVarName.c_str()))
			{
				if (it->second.value != szValue)
				{
					it->second.bIsChanged = true;
				}

				it->second.value = szValue;	
				it->second.bIsRequestRestart = isRequestRestart;
				return;
			}
		}

		SVariableValue variable;
		variable.value = szValue;
		variable.bIsRequestRestart = isRequestRestart;
		variable.bIsChanged = true;

		consoleVariables.emplace(szCVarName, variable);
	}

	struct SVariableValue
	{
		SVariableValue() {}
		SVariableValue(const string& str) : value(str) {}

		string value;
		bool bIsChanged = false;
		bool bIsRequestRestart = false;
	};

	std::map<string, SVariableValue> consoleVariables;
};

struct SConsoleVariable
{
	enum class EType
	{
		String,
		Int,
		Float,
		Bool,
		Enum
	};

	SConsoleVariable() {}

	SConsoleVariable(string _name, QVariant _value, EType _type, bool _restart)
		: name(_name)
		, value(_value)
		, type(_type)
		, bIsRequestRestart(_restart) 
	{
	}

	string   name;
	string   description;
	QVariant value;
	EType    type = EType::String;
	bool     bIsRequestRestart = false;

	void ParseFromString(const string& str)
	{
		if (str.IsEmpty())
			return;

		value = str.c_str();
	}

	string SaveToString()
	{
		return QtUtil::ToString(value.toString());
	}
};

#define CREATE_CONSOLE_VAR(_name, _defaultValue, _type, _requestRestart) SConsoleVariable _name = { #_name, _defaultValue, _type, _requestRestart };
#define GENERATE_PAGE_CONSTRUCTOR(_page, _name, _category) _page::_page() : SProjectSettingsPage(_name, _category) {};

#define PARSE_CONSOLE_VAR(_var, _helper) _var.ParseFromString(_helper.GetConsoleVariableValue(_var.name));
#define PARSE_CONSOLE_VAR_AS_ENUM(_var, _helper, _enum) \
yasli::EnumDescription& _enum ## _description = yasli::EnumDescriptionImpl<_enum>::the(); \
const string _var ## str_value = _helper.GetConsoleVariableValue(_var.name); \
_enum _var ## value = static_cast<_enum>(_enum ## _description.value(_var ## str_value.c_str())); \
_var.value = _var ## value; \

#define SAVE_CONSOLE_VAR(_var, _helper) _helper.StoreConsoleVariable(_var.name, _var.SaveToString(), _var.bIsRequestRestart);
#define SAVE_CONSOLE_VAR_AS_ENUM(_var, _helper, _enum) \
yasli::EnumDescription& _enum ## _description = yasli::EnumDescriptionImpl<_enum>::the(); \
_helper.StoreConsoleVariable(_var.name, _enum ## _description.name(_var.value.value<_enum>()), _var.bIsRequestRestart); \

#define SERIALIZE_CONSOLE_VAR(_var, _description) ar(_var, #_var, _description);
#define SERIALIZE_CONSOLE_VAR_AS_ENUM(_var, _description, _enum)              \
if (ar.isOutput()) { ar(_var.value.value<_enum>(), #_var, _description);}   \
else { _enum _value = static_cast<_enum>(0); ar(_value, #_var, _description); \
	_var.value = _value;                                                      \
} \

bool Serialize(Serialization::IArchive& ar, SConsoleVariable& var, const char* szName, const char* szLabel);

struct SProjectSettingsPage
{
	SProjectSettingsPage(const char* name, const char* path)
		: m_name(name)
		, m_path(path)
	{
	}

	virtual ~SProjectSettingsPage() {}

	const string& GetName() const { return m_name; }
	const string& GetPath() const { return m_path; }
	string        GetFullPath() const { return m_path + "/" + m_name; }

	virtual bool  Serialize(yasli::Archive& ar)
	{
		return true;
	}

	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper)
	{
	}

	virtual void SaveToFile(SConsoleVariableHelper& helper)
	{
	}

	virtual void CheckPluginAvailable(const string& pluginName)
	{
	}

	void operator=(const SProjectSettingsPage& other)
	{
		if (this != &other)
		{
			m_name = other.m_name;
			m_path = other.m_path;
		}
	}

	void SetIsVisible(bool visible) { m_bIsVisible = visible; }
	bool IsVisible() const { return m_bIsVisible; }

private:
	// private empty constructor to make sure we have a valid name & path
	SProjectSettingsPage() {}

	friend class CProjectSettings;
	void    SetName(const string& name) { m_name = name; }
	void    SetPath(const string& path) { m_path = path; }

	QString GetSerializedProperties();
	void    FromSerializedProperties(const QByteArray& jsonBlob);

public:
	CCrySignal<void()> signalSettingsChanged;

private:
	CCrySignal<void()> signalRequestReset;

	string             m_name;
	string             m_path;
	bool               m_bIsVisible = true;
};

class CProjectSettings
{
	friend yasli::Serializer;
public:
	CProjectSettings();
	~CProjectSettings();

	// Need to call init after all preferences have been registered
	void Init();

	// Tray area controls the lifetime of the widget
	template<typename Type>
	void RegisterPage()
	{
		Type* pPreferencePage = new Type();
		pPreferencePage->signalSettingsChanged.Connect(std::function<void()>([this]() { signalSettingsChanged(); }));
		pPreferencePage->signalRequestReset.Connect(std::function<void()>([pPreferencePage]()
			{
				*pPreferencePage = Type();
				pPreferencePage->signalSettingsChanged();
			}));

		AddPage(pPreferencePage);
	}

	template<typename Type>
	void RegisterPage(Type* pPreferencePage)
	{
		pPreferencePage->signalSettingsChanged.Connect(std::function<void()>([this]() { signalSettingsChanged(); }));
		pPreferencePage->signalRequestReset.Connect(std::function<void()>([pPreferencePage]()
			{
				*pPreferencePage = Type();
				pPreferencePage->signalSettingsChanged();
			}));

		AddPage(pPreferencePage);
	}

	std::vector<SProjectSettingsPage*> GetPages(const char* path);
	QWidget* GetPageWidget(const char* path)
	{
		return new QProjectSettingsPage(GetPages(path), path);
	}

	const std::map<string, std::vector<SProjectSettingsPage*>>& GetPages() const { return m_preferences; }

	bool                                                   IsLoading() const { return m_bIsLoading; }
	void                                                   Reset(const char* path);
	void                                                   Save();

private:
	void         Load();
	void         AddPage(SProjectSettingsPage* pPreferencePage);

	virtual bool Serialize(yasli::Archive& ar);

public:
	CCrySignal<void()> signalSettingsChanged;
	CCrySignal<void()> signalSettingsReset;

private:
	SConsoleVariableHelper helper;
	std::map<string, std::vector<SProjectSettingsPage*>> m_preferences;
	bool m_bIsLoading;
};

ILINE bool Serialize(yasli::Archive& ar, SProjectSettingsPage* val, const char* name, const char* label)
{
	if (!val)
		return false;

	return ar(*val, name ? name : val->GetFullPath().c_str(), label ? label : val->GetName().c_str());
}