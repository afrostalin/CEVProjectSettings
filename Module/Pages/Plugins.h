// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once 

#include "ProjectSettings.h"

struct CEVPlayer : public SProjectSettingsPage
{
	CEVPlayer();

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	virtual void CheckPluginAvailable(const string& pluginName) override;
	//~SProjectSettingsPage

	CREATE_CONSOLE_VAR(vp_debug_log, 0, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(vp_debug_draw, 0, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(vp_disableLogs, 0, SConsoleVariable::EType::Bool, false);

	CREATE_CONSOLE_VAR(vp_audio_volume, 1.0f, SConsoleVariable::EType::Float, false);
};

extern CEVPlayer gSettings_PluginsCEVPlayer;