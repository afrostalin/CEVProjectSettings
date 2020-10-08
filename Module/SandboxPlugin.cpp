// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#include "StdAfx.h"
#include "SandboxPlugin.h"
#include "ProjectSettings.h"
#include "ProjectSettingsDialog.h"

#include <CryCore/Platform/platform_impl.inl>

REGISTER_PLUGIN(CCEVProjectSettingsPlugin)

REGISTER_VIEWPANE_FACTORY(QProjectSettingsDialog, "ProjectSettings", "Tools", false);

static CCEVProjectSettingsPlugin* g_pInstance = nullptr;

CCEVProjectSettingsPlugin::CCEVProjectSettingsPlugin()
{
	assert(g_pInstance == nullptr);
	g_pInstance = this;

	m_pProjectSettings = new CProjectSettings();

	CAutoRegisterProjectSettingsHelper::RegisterAll();

	m_pProjectSettings->Init();
}

CCEVProjectSettingsPlugin::~CCEVProjectSettingsPlugin()
{
	assert(g_pInstance == this);
	g_pInstance = nullptr;

	SAFE_DELETE(m_pProjectSettings);

	CAutoRegisterProjectSettingsHelper::UnregisterAll();
}


CCEVProjectSettingsPlugin* CCEVProjectSettingsPlugin::GetInstance()
{
	return g_pInstance;
}

const char* CCEVProjectSettingsPlugin::GetPluginName()
{
	return "CEVProjectSettings";
}

int32 CCEVProjectSettingsPlugin::GetPluginVersion()
{
	return 1;
}

const char* CCEVProjectSettingsPlugin::GetPluginDescription()
{
	return "Tool for editing project settings";
}
