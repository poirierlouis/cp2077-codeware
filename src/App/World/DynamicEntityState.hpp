#pragma once

#include "DynamicEntitySpec.hpp"

namespace App
{
struct DynamicEntityState : Red::IScriptable
{
    DynamicEntityState() = default;

    DynamicEntityState(Red::EntityID aEntityId, const DynamicEntitySpec& aEntitySpec)
        : entityID(aEntityId)
        , entitySpec(Red::MakeHandle<DynamicEntitySpec>(aEntitySpec))
        , entityStub(nullptr)
    {
    }

    void TakeoveStub(Red::EntityStubToken& aToken)
    {
        entityStub = aToken.ExtractStub();
    }

    Red::EntityID entityID;
    Red::Handle<DynamicEntitySpec> entitySpec;
    Red::EntityStub* entityStub;

    RTTI_IMPL_TYPEINFO(App::DynamicEntityState);
    RTTI_IMPL_ALLOCATOR(Red::Memory::RTTIAllocator);
};

using DynamicEntityStatePtr = Red::Handle<DynamicEntityState>;
}

RTTI_DEFINE_CLASS(App::DynamicEntityState, {
    RTTI_PERSISTENT(entityID);
    RTTI_PERSISTENT(entitySpec);
});