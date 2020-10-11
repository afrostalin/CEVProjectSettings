start_sources()
sources_platform(ALL)
add_sources("NoUberFile"
	SOURCE_GROUP "Plugin"
		"StdAfx.h"
		"StdAfx.cpp"
		"SandboxPlugin.h"
		"SandboxPlugin.cpp"
		"ProjectSettings.h"
		"ProjectSettings.cpp"
		"ProjectSettingsDialog.h"
		"ProjectSettingsDialog.cpp"
		"CustomParser.h"
		"CustomParser.cpp"
	SOURCE_GROUP "Pages"
		"Pages/Engine.h"
		"Pages/Engine.cpp"
		"Pages/Game.h"
		"Pages/Game.cpp"
		"Pages/Platforms.h"
		"Pages/Platforms.cpp"
		"Pages/Plugins.h"
		"Pages/Plugins.cpp"
		"Pages/Project.h"
		"Pages/Project.cpp"
)

end_sources()

CryEditorPlugin(CEVProjectSettings PCH "StdAfx.cpp" SOLUTION_FOLDER "Project/Plugins/Sandbox")
