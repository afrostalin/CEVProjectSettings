// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once 

#include "ProjectSettings.h"

struct SSettings_Project : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_Project, "Project", "Project/General");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	int    version = 1;
	string type = "Game";
	string name = "Game project";
	string guid = "00000000-0000-0000-0000-000000000000";
};

extern SSettings_Project gProjectSettings;

struct SSettings_Project_Packaging : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_Project_Packaging, "Project", "Project/Packaging");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	//~SProjectSettingsPage
};

extern SSettings_Project_Packaging gProjectSettings_Packaging;