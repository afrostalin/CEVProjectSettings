// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once 

#include "ProjectSettings.h"

struct SSettings_Game : public SProjectSettingsPage
{
	SSettings_Game();

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	//~SProjectSettingsPage

	string assetFolder = "Assets";
	string codeFolder = "Code";
};

extern SSettings_Game gSettings_Game;