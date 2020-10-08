// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#include "StdAfx.h"
#include "Engine.h"

SSettings_EngineGeneral   gSettings_EngineGeneral;
SSettings_EngineAI        gSettings_EngineAI;
SSettings_EngineAnimation gSettings_EngineAnimation;
SSettings_EngineAudio     gSettings_EngineAudio;
SSettings_EngineConsole   gSettings_EngineConsole;
SSettings_EngineInput     gSettings_EngineInput;
SSettings_EngineNetwork   gSettings_EngineNetwork;
SSettings_EnginePhysics   gSettings_EnginePhysics;
SSettings_EngineRendering gSettings_EngineRendering;
SSettings_EngineUI        gSettings_EngineUI;
SSettings_EngineCompiler  gSettings_EngineCompiler;

REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineGeneral, &gSettings_EngineGeneral)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineAI, &gSettings_EngineAI)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineAnimation, &gSettings_EngineAnimation)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineAudio, &gSettings_EngineAudio)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineConsole, &gSettings_EngineConsole)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineInput, &gSettings_EngineInput)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineNetwork, &gSettings_EngineNetwork)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EnginePhysics, &gSettings_EnginePhysics)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineRendering, &gSettings_EngineRendering)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineUI, &gSettings_EngineUI)
REGISTER_PROJECT_SETTINGS_PAGE_PTR(SSettings_EngineCompiler, &gSettings_EngineCompiler)

YASLI_ENUM_BEGIN(EAudioImplName, "EAudioImplName")
YASLI_ENUM(EAudioImplName::EAIMPL_CryAudioImplSDLMixer, "CryAudioImplSDLMixer", "CryAudioImplSDLMixer")
YASLI_ENUM(EAudioImplName::EAIMPL_CryAudioImplFmod, "CryAudioImplFmod", "CryAudioImplFmod")
YASLI_ENUM(EAudioImplName::EAIMPL_CryAudioImplPortAudio, "CryAudioImplPortAudio", "CryAudioImplPortAudio")
YASLI_ENUM(EAudioImplName::EAIMPL_CryAudioImplWwise, "CryAudioImplWwise", "CryAudioImplWwise")
YASLI_ENUM(EAudioImplName::EAIMPL_CryAudioImplAdx2, "CryAudioImplAdx2", "CryAudioImplAdx2")
YASLI_ENUM_END()

YASLI_ENUM_BEGIN(ERendererDriver, "ERendererDriver")
YASLI_ENUM(ERendererDriver::ERD_DX11, "DX11", "DX11")
YASLI_ENUM(ERendererDriver::ERD_DX12, "DX12", "DX12")
YASLI_ENUM(ERendererDriver::ERD_GL, "GL", "GL")
YASLI_ENUM(ERendererDriver::ERD_VK, "VK", "VK")
YASLI_ENUM(ERendererDriver::ERD_AUTO, "AUTO", "AUTO")
YASLI_ENUM_END()

YASLI_ENUM_BEGIN(EVolumetricClouds, "EVolumetricClouds")
YASLI_ENUM(EVolumetricClouds::EVClouds_OFF, "0", "Disabled")
YASLI_ENUM(EVolumetricClouds::EVClouds_ON_1_2, "1", "Enabled (1/2x Res)")
YASLI_ENUM(EVolumetricClouds::EVClouds_ON_1_4, "2", "Enabled (1/4x Res)")
YASLI_ENUM_END()

YASLI_ENUM_BEGIN(EAAMode, "EAAMode")
YASLI_ENUM(EAAMode::EAAM_Off, "0", "Disabled")
YASLI_ENUM(EAAMode::EAAM_SMAA1X, "1", "SMAA1X")
YASLI_ENUM(EAAMode::EAAM_SMAA1TX, "2", "SMAA1TX")
YASLI_ENUM(EAAMode::EAAM_SMAA2TX, "3", "SMAA2TX")
YASLI_ENUM(EAAMode::EAAM_TSAA, "4", "TSAA")
YASLI_ENUM_END()

YASLI_ENUM_BEGIN(EPostProcessEffects, "EPostProcessEffects")
YASLI_ENUM(EPostProcessEffects::EPPE_Off, "0", "Disabled")
YASLI_ENUM(EPostProcessEffects::EPPE_Enabled, "1", "Enabled")
YASLI_ENUM(EPostProcessEffects::EPPE_EnabledAndDisplay, "2", "Enabled and display active effects")
YASLI_ENUM_END()

YASLI_ENUM_BEGIN(EHDREyeAdaptationMode, "EHDREyeAdaptationMode")
YASLI_ENUM(EHDREyeAdaptationMode::EHDREA_Disabled, "0", "Disabled")
YASLI_ENUM(EHDREyeAdaptationMode::EHDREA_Standart, "1", "Standart")
YASLI_ENUM(EHDREyeAdaptationMode::EHDREA_Legacy, "2", "Legacy")
YASLI_ENUM_END()

bool SSettings_EngineGeneral::Serialize(yasli::Archive& ar)
{
	ar.openBlock("EngineLog", "Log settings");

	SERIALIZE_CONSOLE_VAR(log_Verbosity, "Log verbosity level in console");
	SERIALIZE_CONSOLE_VAR(log_WriteToFile, "Write log to file");
	SERIALIZE_CONSOLE_VAR(log_WriteToFileVerbosity, "Log verbosity level in file");

	ar.closeBlock();

	return true;
}

void SSettings_EngineGeneral::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR(log_Verbosity, helper);
	PARSE_CONSOLE_VAR(log_WriteToFile, helper);
	PARSE_CONSOLE_VAR(log_WriteToFileVerbosity, helper);
}

void SSettings_EngineGeneral::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR(log_Verbosity, helper);
	SAVE_CONSOLE_VAR(log_WriteToFile, helper);
	SAVE_CONSOLE_VAR(log_WriteToFileVerbosity, helper);
}

bool SSettings_EngineAI::Serialize(yasli::Archive& ar)
{
	return true;
}

bool SSettings_EngineAnimation::Serialize(yasli::Archive& ar)
{
	ar.openBlock("EngineAnimation", "General");

	SERIALIZE_CONSOLE_VAR(ca_SkeletonEffectsPlayAudioInEngine, "Skeleton audio effects are spawned and played within CE");
	SERIALIZE_CONSOLE_VAR(ca_useIMG_CAF, "Use IMG file (disabled in development mode)");

	ar.closeBlock();

	return true;
}

void SSettings_EngineAnimation::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR(ca_SkeletonEffectsPlayAudioInEngine, helper);
	PARSE_CONSOLE_VAR(ca_useIMG_CAF, helper);
}

void SSettings_EngineAnimation::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR(ca_SkeletonEffectsPlayAudioInEngine, helper);
	SAVE_CONSOLE_VAR(ca_useIMG_CAF, helper);
}

bool SSettings_EngineAudio::Serialize(yasli::Archive& ar)
{
	ar.openBlock("EngineAudio", "General");

	SERIALIZE_CONSOLE_VAR_AS_ENUM(s_ImplName, "Audio library", EAudioImplName);
	SERIALIZE_CONSOLE_VAR(sys_audio_disable, "Disable audio system");

	ar.closeBlock();

	ar.openBlock("EngineAudio", "Debug");
	SERIALIZE_CONSOLE_VAR(s_drawdebug, "Audio draw debug flags");
	ar.closeBlock();

	return true;
}

void SSettings_EngineAudio::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR_AS_ENUM(s_ImplName, helper, EAudioImplName);
	PARSE_CONSOLE_VAR(sys_audio_disable, helper);
	PARSE_CONSOLE_VAR(s_drawdebug, helper);
}

void SSettings_EngineAudio::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR_AS_ENUM(s_ImplName, helper, EAudioImplName);
	SAVE_CONSOLE_VAR(sys_audio_disable, helper);
	SAVE_CONSOLE_VAR(s_drawdebug, helper);
}

bool SSettings_EngineConsole::Serialize(yasli::Archive& ar)
{
	ar.openBlock("EngineConsole", "General");

	SERIALIZE_CONSOLE_VAR(sys_DeactivateConsole, "Deactivate console");
	SERIALIZE_CONSOLE_VAR(con_showonload, "Show console on level loading");

	ar.closeBlock();

	return true;
}

void SSettings_EngineConsole::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR(sys_DeactivateConsole, helper);
	PARSE_CONSOLE_VAR(con_showonload, helper);
}

void SSettings_EngineConsole::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR(sys_DeactivateConsole, helper);
	SAVE_CONSOLE_VAR(con_showonload, helper);
}

bool SSettings_EngineInput::Serialize(yasli::Archive& ar)
{
	return true;
}

bool SSettings_EngineNetwork::Serialize(yasli::Archive& ar)
{
	return true;
}

bool SSettings_EnginePhysics::Serialize(yasli::Archive& ar)
{
	ar.openBlock("EnginePhysicsGeneral", "General");

	SERIALIZE_CONSOLE_VAR(sys_physics, "Enable physics");

	ar.closeBlock();

	ar.openBlock("EnginePhysicsDebug", "Debug");

	SERIALIZE_CONSOLE_VAR(p_draw_helpers, "Draw physics helpers flags");

	ar.closeBlock();

	return true;
}

void SSettings_EnginePhysics::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR(sys_physics, helper);
	PARSE_CONSOLE_VAR(p_draw_helpers, helper);
}

void SSettings_EnginePhysics::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR(sys_physics, helper);
	SAVE_CONSOLE_VAR(p_draw_helpers, helper);
}

bool SSettings_EngineRendering::Serialize(yasli::Archive& ar)
{
	ar.openBlock("RenderingGeneral", "General");

	SERIALIZE_CONSOLE_VAR(r_vsync, "Enable VSync");
	SERIALIZE_CONSOLE_VAR(sys_maxFPS, "Max FPS");
	SERIALIZE_CONSOLE_VAR_AS_ENUM(r_driver, "Driver", ERendererDriver);

	ar.closeBlock();

	ar.openBlock("RenderingDebug", "Debug");

	SERIALIZE_CONSOLE_VAR(r_displayInfo, "Display info level");
	SERIALIZE_CONSOLE_VAR(r_profiler, "Rendering profiler level");

	ar.closeBlock();

	ar.openBlock("RenderingGraphics", "Graphics");
	{
		SERIALIZE_CONSOLE_VAR_AS_ENUM(r_AntialiasingMode, "Anti-Aliasing mode", EAAMode);
		SERIALIZE_CONSOLE_VAR(r_ssdo, "Enable Screen Space Directional Occlusion");
		SERIALIZE_CONSOLE_VAR_AS_ENUM(r_HDREyeAdaptationMode, "Eye adaptation (auto exposure) mode", EHDREyeAdaptationMode);
		SERIALIZE_CONSOLE_VAR_AS_ENUM(r_PostProcessEffects, "Post process effects", EPostProcessEffects);

		ar.openBlock("Sky", "Sky");
		{
			SERIALIZE_CONSOLE_VAR(e_SkyBox, "Enable skybox");
			SERIALIZE_CONSOLE_VAR_AS_ENUM(r_VolumetricClouds, "Volumetric clouds", EVolumetricClouds);
		}
		ar.closeBlock();

		ar.openBlock("Fog", "Fog");
		{
			SERIALIZE_CONSOLE_VAR(e_VolumetricFog, "Enable volumetric fog");
			SERIALIZE_CONSOLE_VAR(e_Fog, "Enable fog");
		}
		ar.closeBlock();
		
		ar.openBlock("Shadows", "Shadows");
		{
			SERIALIZE_CONSOLE_VAR(e_ShadowsMaxTexRes, "Maximum resolution of shadow map");
			SERIALIZE_CONSOLE_VAR(r_ShadowsScreenSpace, "Include screen space tracing into shadow computations");
		}
		ar.closeBlock();

		ar.openBlock("Water", "Water");
		{
			SERIALIZE_CONSOLE_VAR(r_WaterReflections, "Enable water reflections");
			SERIALIZE_CONSOLE_VAR(r_WaterCaustics, "Enable water caustics");
		}
		ar.closeBlock();
	}
	ar.closeBlock();
	

	return true;
}

void SSettings_EngineRendering::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR(r_vsync, helper);
	PARSE_CONSOLE_VAR(sys_maxFPS, helper);

	PARSE_CONSOLE_VAR_AS_ENUM(r_driver, helper, ERendererDriver);

	PARSE_CONSOLE_VAR(r_displayInfo, helper);
	PARSE_CONSOLE_VAR(r_profiler, helper);
	PARSE_CONSOLE_VAR(e_SkyBox, helper);

	PARSE_CONSOLE_VAR_AS_ENUM(r_VolumetricClouds, helper, EVolumetricClouds);

	PARSE_CONSOLE_VAR(e_VolumetricFog, helper);
	PARSE_CONSOLE_VAR(e_Fog, helper);
	PARSE_CONSOLE_VAR_AS_ENUM(r_AntialiasingMode, helper, EAAMode);
	PARSE_CONSOLE_VAR(r_ssdo, helper);
	PARSE_CONSOLE_VAR(e_ShadowsMaxTexRes, helper);
	PARSE_CONSOLE_VAR_AS_ENUM(r_HDREyeAdaptationMode, helper, EHDREyeAdaptationMode);
	PARSE_CONSOLE_VAR(r_ShadowsScreenSpace, helper);

	PARSE_CONSOLE_VAR(r_WaterReflections, helper);
	PARSE_CONSOLE_VAR(r_WaterCaustics, helper);
	PARSE_CONSOLE_VAR_AS_ENUM(r_PostProcessEffects, helper, EPostProcessEffects);
}

void SSettings_EngineRendering::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR(r_vsync, helper);
	SAVE_CONSOLE_VAR(sys_maxFPS, helper);

	SAVE_CONSOLE_VAR_AS_ENUM(r_driver, helper, ERendererDriver);

	SAVE_CONSOLE_VAR(r_displayInfo, helper);
	SAVE_CONSOLE_VAR(r_profiler, helper);
	SAVE_CONSOLE_VAR(e_SkyBox, helper);

	SAVE_CONSOLE_VAR_AS_ENUM(r_VolumetricClouds, helper, EVolumetricClouds);

	SAVE_CONSOLE_VAR(e_VolumetricFog, helper);
	SAVE_CONSOLE_VAR(e_Fog, helper);
	SAVE_CONSOLE_VAR_AS_ENUM(r_AntialiasingMode, helper, EAAMode);
	SAVE_CONSOLE_VAR(r_ssdo, helper);
	SAVE_CONSOLE_VAR(e_ShadowsMaxTexRes, helper);
	SAVE_CONSOLE_VAR_AS_ENUM(r_HDREyeAdaptationMode, helper, EHDREyeAdaptationMode);
	SAVE_CONSOLE_VAR(r_ShadowsScreenSpace, helper);

	SAVE_CONSOLE_VAR(r_WaterReflections, helper);
	SAVE_CONSOLE_VAR(r_WaterCaustics, helper);
	SAVE_CONSOLE_VAR_AS_ENUM(r_PostProcessEffects, helper, EPostProcessEffects);
}

bool SSettings_EngineUI::Serialize(yasli::Archive& ar)
{
	ar.openBlock("EngineConsole", "Console general");

	SERIALIZE_CONSOLE_VAR(sys_flash, "Enable Flash UI system");

	ar.closeBlock();

	return true;
}

void SSettings_EngineUI::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR(sys_flash, helper);
}

void SSettings_EngineUI::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR(sys_flash, helper);
}

bool SSettings_EngineCompiler::Serialize(yasli::Archive& ar)
{
	ar.openBlock("EngineCompiler", "Remote shader compiller");

	SERIALIZE_CONSOLE_VAR(r_ShadersRemoteCompiler, "Enables remote shader compilation");
	SERIALIZE_CONSOLE_VAR(r_ShaderCompilerServer, "Shader compiler ip");
	SERIALIZE_CONSOLE_VAR(r_ShaderCompilerPort, "Shader compiler port");
	SERIALIZE_CONSOLE_VAR(r_ShadersAsyncCompiling, "Async compiling mode (r_ShadersAsyncCompiling)");
	SERIALIZE_CONSOLE_VAR(r_ShadersAsyncMaxThreads, "Max async threads count");
	SERIALIZE_CONSOLE_VAR(r_ShadersAllowCompilation, "Allow shaders compilation");
	SERIALIZE_CONSOLE_VAR(r_ShaderTarget, "Shader target(Orbis/Durango/D3D11/D3D12/Vulkan)");

	ar.closeBlock();

	return true;
}

void SSettings_EngineCompiler::ParseConsoleVars(const SConsoleVariableHelper& helper)
{
	PARSE_CONSOLE_VAR(r_ShadersRemoteCompiler, helper);
	PARSE_CONSOLE_VAR(r_ShaderCompilerServer, helper);
	PARSE_CONSOLE_VAR(r_ShaderCompilerPort, helper);
	PARSE_CONSOLE_VAR(r_ShadersAsyncMaxThreads, helper);
	PARSE_CONSOLE_VAR(r_ShadersAsyncCompiling, helper);
	PARSE_CONSOLE_VAR(r_ShadersAllowCompilation, helper);
	PARSE_CONSOLE_VAR(r_ShaderTarget, helper);
}

void SSettings_EngineCompiler::SaveToFile(SConsoleVariableHelper& helper)
{
	SAVE_CONSOLE_VAR(r_ShadersRemoteCompiler, helper);
	SAVE_CONSOLE_VAR(r_ShaderCompilerServer, helper);
	SAVE_CONSOLE_VAR(r_ShaderCompilerPort, helper);
	SAVE_CONSOLE_VAR(r_ShadersAsyncMaxThreads, helper);
	SAVE_CONSOLE_VAR(r_ShadersAsyncCompiling, helper);
	SAVE_CONSOLE_VAR(r_ShadersAllowCompilation, helper);
	SAVE_CONSOLE_VAR(r_ShaderTarget, helper);
}
