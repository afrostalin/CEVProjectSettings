// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once 


#include "ProjectSettings.h"

struct SSettings_EngineGeneral : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineGeneral, "Engine", "Engine/General");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	SConsoleVariable log_Verbosity = { "log_Verbosity", 3, SConsoleVariable::EType::Int, false};
	SConsoleVariable log_WriteToFile = { "log_WriteToFile", 1, SConsoleVariable::EType::Bool, false};
	SConsoleVariable log_WriteToFileVerbosity = { "log_WriteToFileVerbosity", 3, SConsoleVariable::EType::Int, false };
};

extern SSettings_EngineGeneral gSettings_EngineGeneral;

struct SSettings_EngineAI : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineAI, "Engine", "Engine/AI");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	//~SProjectSettingsPage
};

extern SSettings_EngineAI gSettings_EngineAI;

struct SSettings_EngineAnimation : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineAnimation, "Engine", "Engine/Animation");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	CREATE_CONSOLE_VAR(ca_SkeletonEffectsPlayAudioInEngine, 0, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(ca_useIMG_CAF, 0, SConsoleVariable::EType::Bool, false);
};

extern SSettings_EngineAnimation gSettings_EngineAnimation;

enum EAudioImplName
{
	EAIMPL_CryAudioImplSDLMixer,
	EAIMPL_CryAudioImplFmod,
	EAIMPL_CryAudioImplPortAudio,
	EAIMPL_CryAudioImplWwise,
	EAIMPL_CryAudioImplAdx2
};
Q_DECLARE_METATYPE(EAudioImplName);

struct SSettings_EngineAudio : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineAudio, "Engine", "Engine/Audio");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	CREATE_CONSOLE_VAR(s_ImplName, EAudioImplName::EAIMPL_CryAudioImplSDLMixer, SConsoleVariable::EType::Enum, false);
	CREATE_CONSOLE_VAR(s_drawdebug, "0", SConsoleVariable::EType::String, false);
	CREATE_CONSOLE_VAR(sys_audio_disable, 0, SConsoleVariable::EType::Bool, false);
};

extern SSettings_EngineAudio gSettings_EngineAudio;

struct SSettings_EngineConsole : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineConsole, "Engine", "Engine/Console");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	SConsoleVariable sys_DeactivateConsole = { "sys_DeactivateConsole", 0, SConsoleVariable::EType::Bool, false };
	SConsoleVariable con_showonload = { "con_showonload", 0, SConsoleVariable::EType::Bool, false };
};

extern SSettings_EngineConsole gSettings_EngineConsole;

struct SSettings_EngineInput : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineInput, "Engine", "Engine/Input");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	//~SProjectSettingsPage
};

extern SSettings_EngineInput gSettings_EngineInput;

struct SSettings_EngineNetwork : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineNetwork, "Engine", "Engine/Network");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	//~SProjectSettingsPage
};

extern SSettings_EngineNetwork gSettings_EngineNetwork;

struct SSettings_EnginePhysics : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EnginePhysics, "Engine", "Engine/Physics");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	CREATE_CONSOLE_VAR(sys_physics, 1, SConsoleVariable::EType::Bool, false);

	CREATE_CONSOLE_VAR(p_draw_helpers, "0", SConsoleVariable::EType::String, false);
};

extern SSettings_EnginePhysics gSettings_EnginePhysics;

enum ERendererDriver 
{
	ERD_DX11 = 0,
	ERD_DX12,
	ERD_GL,
	ERD_VK,
	ERD_AUTO
};
Q_DECLARE_METATYPE(ERendererDriver);

enum EVolumetricClouds
{
	EVClouds_OFF = 0,
	EVClouds_ON_1_2,
	EVClouds_ON_1_4
};
Q_DECLARE_METATYPE(EVolumetricClouds);

enum EAAMode
{
	EAAM_Off = 0,
	EAAM_SMAA1X,
	EAAM_SMAA1TX,
	EAAM_SMAA2TX,
	EAAM_TSAA
};
Q_DECLARE_METATYPE(EAAMode);

enum EPostProcessEffects
{
	EPPE_Off = 0,
	EPPE_Enabled,
	EPPE_EnabledAndDisplay
};
Q_DECLARE_METATYPE(EPostProcessEffects);

enum EHDREyeAdaptationMode
{
	EHDREA_Disabled = 0,
	EHDREA_Standart,
	EHDREA_Legacy
};
Q_DECLARE_METATYPE(EHDREyeAdaptationMode);

struct SSettings_EngineRendering : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineRendering, "Engine", "Engine/Rendering");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	// General
	CREATE_CONSOLE_VAR(sys_maxFPS, -1, SConsoleVariable::EType::Int, false);
	CREATE_CONSOLE_VAR(r_vsync, 1, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(r_driver, ERendererDriver::ERD_DX11, SConsoleVariable::EType::Enum, true);
	

	// Debug
	CREATE_CONSOLE_VAR(r_displayInfo, 3, SConsoleVariable::EType::Int, false);
	CREATE_CONSOLE_VAR(r_profiler, 0, SConsoleVariable::EType::Int, false);

	// Graphics
	CREATE_CONSOLE_VAR(e_SkyBox, 1, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(r_VolumetricClouds, EVolumetricClouds::EVClouds_OFF, SConsoleVariable::EType::Enum, false);
	CREATE_CONSOLE_VAR(e_VolumetricFog, 0, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(e_Fog, 1, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(r_AntialiasingMode, EAAMode::EAAM_SMAA1TX, SConsoleVariable::EType::Enum, false);
	CREATE_CONSOLE_VAR(r_ssdo, 1, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(e_ShadowsMaxTexRes, 1024, SConsoleVariable::EType::Int, false);
	CREATE_CONSOLE_VAR(r_HDREyeAdaptationMode, EHDREyeAdaptationMode::EHDREA_Legacy, SConsoleVariable::EType::Enum, false);
	CREATE_CONSOLE_VAR(r_ShadowsScreenSpace, 0, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(r_PostProcessEffects, EPostProcessEffects::EPPE_Enabled, SConsoleVariable::EType::Enum, false);

	// Water
	CREATE_CONSOLE_VAR(r_WaterReflections, 1, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(r_WaterCaustics, 1, SConsoleVariable::EType::Bool, false);
};

extern SSettings_EngineRendering gSettings_EngineRendering;

struct SSettings_EngineUI : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineUI, "Engine", "Engine/User interface");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	CREATE_CONSOLE_VAR(sys_flash, 1, SConsoleVariable::EType::Bool, false);
};

extern SSettings_EngineUI gSettings_EngineUI;


struct SSettings_EngineCompiler : public SProjectSettingsPage
{
	GENERATE_PAGE_CONSTRUCTOR(SSettings_EngineCompiler, "Engine", "Engine/Compiler");

	// SProjectSettingsPage
	virtual bool Serialize(yasli::Archive& ar) override;
	virtual void ParseConsoleVars(const SConsoleVariableHelper& helper) override;
	virtual void SaveToFile(SConsoleVariableHelper& helper) override;
	//~SProjectSettingsPage

	CREATE_CONSOLE_VAR(r_ShadersRemoteCompiler, 0, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(r_ShaderCompilerServer, "localhost", SConsoleVariable::EType::String, false);
	CREATE_CONSOLE_VAR(r_ShaderCompilerPort, 61453, SConsoleVariable::EType::Int, false);
	CREATE_CONSOLE_VAR(r_ShadersAsyncCompiling, 3, SConsoleVariable::EType::Int, false);
	CREATE_CONSOLE_VAR(r_ShadersAsyncMaxThreads, 1, SConsoleVariable::EType::Int, false);
	CREATE_CONSOLE_VAR(r_ShadersAllowCompilation, 1, SConsoleVariable::EType::Bool, false);
	CREATE_CONSOLE_VAR(r_ShaderTarget, "", SConsoleVariable::EType::String, false);
};

extern SSettings_EngineCompiler gSettings_EngineCompiler;