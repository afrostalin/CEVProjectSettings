// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#include "StdAfx.h"
#include "Project.h"

SSettings_Project           gProjectSettings;
SSettings_Project_Packaging gProjectSettings_Packaging;

REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_Project, &gProjectSettings)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_Project_Packaging, &gProjectSettings_Packaging)

bool SSettings_Project::Serialize(yasli::Archive& ar)
{
	// General
	ar.openBlock("ProjectGeneral", "General");
	ar(version, "ProjectVersion", "Project version");
	ar(type, "ProjectType", "Project type");
	ar.closeBlock();

	// Description
	ar.openBlock("ProjectDescription", "Description");
	ar(name, "ProjectName", "Project name");
	ar(guid, "ProjectGUID", "Project guid");
	ar.closeBlock();

	return true;
}

void SSettings_Project::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
}

void SSettings_Project::SaveToFile(SConsoleVariableHelper& helper)
{
}

bool SSettings_Project_Packaging::Serialize(yasli::Archive& ar)
{
	return true;
}
