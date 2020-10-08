// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once 

#include "ProjectSettings.h"

struct SSettings_PlatformsGeneral : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_PlatformsGeneral, "Platforms", "Platforms/General");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	CREATE_CONSOLE_VAR(sys_target_platforms, "pc,ps4,xboxone,linux", SConsoleVariable::EType::String, false);
};

extern SSettings_PlatformsGeneral gSettings_PlatformsGeneral;

struct SSettings_PlatformsWindows : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_PlatformsWindows, "Platforms", "Platforms/Windows");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	CREATE_CONSOLE_VAR(r_WindowIconTexture, "assets/textures/icon.dds", SConsoleVariable::EType::String, false);
};

extern SSettings_PlatformsWindows gSettings_PlatformsWindows;

#ifdef CRY_PLATFORM_ORBIS
struct SSettings_PlatformsPlayStation4 : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_PlatformsPlayStation4, "Platforms", "Platforms/Play Station 4");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	//~SProjectSettingsPage
};

extern SSettings_PlatformsPlayStation4 gSettings_PlatformsPlayStation4;
#endif

#ifdef CRY_PLATFORM_DURANGO
struct SSettings_Platforms_XboxOne : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_Platforms_XboxOne, "Platforms", "Platforms/XBox One");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	//~SProjectSettingsPage
};

extern SSettings_Platforms_XboxOne gSettings_PlatformsXboxOne;
#endif

#ifdef CRY_PLATFORM_SWITCH
struct SSettings_Platforms_Switch : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_Platforms_Switch, "Platforms", "Platforms/Switch");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	//~SProjectSettingsPage
};

extern SSettings_Platforms_Switch gSettings_PlatformsSwitch;
#endif

#ifdef CRY_PLATFORM_ANDROID
struct SSettings_Platforms_Android : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_Platforms_Android, "Platforms", "Platforms/Android");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	//~SProjectSettingsPage
};

extern SSettings_Platforms_Android gSettings_PlatformsAndroid;
#endif