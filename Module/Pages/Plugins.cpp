// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#include "StdAfx.h"
#include "Plugins.h"

//CEVPlayer gSettings_PluginsCEVPlayer;
//
//REGISTER_PROJECT_SETTINGS_PAGE_PTR(CEVPlayer, &gSettings_PluginsCEVPlayer)
//
//CEVPlayer::CEVPlayer() : SProjectSettingsPage("Plugins", "Plugins/CEVPlayer")
//{ 
//	SetIsVisible(false);
//}
//
//bool CEVPlayer::Serialize(yasli::Archive& ar)
//{
//	ar.openBlock("CEVPlayer", "General");
//
//	SERIALIZE_CONSOLE_VAR(vp_disableLogs, "Disable logs from plugin");
//	SERIALIZE_CONSOLE_VAR(vp_audio_volume, "Video volume");
//
//	ar.closeBlock();
//
//	ar.openBlock("CEVPlayer", "Debug");
//
//	SERIALIZE_CONSOLE_VAR(vp_debug_log, "Enable debug logging");
//	SERIALIZE_CONSOLE_VAR(vp_debug_draw, "Enable debug draw");
//
//	ar.closeBlock();
//
//	return true;
//}
//
//void CEVPlayer::ParseConsoleVars(const SConsoleVariableHelper& helper)
//{
//	PARSE_CONSOLE_VAR(vp_disableLogs, helper);
//	PARSE_CONSOLE_VAR(vp_audio_volume, helper);
//	PARSE_CONSOLE_VAR(vp_debug_log, helper);
//	PARSE_CONSOLE_VAR(vp_debug_draw, helper);
//}
//
//void CEVPlayer::SaveToFile(SConsoleVariableHelper& helper)
//{
//	SAVE_CONSOLE_VAR(vp_disableLogs, helper);
//	SAVE_CONSOLE_VAR(vp_audio_volume, helper);
//	SAVE_CONSOLE_VAR(vp_debug_log, helper);
//	SAVE_CONSOLE_VAR(vp_debug_draw, helper);
//}
//
//void CEVPlayer::CheckPluginAvailable(const string& pluginName)
//{
//	if (pluginName == "CEVPlayer")
//	{
//		SetIsVisible(true);
//	}
//}
