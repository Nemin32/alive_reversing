#include "stdafx.h"
#include "MotionDetector.hpp"
#include "stdlib.hpp"
#include "ObjectIds.hpp"
#include "SwitchStates.hpp"
#include "ScreenManager.hpp"
#include "PsxDisplay.hpp"
#include "BaseAliveGameObject.hpp"
#include "DDCheat.hpp"
#include "Abe.hpp"
#include "Function.hpp"

class MotionDetectorLaser : public BaseAnimatedWithPhysicsGameObject
{
public:
    EXPORT MotionDetectorLaser* ctor_468290(FP xpos, FP ypos, FP scale, __int16 layer)
    {
        BaseAnimatedWithPhysicsGameObject_ctor_424930(0);
        SetVTable(this, 0x545FB0);
        field_4_typeId = Types::eRedLaser_111;
        BYTE** ppRes = Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kMotionResID);
        Animation_Init_424E10(23280, 37, 60, ppRes, 1, 1);
        field_20_animation.field_C_render_layer = layer;
        field_B8_xpos = xpos;
        field_CC_sprite_scale = scale;
        field_20_animation.field_B_render_mode = 1;
        field_BC_ypos = ypos;
        return this;
    }

    virtual BaseGameObject* VDestructor(signed int flags) override
    {
        return vdtor_468360(flags);
    }

private:
    EXPORT MotionDetectorLaser* vdtor_468360(signed int flags)
    {
        BaseAnimatedWithPhysicsGameObject_dtor_424AD0();
        if (flags & 1)
        {
            Mem_Free_495540(this);
        }
        return this;
    }

private:
    int field_E4_not_used[4];
};
ALIVE_ASSERT_SIZEOF(MotionDetectorLaser, 0xF4);


MotionDetector* MotionDetector::ctor_4683B0(Path_MotionDetector* pTlv, int tlvInfo, BaseAnimatedWithPhysicsGameObject* pOwner)
{
    BaseAnimatedWithPhysicsGameObject_ctor_424930(0);
    SetVTable(this, 0x545FF8);
    field_4_typeId = Types::eGreeterBody_91;

    BYTE** ppRes = Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kMflareResID);
    Animation_Init_424E10(1736, 55, 22, ppRes, 1, 1);

    field_20_animation.field_4_flags.Set(AnimFlags::eBit15_bSemiTrans);
    field_20_animation.field_B_render_mode = 1;
    field_20_animation.field_C_render_layer = 36;
    
    field_D8_yOffset = 0;

    field_D0_r = 64;
    field_D4_b = 0;
    field_D2_g = 0;

    field_178_bObjectInLaser = 0;

    if (!pOwner)
    {
        field_110_bDontComeBack = 1;
        field_10E_bUnknown = 0;
        field_FC_owner_id = -1;

        field_F4_tlvInfo = tlvInfo;
        field_CC_sprite_scale = FP_FromInteger(1);

        if (pTlv->field_10_scale)
        {
            field_CC_sprite_scale = FP_FromDouble(0.5);
        }

        field_114_x1_fp = FP_FromInteger(pTlv->field_8_top_left.field_0_x);
        field_11C_y1_fp = FP_FromInteger(pTlv->field_C_bottom_right.field_0_x);
        field_118_x2_fp = FP_FromInteger(pTlv->field_8_top_left.field_2_y);
        field_120_y2_fp = FP_FromInteger(pTlv->field_C_bottom_right.field_2_y);

        PSX_Point pos = {};
        gMap_5C3030.Get_Abe_Spawn_Pos_4806D0(&pos);
        if (pTlv->field_12_device_x)
        {
            field_B8_xpos = FP_FromInteger(pTlv->field_12_device_x - pos.field_0_x);
            field_BC_ypos = FP_FromInteger(pTlv->field_14_device_y - pos.field_2_y);
        }
        else
        {
            field_B8_xpos = FP_FromInteger(pTlv->field_8_top_left.field_0_x);
            field_BC_ypos = FP_FromInteger(pTlv->field_8_top_left.field_2_y);
        }

        field_174_speed_x256 = (unsigned __int16)pTlv->field_16_speed_x256 << 8;

        MotionDetectorLaser* pLaser = nullptr;
        if (pTlv->field_18_start_on)
        {
            field_100_state = 2;
            pLaser = alive_new<MotionDetectorLaser>();
            if (pLaser)
            {
                pLaser->ctor_468290(field_11C_y1_fp, field_120_y2_fp, field_CC_sprite_scale, 36);
            }
        }
        else
        {
            field_100_state = 0;
            pLaser = alive_new<MotionDetectorLaser>();
            if (pLaser)
            {
                pLaser->ctor_468290(field_114_x1_fp, field_120_y2_fp, field_CC_sprite_scale, 36);
            }
        }

        if (pTlv->field_1A_draw_flare & 1)
        {
            field_20_animation.field_4_flags.Set(AnimFlags::eBit3_Render);
        }
        else
        {
            field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
        }

        if (pLaser)
        {
            field_F8_laser_id = pLaser->field_8_object_id;
            field_108_disable_id = pTlv->field_1C_disable_id;

            if (SwitchStates_Get_466020(static_cast<WORD>(field_F8_laser_id)) == 0)
            {
                pLaser->field_20_animation.field_4_flags.Set(AnimFlags::eBit3_Render);
            }
            else
            {
                pLaser->field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
            }
        }

        field_10A_alarm_id = pTlv->field_1E_alarm_id;
        field_10C_alarm_ticks = pTlv->field_20_alarm_ticks;
        return this;
    }

    field_10E_bUnknown = 1;
    field_CC_sprite_scale = pOwner->field_CC_sprite_scale;

    field_114_x1_fp = pOwner->field_B8_xpos - (field_CC_sprite_scale * FP_FromInteger(75));
    field_11C_y1_fp = (field_CC_sprite_scale * FP_FromInteger(75)) + pOwner->field_B8_xpos;
    field_118_x2_fp = pOwner->field_BC_ypos - (field_CC_sprite_scale * FP_FromInteger(20));
    field_120_y2_fp = pOwner->field_BC_ypos;

    field_B8_xpos = pOwner->field_B8_xpos;
    field_BC_ypos = pOwner->field_BC_ypos - (field_CC_sprite_scale * FP_FromInteger(20));

    field_174_speed_x256 = 0x20000;
    field_100_state = 0;

    auto pLaserMem = alive_new<MotionDetectorLaser>();
    if (pLaserMem)
    {
        pLaserMem->ctor_468290(pOwner->field_B8_xpos, pOwner->field_BC_ypos, field_CC_sprite_scale, 36);
    }

    field_F8_laser_id = pLaserMem->field_8_object_id;
    field_20_animation.field_4_flags.Set(AnimFlags::eBit3_Render);
    field_FC_owner_id = pOwner->field_8_object_id;
    field_10A_alarm_id = 0;
    field_10C_alarm_ticks = 0;
    return this;
}


MotionDetector* MotionDetector::vdtor_468850(signed int flags)
{
    dtor_468880();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
    return this;
}

void MotionDetector::dtor_468880()
{
    SetVTable(this, 0x545FF8);

    if (!field_10E_bUnknown)
    {
        if (field_110_bDontComeBack)
        {
            Path::TLV_Reset_4DB8E0(field_F4_tlvInfo, -1, 0, 0);
        }
        else
        {
            Path::TLV_Reset_4DB8E0(field_F4_tlvInfo, -1, 0, 1);
        }
    }

    BaseGameObject* pLaser = sObjectIds_5C1B70.Find_449CF0(field_F8_laser_id);
    if (pLaser)
    {
        pLaser->field_6_flags.Set(BaseGameObject::eDead);
    }

    BaseAnimatedWithPhysicsGameObject_dtor_424AD0();
}

void MotionDetector::vScreenChanged_469460()
{
    BaseGameObject::VScreenChanged();

    BaseGameObject* pOwner = sObjectIds_5C1B70.Find_449CF0(field_FC_owner_id);
    if (!pOwner)
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }
}

void MotionDetector::vRender_469120(int** pOt)
{
    BaseAnimatedWithPhysicsGameObject::VRender(pOt);

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render))
    {
        auto pLaser = static_cast<MotionDetectorLaser*>(sObjectIds_5C1B70.Find_449CF0(field_F8_laser_id));
        PSX_RECT bLaserRect = {};
        pLaser->vGetBoundingRect_424FD0(&bLaserRect, 1);

        const FP camXFp = pScreenManager_5BB5F4->field_20_pCamPos->field_0_x;
        const FP camYFp = pScreenManager_5BB5F4->field_20_pCamPos->field_4_y;

        const short screenX = FP_GetExponent(field_B8_xpos) - FP_GetExponent(camXFp);

        const short x0 = static_cast<short>(PsxToPCX(screenX, 11));
        const short y0 = FP_GetExponent(field_BC_ypos) - FP_GetExponent(camYFp);
        const short y1 = FP_GetExponent(pLaser->field_BC_ypos - camYFp);
        const short y2 = y1 + bLaserRect.y - bLaserRect.h;
        const short x1 = PsxToPCX(FP_GetExponent(pLaser->field_B8_xpos - camXFp), 11);

        Poly_F3* pPrim = &field_124_prims[gPsxDisplay_5C1130.field_C_buffer_index];
        PolyF3_Init(pPrim);

        SetXY0(pPrim, x0, y0);
        SetXY1(pPrim, x1, y1);
        SetXY2(pPrim, x1, y2);

        SetRGB0(pPrim, 80, 0, 0);

        // Add triangle
        Poly_Set_SemiTrans_4F8A60(&pPrim->mBase.header, TRUE);
        OrderingTable_Add_4F8AA0(&pOt[field_20_animation.field_C_render_layer], &pPrim->mBase.header);
        
        // Add tpage
        const int tpage = PSX_getTPage_4F60E0(2, field_178_bObjectInLaser != 0 ? 1 : 3, 0, 0); // When detected transparency is off, gives the "solid red" triangle
        Prim_SetTPage* pTPage = &field_154_tPage[gPsxDisplay_5C1130.field_C_buffer_index];
        Init_SetTPage_4F5B60(pTPage, 0, 0, tpage);
        OrderingTable_Add_4F8AA0(&pOt[field_20_animation.field_C_render_layer], &pTPage->mBase);
      
        pScreenManager_5BB5F4->InvalidateRect_40EC90(
            std::min(x0, std::min(x1, x1)),
            std::min(y0, std::min(y1, y2)),
            std::max(x0, std::max(x1, x1)),
            std::max(y0, std::max(y1, y2)),
            pScreenManager_5BB5F4->field_3A_idx);
    }
}

signed __int16 MotionDetector::IsInLaser_468980(BaseAliveGameObject* pWho, BaseGameObject* pOwner)
{
    if (pWho->field_4_typeId == BaseGameObject::Types::eType_Abe_69)
    {
        // Abe is safe in these states or if electrocuted or in ddcheat fly mode.
        if (pWho->field_106_current_state == eAbeStates::State_0_Idle_44EEB0 ||
            pWho->field_106_current_state == eAbeStates::State_17_CrouchIdle_456BC0 ||
            pWho->field_106_current_state == eAbeStates::State_67_LedgeHang_454E20 ||
            pWho->field_106_current_state == eAbeStates::State_60_4A3200 ||
            pWho->field_106_current_state == eAbeStates::State_57_Dead_4589A0 ||
            pWho->field_106_current_state == eAbeStates::State_117_In_MineCar_4587C0 ||
            pWho->field_114_flags.Get(Flags_114::e114_Bit7_Electrocuted) ||
            sDDCheat_FlyingEnabled_5C2C08)
        {
            return 0;
        }
    }
    else if (pWho->field_4_typeId == BaseGameObject::Types::eMudokon_110)
    {
        // For some reason when ddcheat is on muds are also invincible to lasers?
        if (sDDCheat_FlyingEnabled_5C2C08)
        {
            return 0;
        }

        // If mud isn't moving then he is safe.
        if (pWho->field_C4_velx == FP_FromInteger(0) && pWho->field_C8_vely == FP_FromInteger(0))
        {
            return 0;
        }
    }
    else if (FP_GetExponent(pWho->field_C4_velx) == 0 && FP_GetExponent(pWho->field_C8_vely) == 0)
    {
        // Whatever this is isn't moving
        return 0;
    }

    if (!(field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render)))
    {
        // Not being rendered so can't set off the motion beam
        return 0;
    }

    if (pOwner && (pWho->field_4_typeId != BaseGameObject::Types::eMudokon_110 && pWho->field_4_typeId != BaseGameObject::Types::eType_Abe_69))
    {
        // If there is an owner (such as a greeter) then only muds and abe can set off the beam?
        return 0;
    }

    return 1;
}