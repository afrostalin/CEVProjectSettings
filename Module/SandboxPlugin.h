// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once

#include <IEditor.h>
#include <IPlugin.h>

class CProjectSettings;
class CCustomParser;

class CCEVProjectSettingsPlugin : public IPlugin
{
public:
	static CCEVProjectSettingsPlugin* GetInstance();
public:
	explicit CCEVProjectSettingsPlugin();
	~CCEVProjectSettingsPlugin();
public:
	// IPlugin
	virtual const char* GetPluginName() override;
	virtual const char* GetPluginDescription() override;
	virtual int32       GetPluginVersion() override;
	//~IPlugin
public:
	CProjectSettings* GetProjectSettings() const { return m_pProjectSettings; }
	CCustomParser*    GetParser() const { return m_pParser;}
private:
	CProjectSettings* m_pProjectSettings = nullptr;
	CCustomParser*    m_pParser = nullptr;
};
