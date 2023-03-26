
public native class DynamicEntitySpec {
    public native let recordID: TweakDBID;
    public native let templatePath: ResRef;
    public native let appearanceName: CName;
    public native let position: Vector4;
    public native let orientation: Quaternion;
    public native let persistState: Bool;
    public native let persistSpawn: Bool;
    public native let alwaysSpawned: Bool;
    public native let spawnInView: Bool;
    public native let tags: array<CName>;
    public native let active: Bool;

    public native func IsValid() -> Bool
}

public native class DynamicEntitySystem extends IGameSystem {
    public native func CreateEntity(spec: ref<DynamicEntitySpec>) -> EntityID
    public native func DeleteEntity(id: EntityID) -> Bool
    public native func EnableEntity(id: EntityID) -> Bool
    public native func DisableEntity(id: EntityID) -> Bool

    public native func AssignTag(id: EntityID, tag: CName)
    public native func UnassignTag(id: EntityID, tag: CName)
    public native func GetTags(id: EntityID) -> array<CName>
    public native func IsPopulated(tag: CName) -> Bool
    public native func GetEntityID(tag: CName) -> EntityID
    public native func GetEntityIDs(tag: CName) -> array<EntityID>
    public native func DeleteTagged(tag: CName)
    public native func EnableTagged(tag: CName)
    public native func DisableTagged(tag: CName)
}
