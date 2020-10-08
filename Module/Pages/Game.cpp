// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#include "StdAfx.h"
#include "Game.h"

SSettings_Game gSettings_Game;

REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_Game, &gSettings_Game)

SSettings_Game::SSettings_Game() : SProjectSettingsPage("Game", "Game/General")
{
}

bool SSettings_Game::Serialize(yasli::Archive& ar)
{
	ar.openBlock("GameGeneral", "General");
	ar(assetFolder, "GameAssetFolder", "Assets folder");
	ar(codeFolder, "GameCodeFolder", "Code folder");
	ar.closeBlock();

	return false;
}
