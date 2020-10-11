// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once

#include <CryCore/Project/CryModuleDefs.h>
#include <CryCore/Platform/platform.h>

#define CRY_USE_MFC
#include <CryCore/Platform/CryAtlMfc.h>
#include <CryString/CryPath.h>

#include "EditorCommon.h"

struct SHelper
{
	static std::vector<string> GetAllAssetWithExt(const string& folder, const string& ext)
	{
		std::vector<string> resultSet;

		const string search_path = folder + "/*." + ext;
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				// read all (real) files in current folder
				// , delete '!' read other 2 default folder . and ..
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					const string fileName = fd.cFileName;
					resultSet.push_back(folder + "/" + fileName);
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		return resultSet;
	}
};