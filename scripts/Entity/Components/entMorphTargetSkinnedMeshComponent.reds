public native class entMorphTargetSkinnedMeshComponent extends entISkinTargetComponent {
  native let morphResource: ResourceAsyncRef;
  native let meshAppearance: CName;
  native let castShadows: shadowsShadowCastingMode;
  native let castLocalShadows: shadowsShadowCastingMode;
  native let acceptDismemberment: Bool;
  native let chunkMask: Uint64;
  native let renderingPlaneAnimationParam: CName;
  native let visibilityAnimationParam: CName;
  native let isEnabled: Bool;
  native let tags: TagList;
}
