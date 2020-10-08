// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#include "StdAfx.h"
#include "Platforms.h"

SSettings_PlatformsGeneral      gSettings_PlatformsGeneral;
SSettings_PlatformsWindows      gSettings_PlatformsWindows;
#ifdef CRY_PLATFORM_ORBIS
SSettings_PlatformsPlayStation4 gSettings_PlatformsPlayStation4;
#endif
#ifdef CRY_PLATFORM_DURANGO
SSettings_Platforms_XboxOne     gSettings_PlatformsXboxOne;
#endif
#ifdef CRY_PLATFORM_SWITCH
SSettings_Platforms_Switch      gSettings_PlatformsSwitch;
#endif
#ifdef CRY_PLATFORM_ANDROID
SSettings_Platforms_Android     gSettings_PlatformsAndroid;
#endif

REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_PlatformsGeneral, &gSettings_PlatformsGeneral)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_PlatformsWindows, &gSettings_PlatformsWindows)
#ifdef CRY_PLATFORM_ORBIS
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_PlatformsPlayStation4, &gSettings_PlatformsPlayStation4)
#endif
#ifdef CRY_PLATFORM_DURANGO
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_Platforms_XboxOne, &gSettings_PlatformsXboxOne)
#endif
#ifdef CRY_PLATFORM_SWITCH
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_Platforms_Switch, &gSettings_PlatformsSwitch)
#endif
#ifdef CRY_PLATFORM_ANDROID
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_Platforms_Android, &gSettings_PlatformsAndroid)
#endif

bool SSettings_PlatformsGeneral::Serialize(yasli::Archive& ar)
{
	ar.openBlock("PlatformGeneral", "General");

	SERIALIZE_CONSOLE_VAR(sys_target_platforms, "Target platforms");

	ar.closeBlock();

	return true;
}

void SSettings_PlatformsGeneral::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR(sys_target_platforms, helper);
}

void SSettings_PlatformsGeneral::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR(sys_target_platforms, helper);
}

bool SSettings_PlatformsWindows::Serialize(yasli::Archive& ar)
{
	SERIALIZE_CONSOLE_VAR(r_WindowIconTexture, "Path to window icon texture");
	return true;
}

void SSettings_PlatformsWindows::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR(r_WindowIconTexture, helper);
}

void SSettings_PlatformsWindows::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR(r_WindowIconTexture, helper);
}

#ifdef CRY_PLATFORM_ORBIS
bool SSettings_PlatformsPlayStation4::Serialize(yasli::Archive& ar)
{
	return true;
}
#endif

#ifdef CRY_PLATFORM_DURANGO
bool SSettings_Platforms_XboxOne::Serialize(yasli::Archive& ar)
{
	return true;
}
#endif

#ifdef CRY_PLATFORM_SWITCH
bool SSettings_Platforms_Switch::Serialize(yasli::Archive& ar)
{
	return true;
}
#endif

#ifdef CRY_PLATFORM_ANDROID
bool SSettings_Platforms_Android::Serialize(yasli::Archive& ar)
{
	return true;
}
#endif