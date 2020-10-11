// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once

#include "ProjectSettings.h"

struct SProjectCustomConfig
{
	struct SConfig
	{
		void Serialize(Serialization::IArchive& ar)
		{
			ar(category, "category", "category");
			ar(path, "path", "path");
			ar(variables, "variables", "variables");
		}

		struct SVariable
		{
			void Serialize(Serialization::IArchive& ar)
			{
				ar(name, "name", "name");
				ar(value, "value", "value");
				ar(description, "description", "description");
				ar(type, "type", "type");
				ar(enumDescription, "enumDescription", "enumDescription");
				ar(requestRestart, "requestRestart", "requestRestart");
			}

			struct SEnumDescription
			{
				void Serialize(Serialization::IArchive& ar)
				{
					ar(key, "key", "key");
					ar(description, "description", "description");
				}

				string key;
				string description;
			};

			string name;
			string value;
			string description;
			string type;
			bool requestRestart = false;
			std::vector<SEnumDescription> enumDescription;
		};

		string category;
		string path;
		std::vector<SVariable> variables;
	};

	std::vector<SConfig> configs;

	bool Serialize(Serialization::IArchive& ar)
	{
		ar(configs, "configs", "configs");

		return true;
	}
};

class CCustomSettingsPage : public SProjectSettingsPage
{
public:
	CCustomSettingsPage() : SProjectSettingsPage(nullptr, nullptr) {}
	CCustomSettingsPage(const SProjectCustomConfig::SConfig& _config);
public:
	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	virtual void CheckPluginAvailable(const string& pluginName) override;
	//~SProjectSettingsPage
private:
	SProjectCustomConfig::SConfig config;
private:
	std::map<string, SConsoleVariable> variables;
};

class CCustomParser
{
public:
	CCustomParser() {}
	~CCustomParser() {}
public:
	void FindAndParseCustomSettings();
private:
	std::vector<SProjectCustomConfig> customConfigs;
	std::vector<CCustomSettingsPage*> pages;
};