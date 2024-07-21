#pragma once

namespace App
{
struct PlacedComponentEx : Red::IPlacedComponent
{
    Vector4 GetWorldPosition() const;
    Quaternion GetWorldOrientation() const;
};
}

RTTI_EXPAND_CLASS(Red::IPlacedComponent, App::PlacedComponentEx, {
    RTTI_METHOD(GetWorldPosition);
    RTTI_METHOD(GetWorldOrientation);
});
