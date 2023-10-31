#pragma once

#include "Red/Addresses.hpp"

namespace Red
{
using FactHash = uint32_t;
using FactStoreIndex = uint32_t;

struct FactStore
{
    uint64_t unk00;
    Red::Map<FactHash, int32_t> data;
};

struct FactManager
{
    virtual ~FactManager() = 0;                                                      // 00
    virtual void sub_08() = 0;                                                       // 08
    virtual int32_t GetFact(FactStoreIndex aStore, FactHash aFact) = 0;              // 10
    virtual void SetFact(FactStoreIndex aStore, FactHash aFact, int32_t aValue) = 0; // 18

    inline uint32_t GetFact(FactHash aFact)
    {
        return GetFact(1, aFact);
    }

    inline void SetFact(FactHash aFact, int32_t aValue)
    {
        SetFact(1, aFact, aValue);
    }

    FactStore* data[11];
};

using NodeID = uint16_t;
using NodePath = DynArray<NodeID>;
using NodePathHash = uint32_t;

struct PhaseNodePath
{
    PhaseNodePath() = default;

    PhaseNodePath(NodePathHash aPhaseHash, NodeID aNodeID = 0, NodeID aSubNodeID = 0)
        : phaseHash(aPhaseHash)
        , subNodeID(aSubNodeID)
        , nodeID(aNodeID)
    {
    }

    PhaseNodePath(const NodePath& aNodePath, NodeID aNodeID = 0, NodeID aSubNodeID = 0)
        : phaseHash(FNV1a32(reinterpret_cast<uint8_t*>(aNodePath.entries), aNodePath.size * sizeof(NodeID)))
        , subNodeID(aSubNodeID)
        , nodeID(aNodeID)
    {
    }

    NodePathHash phaseHash;
    NodeID subNodeID;
    NodeID nodeID;
};

struct QuestContext
{
    uint8_t unk0[0xF8];                       // 00
    DynArray<questPhaseInstance*> phaseStack; // F8
    uint16_t unk108;                          // 108
    uint64_t unk110[0x44];                    // 110
};
RED4EXT_ASSERT_SIZE(QuestContext, 0x330);
RED4EXT_ASSERT_OFFSET(QuestContext, phaseStack, 0xF8);

struct QuestNodeSocket
{
    QuestNodeSocket(CName aName = {})
        : name(aName)
        , unk08(0)
    {
    }

    CName name;
    uint8_t unk08;
};
}

namespace Raw::QuestsSystem
{
using FactManager = Core::OffsetPtr<0xF8, Red::FactManager*>;

// constexpr auto StopPhase = Core::RawVFunc<
//     /* addr = */ 0x210,
//     /* type = */ void (Red::questIQuestsSystem::*)(const Red::PhaseNodePath& aNodePath, uint8_t a2)>();
//
// constexpr auto RestartPhase = Core::RawVFunc<
//     /* addr = */ 0x238,
//     /* type = */ void (Red::questIQuestsSystem::*)(const Red::PhaseNodePath& aNodePath,
//                                                    const Red::DynArray<Red::CName>& aInputSockets)>();

constexpr auto CreateContext = Core::RawFunc<
    /* addr = */ 0x14027A6E4 - Red::Addresses::ImageBase, // FIXME
    /* type = */ void* (*)(Red::questIQuestsSystem* aPhase,
                           Red::QuestContext* aContext,
                           int8_t a3 /* = 1 */,
                           int8_t a4 /* = 0 */,
                           int32_t a5 /* = 1000000 */,
                           int32_t a6 /* = -1 */)>();
}

namespace Raw::PhaseInstance
{
constexpr auto Initialize = Core::RawFunc<
    /* addr = */ 0x14027CFA4 - Red::Addresses::ImageBase, // FIXME
    /* type = */ void* (*)(Red::questPhaseInstance* aPhase,
                           uint64_t a2,
                           const Red::Handle<Red::questQuestPhaseResource>& aResource,
                           const Red::Handle<Red::questGraphDefinition>& aGraph,
                           const Red::NodePath& aParentPath,
                           Red::NodeID aPhaseNodeID)>();

constexpr auto ExequteSequence = Core::RawFunc<
    /* addr = */ 0x1404D9A70 - Red::Addresses::ImageBase, // FIXME
    /* type = */ bool (*)(Red::questPhaseInstance* aPhase,
                          Red::QuestContext& aContext,
                          const Red::WeakHandle<Red::questNodeDefinition>& aNode,
                          const Red::QuestNodeSocket& aInputSocket,
                          bool a5,
                          const Red::DynArray<Red::QuestNodeSocket>& aOutputSocket)>();

constexpr auto ExecuteNode = Core::RawFunc<
    /* addr = */ 0x14027DD1C - Red::Addresses::ImageBase, // FIXME
    /* type = */ bool (*)(Red::questPhaseInstance* aPhase,
                          Red::questNodeDefinition* aNode,
                          Red::QuestContext& aContext,
                          const Red::QuestNodeSocket& aInputSocket,
                          const Red::DynArray<Red::QuestNodeSocket>& aOutputSocket)>();
}
