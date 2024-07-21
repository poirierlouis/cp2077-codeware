#include "PlacedComponentEx.hpp"

Vector4 App::PlacedComponentEx::GetWorldPosition() const
{
    Red::Vector4 position{};

    Red::CallStatic("WorldPosition", "ToVector4", position, worldTransform.Position);
    return position;
}

Quaternion App::PlacedComponentEx::GetWorldOrientation() const
{
    return worldTransform.Orientation;
}
