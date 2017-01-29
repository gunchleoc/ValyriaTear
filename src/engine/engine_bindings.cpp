///////////////////////////////////////////////////////////////////////////////
//            Copyright (C) 2004-2011 by The Allacrost Project
//            Copyright (C) 2012-2016 by Bertram (Valyria Tear)
//                         All Rights Reserved
//
// This code is licensed under the GNU GPL version 2. It is free software
// and you may modify it and/or redistribute it under the terms of this license.
// See http://www.gnu.org/copyleft/gpl.html for details.
///////////////////////////////////////////////////////////////////////////////

/** ***************************************************************************
*** \file    engine_bindings.cpp
*** \author  Daniel Steuernol, steu@allacrost.org
*** \author  Yohann Ferreira, yohann ferreira orange fr
*** \brief   Lua bindings for the engine code
***
*** All bindings for the engine code is contained within this file.
*** Therefore, everything that you see bound within this file will be made
*** available in Lua.
***
*** \note To most C++ programmers, the syntax of the binding code found in this
*** file may be very unfamiliar and obtuse. Refer to the Luabind documentation
*** as necessary to gain an understanding of this code style.
*** **************************************************************************/

#include "utils/utils_pch.h"

#include "engine/audio/audio.h"
#include "engine/input.h"
#include "engine/mode_manager.h"
#include "engine/script/script.h"
#include "engine/system.h"
#include "engine/video/video.h"
#include "engine/video/particle_effect.h"

#include "common/global/global.h"

namespace vt_defs
{

void BindEngineCode()
{
    // ----- Audio Engine Bindings
    {
        using namespace vt_audio;

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_audio")
        [
            luabind::class_<AudioEngine>("GameAudio")
            .def("LoadSound", &AudioEngine::LoadSound)
            .def("PlaySound", &AudioEngine::PlaySound)
            .def("PlayMusic", &AudioEngine::PlayMusic)
            .def("LoadMusic", &AudioEngine::LoadMusic)
            .def("PauseActiveMusic", &AudioEngine::PauseActiveMusic)
            .def("ResumeActiveMusic", &AudioEngine::ResumeActiveMusic)
            .def("FadeOutActiveMusic", &AudioEngine::FadeOutActiveMusic)
            .def("FadeInActiveMusic", &AudioEngine::FadeInActiveMusic)
            .def("FadeOutAllSounds", &AudioEngine::FadeOutAllSounds)
        ];

    } // End using audio namespaces



    // ----- Input Engine Bindings
    {
        using namespace vt_input;

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_input")
        [
            luabind::class_<InputEngine>("GameInput")
            .def("GetUpKeyName", &InputEngine::GetUpKeyName)
            .def("GetDownKeyName", &InputEngine::GetDownKeyName)
            .def("GetLeftKeyName", &InputEngine::GetLeftKeyName)
            .def("GetRightKeyName", &InputEngine::GetRightKeyName)
            .def("GetConfirmKeyName", &InputEngine::GetConfirmKeyName)
            .def("GetCancelKeyName", &InputEngine::GetCancelKeyName)
            .def("GetMenuKeyName", &InputEngine::GetMenuKeyName)
            .def("GetMinimapKeyName", &InputEngine::GetMinimapKeyName)
            .def("GetPauseKeyName", &InputEngine::GetPauseKeyName)
            .def("GetHelpKeyName", &InputEngine::GetHelpKeyName)
            .def("GetQuitKeyName", &InputEngine::GetQuitKeyName)
        ];

    } // End using input namespaces



    // ----- Mode Manager Engine Bindings
    {
        using namespace vt_mode_manager;

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_mode_manager")
        [
            luabind::class_<ScriptSupervisor>("ScriptSupervisor")
            .def("AddScript", &ScriptSupervisor::AddScript)
            .def("CreateImage", &ScriptSupervisor::CreateImage)
            .def("CreateAnimation", &ScriptSupervisor::CreateAnimation)
            .def("CreateText", (vt_video::TextImage*(ScriptSupervisor:: *)(const std::string&, const vt_video::TextStyle&))&ScriptSupervisor::CreateText)
            .def("CreateText", (vt_video::TextImage*(ScriptSupervisor:: *)(const vt_utils::ustring&, const vt_video::TextStyle&))&ScriptSupervisor::CreateText)
            .def("SetDrawFlag", &ScriptSupervisor::SetDrawFlag)
        ];

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_mode_manager")
        [
            luabind::class_<EffectSupervisor>("EffectSupervisor")
            .def("EnableLightingOverlay", &EffectSupervisor::EnableLightingOverlay)
            .def("DisableLightingOverlay", &EffectSupervisor::DisableLightingOverlay)
            .def("EnableAmbientOverlay", &EffectSupervisor::EnableAmbientOverlay)
            .def("DisableAmbientOverlay", &EffectSupervisor::DisableAmbientOverlay)
            .def("DisableEffects", &EffectSupervisor::DisableEffects)
            .def("GetCameraXMovement", &EffectSupervisor::GetCameraXMovement)
            .def("GetCameraYMovement", &EffectSupervisor::GetCameraYMovement)
            .def("ShakeScreen", &EffectSupervisor::ShakeScreen)
            .def("StopShaking", &EffectSupervisor::StopShaking)

            // Namespace constants
            .enum_("constants") [
                // Shake fall off types
                luabind::value("SHAKE_FALLOFF_NONE", SHAKE_FALLOFF_NONE),
                luabind::value("SHAKE_FALLOFF_EASE", SHAKE_FALLOFF_EASE),
                luabind::value("SHAKE_FALLOFF_LINEAR", SHAKE_FALLOFF_LINEAR),
                luabind::value("SHAKE_FALLOFF_GRADUAL", SHAKE_FALLOFF_GRADUAL),
                luabind::value("SHAKE_FALLOFF_SUDDEN", SHAKE_FALLOFF_SUDDEN)
            ]
        ];

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_mode_manager")
        [
            luabind::class_<ParticleEffect>("ParticleEffect")
            .def(luabind::constructor<>())
            .def(luabind::constructor<const std::string &>())
            .def("LoadEffect", &ParticleEffect::LoadEffect)
            .def("Update", (void (ParticleEffect:: *)())&ParticleEffect::Update)
            .def("Draw", &ParticleEffect::Draw)
            .def("IsAlive", &ParticleEffect::IsAlive)
            .def("Move", &ParticleEffect::Move)
            .def("Stop", &ParticleEffect::Stop)
            .def("Start", &ParticleEffect::Start)
        ];

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_mode_manager")
        [
            luabind::class_<ParticleManager>("ParticleManager")
            .def("AddParticleEffect", &ParticleManager::AddParticleEffect)
            .def("StopAll", &ParticleManager::StopAll)
        ];

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_mode_manager")
        [
            luabind::class_<IndicatorSupervisor>("IndicatorSupervisor")
            .def("AddDamageIndicator", &IndicatorSupervisor::AddDamageIndicator)
            .def("AddHealingIndicator", &IndicatorSupervisor::AddHealingIndicator)
            .def("AddItemIndicator", &IndicatorSupervisor::AddItemIndicator)
            .def("AddShortNotice", &IndicatorSupervisor::AddShortNotice)
        ];

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_mode_manager")
        [
            luabind::class_<GameMode>("GameMode")
            .def("GetScriptSupervisor", &GameMode::GetScriptSupervisor)
            .def("GetEffectSupervisor", &GameMode::GetEffectSupervisor)
            .def("GetParticleManager", &GameMode::GetParticleManager)
            .def("GetIndicatorSupervisor", &GameMode::GetIndicatorSupervisor)
        ];

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_mode_manager")
        [
            luabind::class_<ModeEngine>("GameModeManager")
            // The adopt policy set on the GameMode pointer is permitting to avoid
            // a memory corruption after the call time.
            .def("Push", &ModeEngine::Push, luabind::adopt(_2))
            .def("Pop", &ModeEngine::Pop)
            .def("PopAll", &ModeEngine::PopAll)
            .def("GetTop", &ModeEngine::GetTop)
            .def("Get", &ModeEngine::Get)
            .def("GetGameType", (uint8_t(ModeEngine:: *)(uint32_t))&ModeEngine::GetGameType)
            .def("GetGameType", (uint8_t(ModeEngine:: *)())&ModeEngine::GetGameType)
        ];

    } // End using mode manager namespaces

    // ----- Script Engine Bindings
    {
        using namespace vt_script;

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_script")
        [
            luabind::class_<ScriptEngine>("GameScript")
            .def("DEBUG_DumpScriptsState", &ScriptEngine::DEBUG_DumpScriptsState)
        ];

    } // End using script namespaces



    // ----- System Engine Bindings
    {
        using namespace vt_system;

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_system")
        [
            luabind::def("Translate", &vt_system::Translate),
            luabind::def("CTranslate", &vt_system::CTranslate),
            luabind::def("UTranslate", &vt_system::UTranslate),
            luabind::def("CUTranslate", &vt_system::CUTranslate),

            // Specializaton of c-formatted translation bounds
            luabind::def("VTranslate", (std::string(*)(const std::string&, uint32_t)) &vt_system::VTranslate),
            luabind::def("VTranslate", (std::string(*)(const std::string&, int32_t)) &vt_system::VTranslate),
            luabind::def("VTranslate", (std::string(*)(const std::string&, float)) &vt_system::VTranslate),
            luabind::def("VTranslate", (std::string(*)(const std::string&, const std::string&)) &vt_system::VTranslate),

            luabind::class_<SystemTimer>("SystemTimer")
            .def(luabind::constructor<>())
            .def(luabind::constructor<uint32_t, int32_t>())
            .def("Initialize", &SystemTimer::Initialize)
            .def("EnableAutoUpdate", &SystemTimer::EnableAutoUpdate)
            .def("EnableManualUpdate", &SystemTimer::EnableManualUpdate)
            .def("Update", (void(SystemTimer:: *)(void)) &SystemTimer::Update)
            .def("Update", (void(SystemTimer:: *)(uint32_t)) &SystemTimer::Update)
            .def("Reset", &SystemTimer::Reset)
            .def("Run", &SystemTimer::Run)
            .def("Pause", &SystemTimer::Pause)
            .def("Finish", &SystemTimer::Finish)
            .def("IsInitial", &SystemTimer::IsInitial)
            .def("IsRunning", &SystemTimer::IsRunning)
            .def("IsPaused", &SystemTimer::IsPaused)
            .def("IsFinished", &SystemTimer::IsFinished)
            .def("CurrentLoop", &SystemTimer::CurrentLoop)
            .def("TimeLeft", &SystemTimer::TimeLeft)
            .def("PercentComplete", &SystemTimer::PercentComplete)
            .def("SetDuration", &SystemTimer::SetDuration)
            .def("SetNumberLoops", &SystemTimer::SetNumberLoops)
            .def("SetModeOwner", &SystemTimer::SetModeOwner)
            .def("GetState", &SystemTimer::GetState)
            .def("GetDuration", &SystemTimer::GetDuration)
            .def("GetNumberLoops", &SystemTimer::GetNumberLoops)
            .def("IsAutoUpdate", &SystemTimer::IsAutoUpdate)
            .def("GetModeOwner", &SystemTimer::GetModeOwner)
            .def("GetTimeExpired", &SystemTimer::GetTimeExpired)
            .def("GetTimesCompleted", &SystemTimer::GetTimesCompleted),

            luabind::class_<SystemEngine>("GameSystem")
            .def("GetUpdateTime", &SystemEngine::GetUpdateTime)
            .def("SetPlayTime", &SystemEngine::SetPlayTime)
            .def("GetPlayHours", &SystemEngine::GetPlayHours)
            .def("GetPlayMinutes", &SystemEngine::GetPlayMinutes)
            .def("GetPlaySeconds", &SystemEngine::GetPlaySeconds)
            .def("GetLanguageLocale", &SystemEngine::GetLanguageLocale)
            .def("GetGameDifficulty", &SystemEngine::GetGameDifficulty)
        ];

    } // End using system namespaces



    // ----- Video Engine Bindings
    {
        using namespace vt_video;

        luabind::module(vt_script::ScriptManager->GetGlobalState(), "vt_video")
        [
            luabind::class_<Color>("Color")
            .def(luabind::constructor<float, float, float, float>())
            .def("SetAlpha", &Color::SetAlpha)
            .def("SetColor", (void(Color::*)(float, float, float, float))&Color::SetColor),

            luabind::class_<ImageDescriptor>("ImageDescriptor")
            .def("GetWidth", &ImageDescriptor::GetWidth)
            .def("GetHeight", &ImageDescriptor::GetHeight)
            .def("SetGrayscale", &ImageDescriptor::SetGrayscale)
            .def("IsGrayscale", &ImageDescriptor::IsGrayscale)
            .def("Update", &ImageDescriptor::Update),

            luabind::class_<StillImage, ImageDescriptor>("StillImage")
            .def("Clear", &StillImage::Clear)
            .def("Draw", (void(StillImage::*)(const vt_video::Color&)) &StillImage::Draw)
            .def("Draw", (void(StillImage::*)()) &StillImage::Draw)
            .def("SetWidth", &StillImage::SetWidth)
            .def("SetHeight", &StillImage::SetHeight)
            .def("SetWidthKeepRatio", &StillImage::SetWidthKeepRatio)
            .def("SetHeightKeepRatio", &StillImage::SetHeightKeepRatio)
            .def("SetDimensions", &StillImage::SetDimensions)
            .def("SetXDrawOffset", &StillImage::SetXDrawOffset)
            .def("SetYDrawOffset", &StillImage::SetYDrawOffset)
            .def("SetDrawOffsets", &StillImage::SetDrawOffsets),

            luabind::class_<AnimatedImage, ImageDescriptor>("AnimatedImage")
            .def("Clear", &AnimatedImage::Clear)
            .def("Draw", (void(AnimatedImage::*)(const Color&))&AnimatedImage::Draw)
            .def("Draw", (void(AnimatedImage::*)())&AnimatedImage::Draw)
            .def("Update", (void(AnimatedImage::*)())&AnimatedImage::Update)
            .def("Update", (void(AnimatedImage::*)(uint32_t))&AnimatedImage::Update)
            .def("ResetAnimation", &AnimatedImage::ResetAnimation)
            .def("GetAnimationLength", &AnimatedImage::GetAnimationLength)
            .def("RandomizeAnimationFrame", &AnimatedImage::RandomizeAnimationFrame)
            .def("SetWidth", &AnimatedImage::SetWidth)
            .def("SetHeight", &AnimatedImage::SetHeight)
            .def("SetDimensions", &AnimatedImage::SetDimensions)
            .def("SetAnimationBlended", &AnimatedImage::SetAnimationBlended)
            .def("GetAnimationBlended", &AnimatedImage::GetAnimationBlended),

            luabind::class_<TextImage, ImageDescriptor>("TextImage")
            .def("Clear", &TextImage::Clear)
            .def("Draw", (void(TextImage::*)(const Color&))&TextImage::Draw)
            .def("Draw", (void(TextImage::*)())&TextImage::Draw)
            .def("SetWidth", &TextImage::SetWidth)
            .def("SetHeight", &TextImage::SetHeight)
            .def("SetDimensions", &TextImage::SetDimensions)
            .def("SetText", (void(TextImage::*)(const std::string&))&TextImage::SetText)
            .def("SetText", (void(TextImage::*)(const std::string&, const TextStyle&))&TextImage::SetText)
            .def("SetText", (void(TextImage::*)(const vt_utils::ustring&))&TextImage::SetText)
            .def("SetText", (void(TextImage::*)(const vt_utils::ustring&, const TextStyle&))&TextImage::SetText)
            .def("SetStyle", &TextImage::SetStyle)
            .def("SetWordWrapWidth", &TextImage::SetWordWrapWidth)
            .def("GetWordWrapWidth", &TextImage::GetWordWrapWidth),

            luabind::class_<TextStyle>("TextStyle")
            .def(luabind::constructor<const std::string&>())
            .def(luabind::constructor<const std::string&, const Color&>()),

            luabind::class_<VideoEngine>("GameVideo")
            .def("FadeScreen", &VideoEngine::FadeScreen)
            .def("IsFading", &VideoEngine::IsFading)
            .def("FadeIn", &VideoEngine::FadeIn)

            // Draw cursor commands
            .def("Move", &VideoEngine::Move)
            .def("MoveRelative", &VideoEngine::MoveRelative)
            .def("Rotate", &VideoEngine::Rotate)

            // Namespace constants
            .enum_("constants") [
                // Video context drawing constants
                luabind::value("VIDEO_X_LEFT", VIDEO_X_LEFT),
                luabind::value("VIDEO_X_CENTER", VIDEO_X_CENTER),
                luabind::value("VIDEO_X_RIGHT", VIDEO_X_RIGHT),
                luabind::value("VIDEO_Y_TOP", VIDEO_Y_TOP),
                luabind::value("VIDEO_Y_CENTER", VIDEO_Y_CENTER),
                luabind::value("VIDEO_Y_BOTTOM", VIDEO_Y_BOTTOM),
                luabind::value("VIDEO_X_FLIP", VIDEO_X_FLIP),
                luabind::value("VIDEO_X_NOFLIP", VIDEO_X_NOFLIP),
                luabind::value("VIDEO_Y_FLIP", VIDEO_Y_FLIP),
                luabind::value("VIDEO_Y_NOFLIP", VIDEO_Y_NOFLIP),
                luabind::value("VIDEO_NO_BLEND", VIDEO_NO_BLEND),
                luabind::value("VIDEO_BLEND", VIDEO_BLEND),
                luabind::value("VIDEO_BLEND_ADD", VIDEO_BLEND_ADD)
            ]
        ];

    } // End using video namespaces

    // ---------- Bind engine class objects
    luabind::object global_table = luabind::globals(vt_script::ScriptManager->GetGlobalState());
    global_table["AudioManager"]     = vt_audio::AudioManager;
    global_table["InputManager"]     = vt_input::InputManager;
    global_table["ModeManager"]      = vt_mode_manager::ModeManager;
    global_table["ScriptManager"]    = vt_script::ScriptManager;
    global_table["SystemManager"]    = vt_system::SystemManager;
    global_table["VideoManager"]     = vt_video::VideoManager;
} // void BindEngineCode()

} // namespace vt_defs
