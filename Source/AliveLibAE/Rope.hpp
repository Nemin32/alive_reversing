#pragma once

#include "FunctionFwd.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"

class AnimationUnknown;

class Rope : public BaseAnimatedWithPhysicsGameObject
{
public:
    EXPORT Rope* ctor_4A0A70(unsigned __int16 left, __int16 top, unsigned __int16 bottom, FP scale);
    virtual BaseGameObject* VDestructor(signed int flags) override;
    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;
private:
    EXPORT void dtor_4A0DB0();
    EXPORT Rope* vdtor_4A0D80(signed int flags);
    EXPORT void vRender_4A0E30(PrimHeader** ppOt);
private:
    __int16 field_F4_rope_segment_count;
public:
    __int16 field_F6_rope_length;
    BYTE **field_F8_ppRopeRes;
    AnimationUnknown* field_FC_pRopeRes;
    __int16 field_100_left;
    __int16 field_102_top;
    __int16 field_104_right;
    __int16 field_106_bottom;
};
ALIVE_ASSERT_SIZEOF(Rope, 0x108);

EXPORT void CC ClipPoly_Vertically_4A09E0(Poly_FT4* pPoly, int minY, int maxY);
