#pragma once

#include "App/Scripting/ScriptableEnv.hpp"
#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/GameFramework.hpp"
#include "Red/GameInstance.hpp"
#include "Red/Scripting.hpp"

namespace App
{
class ScriptingService
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
public:
    Red::Handle<ScriptableEnv> GetEnvironment(Red::CClass* aType);

protected:
    void OnBootstrap() override;

    static void OnInitializeScripts();
    static void OnInitializeGameInstance();
    static void OnCreateInstance(Red::IScriptable*& aInstance, Red::CClass* aClass, uint32_t, bool);
    static void OnValidateScripts(void* aValidator, Red::ScriptBundle* aBundle, void* aReport);
    static bool OnValidateScriptType(Red::CBaseRTTIType* aNativeType, Red::ScriptType* aScriptType);
    static void OnValidateTypeName(bool& aValid, Red::CName aScriptTypeName, Red::CName aNativeTypeName);
    static void OnRegisterScriptOpCodes();
    static void ScriptOpCodeNew(Red::IScriptable*, Red::CStackFrame* aFrame, void* aRet, Red::CBaseRTTIType*);
    static void ScriptOpCodeCast(Red::IScriptable*, Red::CStackFrame* aFrame, void* aRet, Red::CBaseRTTIType*);
    // static void OnCheckScriptableClass(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
    //                                    bool* aRet, Red::CBaseRTTIType* aType);
    // static void OnCheckScriptableExactClass(Red::IScriptable* aContext, Red::CStackFrame* aFrame,
    //                                         bool* aRet, Red::CBaseRTTIType* aType);
    static void GetScriptGameInstance(Red::IScriptable*, Red::CStackFrame* aFrame,
                                      Red::ScriptGameInstance* aRet, Red::CBaseRTTIType*);

    inline static Core::Map<Red::CClass*, Red::Handle<ScriptableEnv>> s_environments;
};
}
