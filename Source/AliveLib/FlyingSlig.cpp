#include "stdafx.h"
#include "FlyingSlig.hpp"
#include "Function.hpp"
#include "Events.hpp"
#include "Collisions.hpp"
#include "Shadow.hpp"
#include "stdlib.hpp"
#include "Game.hpp"
#include "Math.hpp"
#include "ObjectIds.hpp"
#include "SwitchStates.hpp"
#include "Sfx.hpp"
#include "Abe.hpp"
#include "Map.hpp"
#include "MusicController.hpp"
#include "DDCheat.hpp"
#include "Slig.hpp"
#include "Grenade.hpp"
#include "Dove.hpp"
#include "NakedSlig.hpp"
#include "Particle.hpp"
#include "Gibs.hpp"
#include "Blood.hpp"
#include "GameSpeak.hpp"
#include "Explosion.hpp"
#include "Bullet.hpp"
#include "ParticleBurst.hpp"
#include "Switch.hpp"

ALIVE_ARY(1, 0x5523A0, TFlyingSligFn, 26, sFlyingSlig_motion_table_5523A0,
{
    &FlyingSlig::M_Idle_0_4385E0,
    &FlyingSlig::M_HorizontalMovement_1_4386A0,
    &FlyingSlig::M_IdleToTurn_2_4388B0,
    &FlyingSlig::M_DownMovement_3_438AA0,
    &FlyingSlig::M_DownMovementToTurn_4_438CC0,
    &FlyingSlig::M_UpMovement_5_438DD0,
    &FlyingSlig::M_UpMovementToTurn_6_439030,
    &FlyingSlig::M_LeverPull_7_439150,
    &FlyingSlig::M_GameSpeak_8_4391D0,
    &FlyingSlig::M_Possession_9_434290,
    &FlyingSlig::M_EndHorizontalMovement_10_4387D0,
    &FlyingSlig::M_BeginUpMovement_11_438E40,
    &FlyingSlig::M_HorizontalToDownMovement_12_438B10,
    &FlyingSlig::M_UpToHorizontalMovement_13_438F60,
    &FlyingSlig::M_DownToHorizontalMovement_14_438BF0,
    &FlyingSlig::M_QuickTurn_15_4387F0,
    &FlyingSlig::M_IdleToHorizontalMovement_16_438730,
    &FlyingSlig::M_BeginDownMovement_17_438B80,
    &FlyingSlig::M_EndDownMovement_18_438C90,
    &FlyingSlig::M_DownKnockback_19_4390D0,
    &FlyingSlig::M_UpKnockback_20_439110,
    &FlyingSlig::M_EndUpMovement_21_438EB0,
    &FlyingSlig::M_InstantUpXTurn_22_438EE0,
    &FlyingSlig::M_InstantDownXTurn_23_438F20,
    &FlyingSlig::M_HorizontalToUpMovement_24_438D60,
    &FlyingSlig::M_TurnToHorizontalMovement_25_4389E0,
});

ALIVE_ARY(1, 0x552350, TFlyingSligFn, 18, sFlyingSlig_AI_table_552350,
{
    &FlyingSlig::AI_Inactive_0_4355B0,
    &FlyingSlig::AI_Death_1_4364E0,
    &FlyingSlig::AI_Moving_2_4356D0,
    &FlyingSlig::AI_GetAlerted_3_435750,
    &FlyingSlig::AI_ChasingEnemy_4_435BC0,
    &FlyingSlig::AI_Idle_5_435820,
    &FlyingSlig::AI_GameSpeakToMoving_6_435940,
    &FlyingSlig::AI_PanicMoving_7_435990,
    &FlyingSlig::AI_PanicIdle_8_435AC0,
    &FlyingSlig::AI_SpottedEnemy_9_435E40,
    &FlyingSlig::AI_LaunchingGrenade_10_435F10,
    &FlyingSlig::AI_AbeDead_11_435FD0,
    &FlyingSlig::AI_Possessed_12_436040,
    &FlyingSlig::AI_Possession_13_4360F0,
    &FlyingSlig::AI_DePossession_14_436180,
    &FlyingSlig::AI_FlyingSligSpawn_15_4362C0,
    &FlyingSlig::AI_Death_1_4364E0,
    &FlyingSlig::AI_FromNakedSlig_17_4355E0,
});

const static AIFunctionData<TFlyingSligFn> sFlyingSligAITable[18] =
{
    { &FlyingSlig::AI_Inactive_0_4355B0, 0x401802 , "AI_Inactive_0" },
    { &FlyingSlig::AI_Death_1_4364E0, 0x402ABD , "AI_Death_1 (first)" },
    { &FlyingSlig::AI_Moving_2_4356D0, 0x4046BF, "AI_Moving_2" },
    { &FlyingSlig::AI_GetAlerted_3_435750, 0x402603, "AI_GetAlerted_3" },
    { &FlyingSlig::AI_ChasingEnemy_4_435BC0, 0x402086, "AI_ChasingEnemy_4" },
    { &FlyingSlig::AI_Idle_5_435820, 0x4028A6, "AI_Idle_5" },
    { &FlyingSlig::AI_GameSpeakToMoving_6_435940, 0x403E31, "AI_GameSpeakToMoving_6" },
    { &FlyingSlig::AI_PanicMoving_7_435990, 0x404453 , "AI_PanicMoving_7" },
    { &FlyingSlig::AI_PanicIdle_8_435AC0, 0x4013A2, "AI_PanicIdle_8" },
    { &FlyingSlig::AI_SpottedEnemy_9_435E40, 0x40394A, "AI_SpottedEnemy_9" },
    { &FlyingSlig::AI_LaunchingGrenade_10_435F10, 0x40253B, "AI_LaunchingGrenade_10" },
    { &FlyingSlig::AI_AbeDead_11_435FD0, 0x40469C, "AI_AbeDead_11" },
    { &FlyingSlig::AI_Possessed_12_436040, 0x404480, "AI_Possessed_12" },
    { &FlyingSlig::AI_Possession_13_4360F0, 0x40241E , "AI_Possession_13" },
    { &FlyingSlig::AI_DePossession_14_436180, 0x403DBE, "AI_DePossession_14" },
    { &FlyingSlig::AI_FlyingSligSpawn_15_4362C0, 0x40128A , "AI_FlyingSligSpawn_15" },
    { &FlyingSlig::AI_Death_1_4364E0, 0x402ABD, "AI_Death_1 (second)" },
    { &FlyingSlig::AI_FromNakedSlig_17_4355E0, 0x401749, "AI_FromNakedSlig_17" },
};

void FlyingSlig::SetBrain(TFlyingSligFn fn)
{
    ::SetBrain(fn, field_29C_brain_state, sFlyingSligAITable);
}

bool FlyingSlig::BrainIs(TFlyingSligFn fn)
{
    return ::BrainIs(fn, field_29C_brain_state, sFlyingSligAITable);
}

FlyingSlig* FlyingSlig::ctor_4342B0(Path_FlyingSlig* pTlv, int tlvInfo)
{
    //BaseCtor_4340B0(9); // Omitted for direct call
    ctor_408240(9);

    field_178 = 0;
    field_164 = -1;
    field_17A = -1;

    SetVTable(this, 0x545120);

    if (tlvInfo != -1)
    {
        field_C_objectId = tlvInfo;
    }

    field_4_typeId = Types::eFlyingSlig_54;

    field_10_resources_array.SetAt(0, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kFlySligResID, TRUE, FALSE));
    field_10_resources_array.SetAt(1, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kSligBlowResID, TRUE, FALSE));
    field_10_resources_array.SetAt(2, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kGrenadeResID, TRUE, FALSE));
    field_10_resources_array.SetAt(3, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kSmallExplo2ResID, TRUE, FALSE));
    field_10_resources_array.SetAt(4, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kMetalResID, TRUE, FALSE));
    field_10_resources_array.SetAt(5, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeblowResID, TRUE, FALSE));
    field_10_resources_array.SetAt(6, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kBigflashResID, TRUE, FALSE));
    field_10_resources_array.SetAt(7, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kVaporResID, TRUE, FALSE));
    field_10_resources_array.SetAt(8, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kSlogBlowResID, TRUE, FALSE));

    Animation_Init_424E10(
        116888,
        107,
        48u,
        field_10_resources_array.ItemAt(0),
        1,
        1u);

    field_15E = 0;

    field_20_animation.field_1C_fn_ptr_array = kFlyingSlig_Anim_Frames_Fns_55EFC4;

    field_114_flags.Set(Flags_114::e114_Bit3_Can_Be_Possessed);
    field_114_flags.Set(Flags_114::e114_Bit6_SetOffExplosives);

    field_6_flags.Set(BaseGameObject::eCanExplode);

    field_14C_timer = 0;
    field_DC_bApplyShadows |= 2u;

    field_15C_voice_pitch_min = 45 * ((Math_NextRandom() % 5) - 2);

    field_150_grenade_delay = 0;
    field_154 = 0;

    field_17E_flags.Clear(Flags_17E::eBit1_Speaking_flag1);
    field_17E_flags.Clear(Flags_17E::eBit5_Throw);
    field_17E_flags.Clear(Flags_17E::eBit6);
    field_17E_flags.Clear(Flags_17E::eBit7_DoAction);
    field_17E_flags.Clear(Flags_17E::eBit8);
    field_17E_flags.Clear(Flags_17E::eBit9_Chanting);
    field_17E_flags.Clear(Flags_17E::eBit10_Speaking_flag2);

    field_158_obj_id = -1;

    field_288 = 0;
    field_290 = 0;
    field_284 = FP_FromInteger(0);
    field_28C = 0;
    field_1E8 = 0;
    field_184_xSpeed = FP_FromInteger(0);
    field_188_ySpeed = FP_FromInteger(0);
    field_190 = FP_FromInteger(0);

    field_C4_velx = FP_FromInteger(0);
    field_C8_vely = FP_FromInteger(0);

    field_118_data = *pTlv;

    field_148_tlvInfo = tlvInfo;

    SetBrain(&FlyingSlig::AI_Inactive_0_4355B0);

    field_106_current_motion = eFlyingSligMotions::M_Idle_0_4385E0;

    if (field_118_data.field_10_data.field_2_state == 1)
    {
        field_14C_timer = sGnFrame_5C1B84 + field_118_data.field_10_data.field_4_hi_pause_time;
    }
    else if (field_118_data.field_10_data.field_2_state == 0)
    {
        field_14C_timer = sGnFrame_5C1B84 + 1;
    }

    field_2A8_max_x_speed = FP_FromInteger(field_118_data.field_10_data.field_1A_max_velocity) * field_CC_sprite_scale;
    field_2AC_up_vel = FP_FromInteger(-field_118_data.field_10_data.field_1A_max_velocity) * field_CC_sprite_scale;
    field_2B0_down_vel = FP_FromInteger(field_118_data.field_10_data.field_1A_max_velocity) * field_CC_sprite_scale;
    field_2B4_max_slow_down = FP_FromDouble(0.4) * field_CC_sprite_scale;
    field_2B8_max_speed_up = FP_FromDouble(0.4) * field_CC_sprite_scale;

    field_20_animation.field_4_flags.Set(AnimFlags::eBit5_FlipX, field_118_data.field_10_data.field_A_direction == 0);

    if (field_118_data.field_10_data.field_0_scale == 1)
    {
        field_CC_sprite_scale = FP_FromDouble(0.5);
        field_20_animation.field_C_render_layer = 14;
        field_D6_scale = 0;
    }
    else
    {
        field_CC_sprite_scale = FP_FromInteger(1);
        field_20_animation.field_C_render_layer = 33;
        field_D6_scale = 1;
    }

    field_17E_flags.Set(Flags_17E::eBit13_Persistant, field_118_data.field_10_data.field_1E_persistant & 1);

    field_17C_launch_id |= field_118_data.field_10_data.field_1C_launch_id;

    field_B8_xpos = FP_FromInteger((pTlv->field_8_top_left.field_0_x + pTlv->field_C_bottom_right.field_0_x) / 2);
    field_BC_ypos = FP_FromInteger(pTlv->field_8_top_left.field_2_y);

    FP hitX = {};
    FP hitY = {};
    sCollisions_DArray_5C1128->Raycast_417A60(
        FP_FromInteger(pTlv->field_8_top_left.field_0_x),
        FP_FromInteger(pTlv->field_8_top_left.field_2_y),
        FP_FromInteger(pTlv->field_C_bottom_right.field_0_x),
        FP_FromInteger(pTlv->field_C_bottom_right.field_2_y),
        &field_100_pCollisionLine,
        &hitX,
        &hitY,
        0x100);

    if (field_100_pCollisionLine)
    {
        field_B8_xpos = FP_FromInteger(field_100_pCollisionLine->field_0_rect.x);
        field_BC_ypos = FP_FromInteger(field_100_pCollisionLine->field_0_rect.y);
        sub_4348A0();
        field_194 = FP_FromInteger(0);
    }

    field_1D8 = 0;
    field_1DC = 0;
    field_1E0 = 0;
    field_1E4 = 0;

    field_E0_pShadow = alive_new<Shadow>();
    if (field_E0_pShadow)
    {
        field_E0_pShadow->ctor_4AC990();
    }
    return this;
}

void FlyingSlig::dtor_434990()
{
    SetVTable(this, 0x545120);

    if (sControlledCharacter_5C1B8C == this)
    {
        sControlledCharacter_5C1B8C = sActiveHero_5C1B68;
        MusicController::sub_47FD60(0, this, 0, 0);
        if (gMap_5C3030.field_A_5C303A_levelId != LevelIds::eMenu_0)
        {
            gMap_5C3030.SetActiveCam_480D30(
                field_2A0_abe_level,
                field_2A2_abe_path,
                field_2A4_abe_camera, 
                CameraSwapEffects::eEffect0_InstantChange,
                0,
                0);
        }
    }

    Path_TLV* pTlv = sPath_dword_BB47C0->TLV_From_Offset_Lvl_Cam_4DB770(field_148_tlvInfo);
    if (pTlv)
    {
        if (pTlv->field_4_type != TlvTypes::SligGetWings_105 && pTlv->field_4_type != TlvTypes::FlyingSligSpawner_92)
        {
            if (field_10C_health <= FP_FromInteger(0))
            {
                Path::TLV_Reset_4DB8E0(field_148_tlvInfo, -1, 0, 1);
            }
            else
            {
                Path::TLV_Reset_4DB8E0(field_148_tlvInfo, -1, 0, 0);
            }
        }
    }

    BaseAliveGameObject::dtor_4080B0();
}

FlyingSlig* FlyingSlig::vdtor_434870(signed int flags)
{
    dtor_434990();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
    return this;
}

void FlyingSlig::vScreenChanged_434C10()
{
    if (gMap_5C3030.sCurrentLevelId_5C3030 != gMap_5C3030.field_A_5C303A_levelId ||
        gMap_5C3030.field_22 != gMap_5C3030.Get_Path_Unknown_480710() ||
        gMap_5C3030.sCurrentPathId_5C3032 != gMap_5C3030.field_C_5C303C_pathId &&
        (this != sControlledCharacter_5C1B8C ||
        field_17E_flags.Get(Flags_17E::eBit13_Persistant)))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }
}

void FlyingSlig::vUpdate_434AD0()
{
    if (field_114_flags.Get(Flags_114::e114_Bit9))
    {
        field_114_flags.Clear(Flags_114::e114_Bit9);

        if (!IsPossessed_436A90())
        {
            if (field_104_collision_line_type != -1)
            {
                const FP savedNextXPos = field_294_nextXPos;
                const FP savedNextYPos = field_298_nextYPos;
                field_100_pCollisionLine = sCollisions_DArray_5C1128->Get_Line_At_Idx_418070(field_104_collision_line_type);
                sub_4348A0();
                field_294_nextXPos = savedNextXPos;
                field_298_nextYPos = savedNextYPos;
            }
        }

        if (field_158_obj_id != -1)
        {
            for (int i = 0; i < gBaseGameObject_list_BB47C4->Size(); i++)
            {
                BaseGameObject* pObj = gBaseGameObject_list_BB47C4->ItemAt(i);
                if (!pObj)
                {
                    break;
                }

                if (pObj->field_C_objectId == field_158_obj_id)
                {
                    field_158_obj_id = pObj->field_8_object_id;
                    break;
                }
            }
        }
    }

    if (Event_Get_422C00(kEventDeathReset))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }
    else
    {
        field_B8_xpos = field_294_nextXPos;
        field_BC_ypos = field_298_nextYPos;

        const auto oldBrain = field_29C_brain_state;

        (this->*(field_29C_brain_state))();

        (this->*(sFlyingSlig_motion_table_5523A0)[field_106_current_motion])();

        if (oldBrain != field_29C_brain_state)
        {
            LOG_INFO("FlyingSlig: Old brain = " << GetOriginalFn(oldBrain, sFlyingSligAITable).fnName << " new brain = " << GetOriginalFn(field_29C_brain_state, sFlyingSligAITable).fnName);
            //LOG_INFO("FlyingSlig: Old motion = " << oldMotion << " new motion = " << field_106_current_motion);
        }

        Movement_4396E0();
    }
}

void FlyingSlig::sub_4348A0()
{
    field_17E_flags.Clear(Flags_17E::eBit3);
    field_17E_flags.Clear(Flags_17E::eBit2);
    field_298_nextYPos = field_BC_ypos;
    field_294_nextXPos = field_B8_xpos;
    field_18C = FP_FromInteger(0);
    field_190 = FP_FromInteger(0);
    sub_437C70(field_100_pCollisionLine);
    const short v5 = FP_GetExponent(field_BC_ypos - field_1A4_rect.y);
    const short v6 = FP_GetExponent(field_B8_xpos - field_1A4_rect.x);
    field_194 = FP_FromInteger(Math_SquareRoot_Int_496E70(v5 * v5 + v6 * v6));
    field_17E_flags.Set(Flags_17E::eBit4, field_118_data.field_10_data.field_A_direction == 0);
}

const int dword_552500[9] =
{
    -163840,
    -245760,
    -286720,
    -327680,
    -286720,
    -245760,
    -163840,
    -65536,
    65535999
};

const int dword_552524[11] =
{
    74785,
    85101,
    79944,
    59312,
    23209,
    -34563,
    -82422,
    -98373,
    -82422,
    -34563,
    65535999
};

const int dword_552550[11] =
{
    38603,
    84930,
    84928,
    38605,
    -187040,
    -344791,
    -178048,
    70049,
    100043,
    38273,
    65535999
};



ALIVE_ARY(1, 0x55257C, const int*, 3, dword_55257C, { dword_552500, dword_552524, dword_552550 });

void FlyingSlig::Movement_4396E0()
{
    if (!IsPossessed_436A90())
    {
        if (field_190 > FP_FromInteger(0))
        {
            if (field_18C + field_190 > field_2A8_max_x_speed)
            {
                field_18C = field_2A8_max_x_speed;
            }
            else
            {
                field_18C = field_18C + field_190;
            }
        }
        else if (field_190 < FP_FromInteger(0))
        {
            if (field_18C + field_190 < -field_2A8_max_x_speed)
            {
                field_18C = -field_2A8_max_x_speed;
            }
            else
            {
                field_18C += field_190;
            }
        }
        else if (field_190 == FP_FromInteger(0))
        {
            if (field_18C >= -field_2B4_max_slow_down)
            {
                if (field_18C <= field_2B4_max_slow_down)
                {
                    field_18C = FP_FromInteger(0);
                }
                else
                {
                    field_18C = field_18C - field_2B4_max_slow_down;
                }
            }
            else
            {
                field_18C = field_2B4_max_slow_down + field_18C;
            }
        }

        FP_Point posXY = {};
        sub_437AC0(field_18C, &posXY);
        field_C4_velx = posXY.field_0_x - field_B8_xpos;
        field_C8_vely = posXY.field_4_y - field_BC_ypos;
    }
    else
    {
        const int v4 = Math_SquareRoot_Int_496E70(FP_GetExponent((field_C8_vely * field_C8_vely) + (field_C4_velx * field_C4_velx)));
        if (FP_Abs(FP_FromInteger(v4)) > FP_FromDouble(0.05))
        {
            field_C4_velx = field_C4_velx - ((field_C4_velx / FP_FromInteger(v4)) * field_2B4_max_slow_down) + field_184_xSpeed;
            field_C8_vely = field_C8_vely - ((field_C8_vely / FP_FromInteger(v4)) * field_2B4_max_slow_down) + field_188_ySpeed;
        }
        else
        {
            if (field_184_xSpeed != FP_FromInteger(0) || field_188_ySpeed != FP_FromInteger(0))
            {
                field_C4_velx += field_184_xSpeed;
                field_C8_vely = field_C8_vely + field_188_ySpeed;
            }
            else
            {
                field_C4_velx = FP_FromInteger(0);
                field_C8_vely = FP_FromInteger(0);
            }
        }

        const FP v15 = FP_FromInteger(Math_SquareRoot_Int_496E70(FP_GetExponent((field_C8_vely * field_C8_vely) + (field_C4_velx * field_C4_velx))));
        if (v15 > field_2A8_max_x_speed)
        {
            field_C4_velx = ((field_C4_velx / v15) * field_2A8_max_x_speed);
            field_C8_vely = ((field_C8_vely / v15) * field_2A8_max_x_speed);
        }

        if (field_C8_vely < FP_FromInteger(0))
        {
            if (CollisionUp_43A640(field_C8_vely))
            {
                field_C8_vely = -field_C8_vely;
            }
        }
        
        if (field_C8_vely > FP_FromInteger(0))
        {
            if (CollisionDown_43A9E0(field_C8_vely))
            {
                field_C8_vely = -field_C8_vely;
            }
        }

        if (field_C4_velx != FP_FromInteger(0))
        {
            if (CollisionLeftRight_43AC80(field_C4_velx))
            {
                field_C4_velx = -field_C4_velx;
            }
        }
    }

    field_B8_xpos += field_C4_velx;
    field_BC_ypos += field_C8_vely;

    sub_408C40();

    if (field_17E_flags.Get(Flags_17E::eBit5_Throw))
    {
        if (static_cast<int>(sGnFrame_5C1B84) > field_150_grenade_delay &&
            (
                field_114_flags.Get(Flags_114::e114_Bit4_bPossesed) ||
                SwitchStates_Get_466020(field_17C_launch_id) ||
                field_114_flags.Get(Flags_114::e114_Bit4_bPossesed)
            ) &&
            CanThrowGrenade_43A490())
        {
            ThrowGrenade_43A1E0();
        }
    }

    if (field_17E_flags.Get(Flags_17E::eBit10_Speaking_flag2))
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_GameSpeak_8_4391D0);
    }

    if (field_17E_flags.Get(Flags_17E::eBit6))
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_IdleToTurn_2_4388B0);
    }

    if (field_17E_flags.Get(Flags_17E::eBit7_DoAction))
    {
        if (field_106_current_motion == eFlyingSligMotions::M_Idle_0_4385E0)
        {
            TryPullLever_439DB0();
        }
    }

    field_294_nextXPos = field_B8_xpos;
    field_298_nextYPos = field_BC_ypos;

    field_BC_ypos += field_CC_sprite_scale * FP_FromInteger(20);

    if (field_28C)
    {
        if (field_28C >= 3)
        {
            ALIVE_FATAL("FlyingSlig array out of bounds");
        }
        const FP* pTable = reinterpret_cast<const FP*>(dword_55257C[field_28C]); // TODO: Type conversion !!
        field_288 = pTable;
        field_284 = pTable[field_290];
        if (field_284 <= FP_FromInteger(990))
        {
            field_290++;
        }
        else
        {
            field_284 = FP_FromInteger(0);
            field_28C = 0;
            field_290 = 0;
        }
        field_BC_ypos = field_BC_ypos + field_284;
    }
    else
    {
        if (field_284 != FP_FromInteger(0))
        {
            if (field_284 <= FP_FromInteger(0))
            {
                if (field_284 <= FP_FromInteger(-1))
                {
                    field_284 = field_284 + FP_FromInteger(1);
                }
                else
                {
                    field_284 = FP_FromInteger(0);
                }
            }
            else if (field_284 < FP_FromInteger(1))
            {
                field_284 = FP_FromInteger(0);
            }
            else
            {
                field_284 = field_284 - FP_FromInteger(1);
            }
            field_BC_ypos = field_BC_ypos + field_284;
        }
    }

    int v37 = {};
    if (Math_Distance_496EB0(0, 0, FP_GetExponent(field_C4_velx), FP_GetExponent(field_C8_vely)) >= 0)
    {
        v37 = Math_Distance_496EB0(0, 0, FP_GetExponent(field_C4_velx), FP_GetExponent(field_C8_vely));
    }
    else
    {
        v37 = -Math_Distance_496EB0(0, 0, FP_GetExponent(field_C4_velx), FP_GetExponent(field_C8_vely));
    }

    const int v38 = static_cast<int>(sGnFrame_5C1B84) % ((FP_FromInteger(v37) < field_2A8_max_x_speed) + 2);
    if (!v38 && field_10C_health > FP_FromInteger(0))
    {
        Slig_SoundEffect_4BFFE0((Math_NextRandom() % 3) ? 10 : 9, this);
    }

    field_17E_flags.Clear(Flags_17E::eBit5_Throw);
    field_17E_flags.Clear(Flags_17E::eBit6);
    field_17E_flags.Clear(Flags_17E::eBit7_DoAction);
    field_17E_flags.Clear(Flags_17E::eBit10_Speaking_flag2);

    field_184_xSpeed = FP_FromInteger(0);
    field_188_ySpeed = FP_FromInteger(0);

    field_190 = FP_FromInteger(0);
}

__int16 FlyingSlig::vTakeDamage_434C90(BaseGameObject* pFrom)
{
    switch (pFrom->field_4_typeId)
    {
    case Types::eBullet_15:
    {
        if (static_cast<Bullet*>(pFrom)->field_20_type == BulletType::Type_3)
        {
            PSX_RECT bRect = {};
            vGetBoundingRect_424FD0(&bRect, 1);
            Path_TLV* pTlv = nullptr;
            do
            {
                pTlv = sPath_dword_BB47C0->TLV_Get_At_4DB290(pTlv,
                    field_B8_xpos,
                    FP_FromInteger(bRect.y),
                    field_B8_xpos,
                    FP_FromInteger(bRect.y));

                if (pTlv->field_4_type == TlvTypes::ZSligCover_50)
                {
                    // Left/right in cover
                    if (bRect.x >= pTlv->field_8_top_left.field_0_x &&
                        bRect.x <= pTlv->field_C_bottom_right.field_0_x &&
                        bRect.y >= pTlv->field_8_top_left.field_2_y &&
                        bRect.y <= pTlv->field_C_bottom_right.field_2_y)
                    {
                        // Top/bottom in cover
                        if (bRect.w >= pTlv->field_8_top_left.field_0_x &&
                            bRect.w <= pTlv->field_C_bottom_right.field_0_x &&
                            bRect.h >= pTlv->field_8_top_left.field_2_y &&
                            bRect.h <= pTlv->field_C_bottom_right.field_2_y)
                        {
                            return 0;
                        }
                    }
                }
            } while (pTlv);
        }
        // Not in Z-Cover, fall through and be shot
    }
    case Types::eGrinder_30:
    case Types::eRockSpawner_48:
    case Types::eAbe_69:
    case Types::eType_86:
    case Types::eMineCar_89:
    case Types::eType_107:
    case Types::eSlog_126:
    {
        if (BrainIs(&FlyingSlig::AI_Death_1_4364E0))
        {
            return 1;
        }
        BlowUp_436510();
        auto pExplosion = alive_new<Explosion>();
        if (!pExplosion)
        {
            return 1;
        }
        pExplosion->ctor_4A1200(field_B8_xpos, field_BC_ypos - (field_CC_sprite_scale * FP_FromInteger(5)), field_CC_sprite_scale, 1);
        return 1;
    }

    case Types::eElectricWall_39:
        Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Help_10, 0, field_15C_voice_pitch_min, this);
        break;

    case Types::eBaseBomb_46:
    case Types::eExplosion_109:
        if (!BrainIs(&FlyingSlig::AI_Death_1_4364E0))
        {
            BlowUp_436510();
        }
        break;

    case Types::eElectrocute_150:
        if (!BrainIs(&FlyingSlig::AI_Death_1_4364E0))
        {
            field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
            field_10C_health = FP_FromInteger(0);
            SetBrain(&FlyingSlig::AI_Death_1_4364E0);
            field_14C_timer = sGnFrame_5C1B84;
        }
        break;

    default:
        return 1;
    }
    return 1;
}

void FlyingSlig::AI_Inactive_0_4355B0()
{
    if (static_cast<int>(sGnFrame_5C1B84) >= field_14C_timer)
    {
        ToMoving_435720();
    }
}

void FlyingSlig::AI_Death_1_4364E0()
{
    if (static_cast<int>(sGnFrame_5C1B84) >= field_14C_timer)
    {
        field_6_flags.Set(BaseGameObject::eDead);
        Event_Broadcast_422BC0(kEventMudokonComfort, this);
    }
}

void FlyingSlig::AI_Moving_2_4356D0()
{
    if (!sub_436730() && sub_4374A0(1) == 1)
    {
        field_17E_flags.Toggle(Flags_17E::eBit4);
        PatrolDelay_435860();
    }
}

void FlyingSlig::AI_GetAlerted_3_435750()
{
    if (field_106_current_motion != eFlyingSligMotions::M_Idle_0_4385E0)
    {
        field_14C_timer++;
    }
    else if (vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
    {
        if (!sub_436730() && static_cast<int>(sGnFrame_5C1B84) >= field_14C_timer)
        {
            ToMoving_435720();
        }
    }
    else
    {
        field_17E_flags.Set(Flags_17E::eBit6);
        field_14C_timer++;
    }
}

void FlyingSlig::AI_ChasingEnemy_4_435BC0()
{
    field_17E_flags.Clear(Flags_17E::eBit3);

    if (Event_Get_422C00(kEventHeroDying) &&
        gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
    {
        ToAbeDead_436010();
        return;
    }

    if (Event_Get_422C00(kEventResetting) ||
        sControlledCharacter_5C1B8C->field_CC_sprite_scale != field_CC_sprite_scale ||
        IsInInvisibleZone_425710(sControlledCharacter_5C1B8C)||
        sControlledCharacter_5C1B8C->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible) ||
        !IsWallBetween_43A550(this, sControlledCharacter_5C1B8C) &&
        (sControlledCharacter_5C1B8C != sActiveHero_5C1B68 || sActiveHero_5C1B68->field_106_current_motion != eAbeStates::State_65_LedgeAscend_End_4548E0) &&
        sControlledCharacter_5C1B8C->field_4_typeId != Types::eMineCar_89)
    {
        PatrolDelay_435860();
        return;
    }

    if (sub_436C60(&field_100_pCollisionLine->field_0_rect, 1))
    {
        if (FP_Abs(field_194 - field_1C4) < (FP_FromInteger(15) * field_CC_sprite_scale))
        {
            ToLaunchingGrenade_435F50();
            return;
        }

        field_17E_flags.Set(Flags_17E::eBit4, field_1C4 > field_194);
        field_17E_flags.Set(Flags_17E::eBit3);

        if (static_cast<int>(sGnFrame_5C1B84) > field_150_grenade_delay && CanThrowGrenade_43A490())
        {
            if (vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
            {
                if (!(Math_NextRandom() & 15))
                {
                    ToLaunchingGrenade_435F50();
                    return;
                }
            }
        }
    }
    else if (!sub_436B20())
    {
        sub_4373B0();
    }

    sub_4374A0(0);
}

void FlyingSlig::AI_Idle_5_435820()
{
    if (!sub_436730() && static_cast<int>(sGnFrame_5C1B84) >= field_14C_timer)
    {
        ToMoving_435720();
    }
}

void FlyingSlig::AI_GameSpeakToMoving_6_435940()
{
    if (field_106_current_motion != eFlyingSligMotions::M_GameSpeak_8_4391D0)
    {
        ToMoving_435720();
    }
}

void FlyingSlig::AI_PanicMoving_7_435990()
{
    if (CanChase_436850(sControlledCharacter_5C1B8C))
    {
        ToChase_435E10();
        return;
    }

    if (!Event_Is_Event_In_Range_422C30(kEventAbeOhm, field_B8_xpos, field_BC_ypos, field_D6_scale))
    {
        ToMoving_435720();
        return;
    }

    if (static_cast<int>(sGnFrame_5C1B84) < field_14C_timer)
    {
        if (sub_4374A0(0) != 1)
        {
            return;
        }
        field_17E_flags.Toggle(Flags_17E::eBit4);
    }

    ToPanicIdle_435B50();
}

void FlyingSlig::AI_PanicIdle_8_435AC0()
{
    if (CanChase_436850(sControlledCharacter_5C1B8C))
    {
        ToChase_435E10();
    }
    else if (Event_Is_Event_In_Range_422C30(kEventAbeOhm, field_B8_xpos, field_BC_ypos, field_D6_scale))
    {
        if (static_cast<int>(sGnFrame_5C1B84) >= field_14C_timer && field_106_current_motion != eFlyingSligMotions::M_GameSpeak_8_4391D0)
        {
            ToPanicMoving_435A50();
        }
    }
    else
    {
        ToMoving_435720();
    }
}

void FlyingSlig::AI_SpottedEnemy_9_435E40()
{
    if (static_cast<int>(sGnFrame_5C1B84) >= field_14C_timer)
    {
        ToChase_435E10();
    }
}

void FlyingSlig::AI_LaunchingGrenade_10_435F10()
{
    if (vIsFacingMe_4254A0(sControlledCharacter_5C1B8C))
    {
        field_17E_flags.Set(Flags_17E::eBit5_Throw);
    }
    ToChase_435E10();
}

void FlyingSlig::AI_AbeDead_11_435FD0()
{
    if (static_cast<int>(sGnFrame_5C1B84) == field_14C_timer - 45)
    {
        Say_436A50(SligSpeak ::GotYa_12, 0);
    }
    else if (static_cast<int>(sGnFrame_5C1B84) == field_14C_timer)
    {
        Say_436A50(SligSpeak::Laugh_3, 0);
    }
}

void FlyingSlig::AI_Possessed_12_436040()
{
    if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
    {
        MusicController::sub_47FD60(9, this, 0, 0);
    }

    if (!field_17E_flags.Get(Flags_17E::eBit9_Chanting))
    {
        if (Input_IsChanting_45F260())
        {
            ToChantShake_436270();
        }
    }

    if (!Input_IsChanting_45F260())
    {
        field_17E_flags.Clear(Flags_17E::eBit9_Chanting);
    }

    HandlePlayerControls_439340();
}

void FlyingSlig::AI_Possession_13_4360F0()
{
    if (static_cast<int>(sGnFrame_5C1B84) > field_14C_timer)
    {
        Say_436A50(SligSpeak ::Hi_0, 0x1FF);
        ToPlayerControlled_4360C0();
    }
}

void FlyingSlig::AI_DePossession_14_436180()
{
    if (!Input_IsChanting_45F260())
    {
        ToPlayerControlled_4360C0();
        return;
    }

    if (static_cast<int>(sGnFrame_5C1B84) <= field_14C_timer)
    {
        if (!(static_cast<int>(sGnFrame_5C1B84) % 4))
        {
            const FP xOff = (field_CC_sprite_scale * FP_FromInteger(Math_RandomRange_496AB0(-20, 20) + field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX) ? -10 : 10));
            const FP yOff = (field_CC_sprite_scale * FP_FromInteger(Math_RandomRange_496AB0(-20, 10)));
            New_Chant_Particle_426BE0(
                xOff + field_B8_xpos,
                yOff + field_BC_ypos,
                field_CC_sprite_scale, 0);
        }
    }
    else
    {
        BlowUp_436510();
    }
}

void FlyingSlig::AI_FlyingSligSpawn_15_4362C0()
{
    if (sControlledCharacter_5C1B8C == this && field_10C_health > FP_FromInteger(0))
    {
        MusicController::sub_47FD60(9, this, 0, 0);
    }

    if (FP_Abs(field_B8_xpos - field_1C8) >= FP_FromInteger(1) ||
        FP_Abs(field_BC_ypos - field_1CC) >= FP_FromInteger(1))
    {
        const FP delta1 = field_1C8 - field_B8_xpos;
        const FP delta2 = field_1CC - field_BC_ypos;

        if (FP_Abs(field_1C8 - field_B8_xpos) <= FP_FromInteger(2))
        {
            field_B8_xpos = field_1C8;
        }
        else if (delta1 >= FP_FromInteger(2))
        {
            field_B8_xpos += FP_FromInteger(2);
        }
        else
        {
            field_B8_xpos -= FP_FromInteger(2);
        }

        if (FP_Abs(field_1CC - field_BC_ypos) <= FP_FromInteger(2))
        {
            field_BC_ypos = field_1CC;
        }
        else if (delta2 >= FP_FromInteger(2))
        {
            field_BC_ypos += FP_FromInteger(2);
        }
        else
        {
            field_BC_ypos -= FP_FromInteger(2);
        }

        if ((FP_Abs(field_B8_xpos - field_1C8) < FP_FromInteger(1)) && (FP_Abs(field_BC_ypos - field_1CC) < FP_FromInteger(1)))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_LeverPull_7_439150);
        }
    }
    else if (field_106_current_motion == eFlyingSligMotions::M_Idle_0_4385E0)
    {
        ToPlayerControlled_4360C0();
    }
}

void FlyingSlig::AI_FromNakedSlig_17_4355E0()
{
    FP hitX = {};
    FP hitY = {};
    if (sCollisions_DArray_5C1128->Raycast_417A60(
        field_B8_xpos,
        field_BC_ypos,
        field_B8_xpos,
        field_BC_ypos - FP_FromInteger(5),
        &field_100_pCollisionLine,
        &hitX,
        &hitY,
        0x100) == 1)
    {
        field_B8_xpos = hitX;
        field_BC_ypos = hitY;
        sub_4348A0();
        field_C8_vely = FP_FromInteger(0);
        field_C4_velx = FP_FromInteger(0);
        field_188_ySpeed = FP_FromInteger(0);
        field_184_xSpeed = FP_FromInteger(0);
        PatrolDelay_435860();
    }
    else
    {
        field_C4_velx = FP_FromInteger(0);
        field_C8_vely = FP_FromDouble(-4.5);
        field_184_xSpeed = FP_FromInteger(0);
        field_188_ySpeed = FP_FromDouble(-0.5);
    }

}

void FlyingSlig::M_Idle_0_4385E0()
{
    if (!field_28C)
    {
        field_28C = 2;
        field_290 = 0;
    }

    if (field_184_xSpeed != FP_FromInteger(0))
    {
        if (sub_43A510())
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_IdleToHorizontalMovement_16_438730);
            field_28C = 1;
            field_290 = 0;
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_IdleToTurn_2_4388B0);
        }
    }
    else
    {
        if (field_188_ySpeed > FP_FromInteger(0))
        {
            if (field_188_ySpeed >= FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_BeginDownMovement_17_438B80);
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_BeginUpMovement_11_438E40);
            }
        }
    }
}

void FlyingSlig::M_HorizontalMovement_1_4386A0()
{
    if (field_188_ySpeed < FP_FromInteger(0))
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToUpMovement_24_438D60);
    }
    else if (field_188_ySpeed > FP_FromInteger(0))
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToDownMovement_12_438B10);
    }
    else if (field_184_xSpeed == FP_FromInteger(0))
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_EndHorizontalMovement_10_4387D0);
    }
    else if (!sub_43A510())
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_QuickTurn_15_4387F0);
        field_28C = 3;
        field_290 = 0;
    }
}

void FlyingSlig::M_IdleToTurn_2_4388B0()
{
    if (field_20_animation.field_92_current_frame == 4)
    {
        if (field_184_xSpeed != FP_FromInteger(0))
        {
            field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
            if (field_188_ySpeed >= FP_FromInteger(0))
            {
                if (field_188_ySpeed <= FP_FromInteger(0))
                {
                    if (sub_43A510())
                    {
                        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
                        VSetMotion_4081C0(eFlyingSligMotions::M_TurnToHorizontalMovement_25_4389E0);
                    }
                    else
                    {
                        VSetMotion_4081C0(eFlyingSligMotions::M_QuickTurn_15_4387F0);
                    }
                }
                else
                {
                    VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToDownMovement_12_438B10);
                    field_28C = 0;
                }
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToUpMovement_24_438D60);
                field_28C = 0;
            }
        }
    }
    else if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
        if (field_188_ySpeed >= FP_FromInteger(0))
        {
            if (field_188_ySpeed <= FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_Idle_0_4385E0);
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_BeginDownMovement_17_438B80);
            }
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_BeginUpMovement_11_438E40);
        }
    }
}

void FlyingSlig::M_DownMovement_3_438AA0()
{
    if (field_184_xSpeed == FP_FromInteger(0) || sub_43A510())
    {
        if (field_188_ySpeed <= FP_FromInteger(0))
        {
            if (field_184_xSpeed != FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_DownToHorizontalMovement_14_438BF0);
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_EndDownMovement_18_438C90);
            }
        }
    }
    else
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_DownMovementToTurn_4_438CC0);
    }
}

void FlyingSlig::M_DownMovementToTurn_4_438CC0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);

        if (field_184_xSpeed == FP_FromInteger(0) || sub_43A510())
        {
            if (field_188_ySpeed > FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_DownMovement_3_438AA0);
            }
            else if (field_184_xSpeed != FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_DownToHorizontalMovement_14_438BF0);
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_EndDownMovement_18_438C90);
            }
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_DownMovementToTurn_4_438CC0);
        }
    }
}

void FlyingSlig::M_UpMovement_5_438DD0()
{
    if (field_184_xSpeed == FP_FromInteger(0) || sub_43A510())
    {
        if (field_188_ySpeed >= FP_FromInteger(0))
        {
            if (field_184_xSpeed != FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_UpToHorizontalMovement_13_438F60);
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_EndUpMovement_21_438EB0);
            }
        }
    }
    else
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_UpMovementToTurn_6_439030);
    }
}

void FlyingSlig::M_UpMovementToTurn_6_439030()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);

        if (field_184_xSpeed == FP_FromInteger(0) || sub_43A510())
        {
            if (field_188_ySpeed < FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_UpMovement_5_438DD0);
            }
            else if (field_184_xSpeed != FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_UpToHorizontalMovement_13_438F60);
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_EndUpMovement_21_438EB0);
            }
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_UpMovementToTurn_6_439030);
        }
    }
}

void FlyingSlig::M_LeverPull_7_439150()
{
    if (field_20_animation.field_92_current_frame)
    {
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_Idle_0_4385E0);
        }
    }
    else
    {
        auto pSwitch = static_cast<Switch*>(sObjectIds_5C1B70.Find_449CF0(field_158_obj_id));
        if (pSwitch)
        {
            pSwitch->Vsub_4D6050(field_B8_xpos < pSwitch->field_B8_xpos);
        }
        field_158_obj_id = -1;
    }
}

void FlyingSlig::M_GameSpeak_8_4391D0()
{
    if (field_20_animation.field_92_current_frame == 1 && field_17E_flags.Get(Flags_17E::eBit1_Speaking_flag1))
    {
        field_17E_flags.Clear(Flags_17E::eBit1_Speaking_flag1);

        if (BrainIs(&FlyingSlig::AI_Possessed_12_436040))
        {
            switch (field_17D_next_speak)
            {
            case SligSpeak::Hi_0:
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::Slig_Hi_27);
                break;
            case SligSpeak::HereBoy_1:
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::Slig_HereBoy_28);
                break;
            case SligSpeak::GetEm_2:
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::Slig_GetEm_29);
                break;
            case SligSpeak::Laugh_3:
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::Slig_Laugh_8);
                break;
            case SligSpeak::Bullshit_5:
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::Slig_BS_5);
                break;
            case SligSpeak::LookOut_6:
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::Slig_LookOut_6);
                break;
            case SligSpeak::Bullshit2_7:
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::Slig_BS2_7);
                break;
            case SligSpeak::Freeze_8:
                pEventSystem_5BC11C->PushEvent_4218D0(GameSpeakEvents::Slig_Freeze_31);
                break;
            default:
                break;
            }
        }
        Sfx_Slig_GameSpeak_4C04F0(field_17D_next_speak, 0, field_160_voice_pitch_min, this);
        Event_Broadcast_422BC0(kEventSpeaking, this);
    }
    else if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        this->VSetMotion_4081C0(eFlyingSligMotions::M_Idle_0_4385E0);
    }
}

void FlyingSlig::M_Possession_9_434290()
{
    NOT_IMPLEMENTED();
}

void FlyingSlig::M_EndHorizontalMovement_10_4387D0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_Idle_0_4385E0);
    }
}

void FlyingSlig::M_BeginUpMovement_11_438E40()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_184_xSpeed > FP_FromInteger(0))
        {
            if (!sub_43A510())
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_UpMovementToTurn_6_439030);
                return;
            }
        }
        else if (field_188_ySpeed >= FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_EndUpMovement_21_438EB0);
            return;
        }
        VSetMotion_4081C0(eFlyingSligMotions::M_UpMovement_5_438DD0);
    }
}

void FlyingSlig::M_HorizontalToDownMovement_12_438B10()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_184_xSpeed != FP_FromInteger(0))
        {
            if (!sub_43A510())
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_DownMovementToTurn_4_438CC0);
                return;
            }
        }
        else if (field_188_ySpeed <= FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_EndDownMovement_18_438C90);
            return;
        }
        VSetMotion_4081C0(eFlyingSligMotions::M_DownMovement_3_438AA0);
    }
}

void FlyingSlig::M_UpToHorizontalMovement_13_438F60()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_188_ySpeed <= FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalMovement_1_4386A0);
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToDownMovement_12_438B10);
        }
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (field_188_ySpeed > FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToDownMovement_12_438B10);
                field_28C = 0;
            }
            else if (field_188_ySpeed < FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToUpMovement_24_438D60);
                field_28C = 0;
            }
            else if (field_184_xSpeed == FP_FromInteger(0))
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_EndHorizontalMovement_10_4387D0);
            }
            else if (sub_43A510())
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalMovement_1_4386A0);
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_QuickTurn_15_4387F0);
            }
        }
    }
}

void FlyingSlig::M_DownToHorizontalMovement_14_438BF0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_188_ySpeed >= FP_FromInteger(0))
        {
            if (field_188_ySpeed <= FP_FromInteger(0))
            {
                if (field_184_xSpeed > FP_FromInteger(0))
                {
                    if (sub_43A510())
                    {
                        VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalMovement_1_4386A0);
                    }
                    else
                    {
                        VSetMotion_4081C0(eFlyingSligMotions::M_QuickTurn_15_4387F0);
                    }
                }
                else
                {
                    VSetMotion_4081C0(eFlyingSligMotions::M_EndHorizontalMovement_10_4387D0);
                }
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToDownMovement_12_438B10);
                field_28C = 0;
            }
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToUpMovement_24_438D60);
            field_28C = 0;
        }
    }
}

void FlyingSlig::M_QuickTurn_15_4387F0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);

        if (field_188_ySpeed < FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToUpMovement_24_438D60);
            field_28C = 0;
        }
        else if (field_188_ySpeed > FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToDownMovement_12_438B10);
            field_28C = 0;
        }
        else if (field_184_xSpeed == FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_EndHorizontalMovement_10_4387D0);
        }
        else if (!sub_43A510())
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_QuickTurn_15_4387F0);
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalMovement_1_4386A0);
        }
    }
}

void FlyingSlig::M_IdleToHorizontalMovement_16_438730()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_188_ySpeed < FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToUpMovement_24_438D60);
            field_28C = 0;
        }
        else if (field_188_ySpeed > FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToDownMovement_12_438B10);
            field_28C = 0;
        }
        else if (field_184_xSpeed == FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_EndHorizontalMovement_10_4387D0);
        }
        else if (sub_43A510())
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalMovement_1_4386A0);
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_QuickTurn_15_4387F0);
        }
    }
}

void FlyingSlig::M_BeginDownMovement_17_438B80()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_184_xSpeed != FP_FromInteger(0))
        {
            if (!sub_43A510())
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_DownMovementToTurn_4_438CC0);
                return;
            }
        }
        else if (field_188_ySpeed <= FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_EndDownMovement_18_438C90);
            return;
        }
        VSetMotion_4081C0(eFlyingSligMotions::M_DownMovement_3_438AA0);
    }
}

void FlyingSlig::M_EndDownMovement_18_438C90()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_188_ySpeed >= FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_Idle_0_4385E0);
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_BeginUpMovement_11_438E40);
        }
    }
}

void FlyingSlig::M_DownKnockback_19_4390D0()
{
    if (FP_Abs(field_184_xSpeed) > FP_FromDouble(0.1) || field_188_ySpeed < FP_FromDouble(0.1))
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_EndDownMovement_18_438C90);
    }
}

void FlyingSlig::M_UpKnockback_20_439110()
{
    if (FP_Abs(field_184_xSpeed) > FP_FromDouble(0.1) || field_188_ySpeed > FP_FromDouble(-0.1))
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_Idle_0_4385E0);
    }
}

void FlyingSlig::M_EndUpMovement_21_438EB0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_188_ySpeed <= FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_Idle_0_4385E0);
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_BeginDownMovement_17_438B80);
        }
    }
}

void FlyingSlig::M_InstantUpXTurn_22_438EE0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
        VSetMotion_4081C0(eFlyingSligMotions::M_UpMovement_5_438DD0);
    }
}

void FlyingSlig::M_InstantDownXTurn_23_438F20()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);
        VSetMotion_4081C0(eFlyingSligMotions::M_DownMovement_3_438AA0);
    }
}

void FlyingSlig::M_HorizontalToUpMovement_24_438D60()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_184_xSpeed != FP_FromInteger(0))
        {
            if (!sub_43A510())
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_UpMovementToTurn_6_439030);
                return;
            }
        }
        else if (field_188_ySpeed >= FP_FromInteger(0))
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_EndUpMovement_21_438EB0);
            return;
        }
        VSetMotion_4081C0(eFlyingSligMotions::M_UpMovement_5_438DD0);
    }
}

void FlyingSlig::M_TurnToHorizontalMovement_25_4389E0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_20_animation.field_4_flags.Toggle(AnimFlags::eBit5_FlipX);

        if (field_188_ySpeed >= FP_FromInteger(0))
        {
            if (field_188_ySpeed <= FP_FromInteger(0))
            {
                if (field_184_xSpeed != FP_FromInteger(0))
                {
                    if (sub_43A510())
                    {
                        VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalMovement_1_4386A0);
                    }
                    else
                    {
                        VSetMotion_4081C0(eFlyingSligMotions::M_QuickTurn_15_4387F0);
                    }
                }
                else
                {
                    VSetMotion_4081C0(eFlyingSligMotions::M_EndHorizontalMovement_10_4387D0);
                }
            }
            else
            {
                VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToDownMovement_12_438B10);
                field_28C = 0;
            }
        }
        else
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_HorizontalToUpMovement_24_438D60);
            field_28C = 0;
        }
    }
}

signed __int16 FlyingSlig::sub_43A510()
{
    return ((field_184_xSpeed > FP_FromInteger(0) && !(field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX)))
         || (field_184_xSpeed < FP_FromInteger(0) &&   field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX)));
}

void FlyingSlig::ToPlayerControlled_4360C0()
{
    VSetMotion_4081C0(eFlyingSligMotions::M_Idle_0_4385E0);
    SetBrain(&FlyingSlig::AI_Possessed_12_436040);
}

void FlyingSlig::ToMoving_435720()
{
    MusicController::sub_47FD60(4, this, 0, 0);
    SetBrain(&FlyingSlig::AI_Moving_2_4356D0);
}

void FlyingSlig::ToPanicIdle_435B50()
{
    Say_436A50(SligSpeak::Help_10, 0);
    field_14C_timer = (Math_NextRandom() & 7) + sGnFrame_5C1B84 + field_118_data.field_10_data.field_C_panic_delay;
    SetBrain(&FlyingSlig::AI_PanicIdle_8_435AC0);
}

void FlyingSlig::ToChase_435E10()
{
    MusicController::sub_47FD60(8, this, 0, 0);
    SetBrain(&FlyingSlig::AI_ChasingEnemy_4_435BC0);
}

__int16 FlyingSlig::IsPossessed_436A90()
{
    return
        BrainIs(&FlyingSlig::AI_Possessed_12_436040) ||
        BrainIs(&FlyingSlig::AI_FlyingSligSpawn_15_4362C0) ||
        BrainIs(&FlyingSlig::AI_FromNakedSlig_17_4355E0) ||
        BrainIs(&FlyingSlig::AI_Possession_13_4360F0) ||
        BrainIs(&FlyingSlig::AI_DePossession_14_436180);
}

__int16 FlyingSlig::CanChase_436850(BaseAliveGameObject* pObj)
{
    if (!gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) ||
        !gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0) ||
        Event_Get_422C00(kEventResetting) || 
        IsAbeEnteringDoor_43B030(pObj) ||
        sActiveHero_5C1B68->field_CC_sprite_scale != field_CC_sprite_scale ||
        !IsWallBetween_43A550(this, pObj))
    {
        return 0;
    }

    if (Event_Is_Event_In_Range_422C30(kEventAbeOhm, field_B8_xpos, field_BC_ypos, field_D6_scale))
    {
        return 1;
    }

    if (vIsFacingMe_4254A0(pObj) && !IsInInvisibleZone_425710(pObj) && !pObj->field_114_flags.Get(Flags_114::e114_Bit8_bInvisible))
    {
        return 1;
    }

    return 0;
}

void FlyingSlig::Say_436A50(SligSpeak speak, __int16 pitch)
{
    if (field_106_current_motion != eFlyingSligMotions::M_GameSpeak_8_4391D0)
    {
        field_17E_flags.Set(Flags_17E::eBit1_Speaking_flag1);
        field_17E_flags.Set(Flags_17E::eBit10_Speaking_flag2);
        field_17D_next_speak = speak;
        field_160_voice_pitch_min = pitch;
    }
}

__int16 FlyingSlig::sub_4374A0(__int16 /*a2*/)
{
    NOT_IMPLEMENTED();
    return 0;

    /*
    field_17E_flags.Clear(Flags_17E::eBit2);
    auto flags = field_17E_flags;
    FP v12 = {};

    if (flags.Get(Flags_17E::eBit4))
    {
        if (!flags.Get(Flags_17E::eBit12_bNoNextLine) && (!field_182_bound1 || !a2))
        {
            if (!flags.Get(Flags_17E::eBit3))
            {
                field_190 = field_2B8_max_speed_up;
                goto LABEL_70;
            }
            const FP v4 = (field_18C * field_18C);
            const FP v5 = (v4 / field_2B4_max_slow_down);
            const FP v6 = (v5 * FP_FromDouble(0.5));
            const FP v60 = field_18C;
            const FP  v56 = field_18C;
            FP v64 = {};
            if (v6 >= FP_FromInteger(0))
            {
                const FP v9 = (v56 * v60);
                const FP v10 = (v9 / field_2B4_max_slow_down);
                v64 = (v10 * FP_FromDouble(0.5));
            }
            else
            {
                const FP v7 = (v56 * v60);
                const FP v8 = (v7 / field_2B4_max_slow_down);
                v64 = -(v8 * FP_FromDouble(0.5));
            }
            const FP v11 = FP_Abs(field_1C4 - field_194);
            if (v64 >= v11)
            {
                goto LABEL_70;
            }
            v12 = field_2B8_max_speed_up;
            field_190 = v12;
            goto LABEL_70;
        }
        else
        {
            const FP v13 = field_2B8_max_speed_up;
            FP v14 = v13 + field_18C;
            if (v14 > field_2A8_max_x_speed)
            {
                v14 = field_2A8_max_x_speed;
            }

            FP v15 = {};
            FP v16 = {};
            if (v14 <= FP_FromInteger(0))
            {
                v15 = field_1A4_rect.x;
                v16 = field_1A4_rect.w;
            }
            else
            {
                v15 = field_1A4_rect.w;
                v16 = field_1A4_rect.x;
            }

            const FP v17 = v15 - v16;
            bool v18 = v17 == FP_FromInteger(0);
            bool v19 = v17 < FP_FromInteger(0);
            if (v17 > FP_FromInteger(0))
            {
                if (field_182_bound1 == 32)
                {
                    field_190 = v13;
                    goto LABEL_70;
                }
                v18 = v17 == FP_FromInteger(0);
                v19 = v17 < FP_FromInteger(0);
            }

            if (!v19)
            {
                goto LABEL_25;
            }

            if (field_182_bound1 != 45)
            {
                v18 = v17 == FP_FromInteger(0);
            LABEL_25:
                if (v18 && !flags.Get(Flags_17E::eBit12_bNoNextLine))
                {
                    field_190 = v13;
                    goto LABEL_70;
                }

                flags.Set(Flags_17E::eBit2);
                field_17E_flags = flags;

                const FP v20 = (field_18C * field_18C);
                const FP v21 = (v20 / field_2B4_max_slow_down);
                const FP  v22 = (v21 * FP_FromDouble(0.5));
                const FP v61 = field_18C;
                const FP v57 = field_18C;
                FP v65 = {};
                if (v22 >= FP_FromInteger(0))
                {
                    const FP v25 = (v57 * v61);
                    const FP v26 = (v25 / field_2B4_max_slow_down);
                    v65 = (v26 * FP_FromDouble(0.5));
                }
                else
                {
                    const FP v23 = (v57 * v61);
                    const FP v24 = (v23 / field_2B4_max_slow_down);
                    v65 = -(v24 * FP_FromDouble(0.5));
                }
                const FP v27 = field_198_line_length - field_194;
                if (v27 < field_2A8_max_x_speed && field_18C == FP_FromInteger(0))
                {
                    return 1;
                }
                if (v65 >= v27)
                {
                    goto LABEL_70;
                }
                v12 = field_2B8_max_speed_up;
                field_190 = v12;
                goto LABEL_70;
            }
            field_190 = v13;
            goto LABEL_70;
        }
    }
    else
    {
        if (!flags.Get(Flags_17E::eBit11_bNoPrevLine) && (!field_180_bound2 || !a2))
        {
            if (flags.Get(Flags_17E::eBit3))
            {
                const FP v29 = (field_18C * field_18C);
                const FP v30 = (v29 / field_2B4_max_slow_down);
                const FP v31 = (v30 * FP_FromDouble(0.5));
                const FP v62 = field_18C;
                const FP v58 = field_18C;
                FP v66 = {};
                if (v31 >= FP_FromInteger(0))
                {
                    const FP v34 = (v58 * v62);
                    const FP v35 = (v34 / field_2B4_max_slow_down);
                    v66 = (v35 * FP_FromDouble(0.5));
                }
                else
                {
                    const FP  v32 = (v58 * v62);
                    const FP v33 = (v32 / field_2B4_max_slow_down);
                    v66 = -(v33 * FP_FromDouble(0.5));
                }
                const FP v36 = FP_Abs(field_1C4 - field_194);
                if (v66 >= v36)
                {
                    goto LABEL_70;
                }
            }
            v12 = -field_2B8_max_speed_up;
            field_190 = v12;
            goto LABEL_70;

        }
        else
        {
            const FP v37 = field_2B8_max_speed_up;
            FP v38 = -field_2A8_max_x_speed;
            if (field_18C - v37 >= v38)
            {
                v38 = field_18C - v37;
            }

            FP v39 = {};
            FP v40 = {};
            if (v38 <= FP_FromInteger(0))
            {
                v39 = field_1A4_rect.x;
                v40 = field_1A4_rect.w;
            }
            else
            {
                v39 = field_1A4_rect.w;
                v40 = field_1A4_rect.x;
            }

            const FP v41 = v39 - v40;
            bool v42 = v41 == FP_FromInteger(0);
            bool v43 = v41 < FP_FromInteger(0);
            if (v41 > FP_FromInteger(0))
            {
                if (field_180_bound2 == 32)
                {
                    field_190 = -v37;
                    goto LABEL_70;
                }
                v42 = v41 == FP_FromInteger(0);
                v43 = v41 < FP_FromInteger(0);
            }

            if (v43)
            {
                if (field_180_bound2 != 45)
                {
                    v42 = v41 == FP_FromInteger(0);
                    goto LABEL_58;
                }
                field_190 = -v37;
                goto LABEL_70;
            }

        LABEL_58:
            if (v42 && !flags.Get(Flags_17E::eBit11_bNoPrevLine))
            {
                field_190 = -v37;
                goto LABEL_70;
            }
            const FP v44 = field_18C;
            flags.Set(Flags_17E::eBit2);
            field_17E_flags = flags;
            const FP v45 = (v44 * v44);
            const FP v46 = (v45 / field_2B4_max_slow_down);
            const FP v47 = (v46 * FP_FromDouble(0.5));
            const FP v63 = field_18C;
            const FP v59 = field_18C;

            FP v67 = {};
            if (v47 >= FP_FromInteger(0))
            {
                const FP v50 = (v59 * v63);
                const FP v51 = (v50 / field_2B4_max_slow_down);
                v67 = (v51 * FP_FromDouble(0.5));
            }
            else
            {
                const FP v48 = (v59 * v63);
                const FP v49 = (v48 / field_2B4_max_slow_down);
                v67 = -(v49 * FP_FromDouble(0.5));
            }

            const FP v52 = field_194;
            if (v52 < field_2A8_max_x_speed && field_18C == FP_FromInteger(0))
            {
                return 1;
            }

            if (v67 < v52)
            {
                v12 = -field_2B8_max_speed_up;
                field_190 = v12;
                goto LABEL_70;
            }
        }
    }

LABEL_70:

    const FP v53 = field_190;
    if (v53 >= FP_FromInteger(0))
    {
        if (v53 > FP_FromInteger(0))
        {
            const FP v55 = field_1A4_rect.y;
            field_184_xSpeed = field_1A4_rect.w - field_1A4_rect.x;
            field_188_ySpeed = field_1A4_rect.h - v55;
        }
        return 0;
    }
    else
    {
        const FP v54 = field_1A4_rect.h;
        field_184_xSpeed = field_1A4_rect.x - field_1A4_rect.w;
        field_188_ySpeed = field_1A4_rect.y - v54;
        return 0;
    }*/
}

__int16 CCSTD FlyingSlig::IsAbeEnteringDoor_43B030(BaseAliveGameObject* pThis)
{
    return Slig::IsAbeEnteringDoor_4BB990(pThis);
}

BOOL CCSTD FlyingSlig::IsWallBetween_43A550(BaseAliveGameObject *pThis, BaseAliveGameObject *pObj)
{
    // TODO: Duplicated like IsAbeEnteringDoor_4BB990 ??
    PSX_RECT bRect = {};
    pObj->vGetBoundingRect_424FD0(&bRect, 1);

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    return sCollisions_DArray_5C1128->Raycast_417A60(
        pThis->field_B8_xpos,
        pThis->field_BC_ypos,
        pObj->field_B8_xpos,
        FP_FromInteger((bRect.y + bRect.h) / 2),
        &pLine,
        &hitX,
        &hitY,
        (pThis->field_D6_scale != 0 ? 1 : 16) | (pThis->field_D6_scale != 0 ? 6 : 96) | (pThis->field_D6_scale != 0 ? 8 : 0x80)) != 1;
}

void FlyingSlig::ThrowGrenade_43A1E0()
{
    FP grenadeXVel = (FP_FromInteger(Math_RandomRange_496AB0(50, 64)) / FP_FromInteger(10) * field_CC_sprite_scale);
    const FP grenadeYVel = (FP_FromInteger(-6) * field_CC_sprite_scale);

    FP grenadeXPos = (FP_FromInteger(0) * field_CC_sprite_scale);
    const FP grenadeYPos = (FP_FromInteger(-5) * field_CC_sprite_scale);

    const FP xpos = (FP_FromInteger(0) * field_CC_sprite_scale);
    const FP ypos = (FP_FromInteger(-20) * field_CC_sprite_scale);

    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        grenadeXPos = -grenadeXPos;
        grenadeXVel = -grenadeXVel;
    }

    auto pGrenade = alive_new<Grenade>();
    if (pGrenade)
    {
        pGrenade->ctor_447F70(grenadeXPos + field_B8_xpos, grenadeYPos + field_BC_ypos, 0, 1, 0, this);
    }

    pGrenade->field_CC_sprite_scale = field_CC_sprite_scale;
    pGrenade->field_D6_scale = field_D6_scale;
    pGrenade->VThrow_49E460(grenadeXVel, grenadeYVel);

    New_Particle_426890(xpos + field_B8_xpos, ypos + field_BC_ypos, field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX), field_CC_sprite_scale);
    Slig_SoundEffect_4BFFE0(8, this);
    Event_Broadcast_422BC0(kEventShooting, this);
    Event_Broadcast_422BC0(kEventLoudNoise, this);

    Dove::All_FlyAway_41FA60(0);

    int randomisedGrenadeDelay = field_118_data.field_10_data.field_18_grenade_delay + (Math_NextRandom() & 7);
    if (randomisedGrenadeDelay < 20)
    {
        randomisedGrenadeDelay = 20;
    }
    field_150_grenade_delay = randomisedGrenadeDelay + sGnFrame_5C1B84;

    if (IsPossessed_436A90() == 0 && Math_NextRandom() < 168u)
    {
        Sfx_Slig_GameSpeak_4C04F0(SligSpeak::HereBoy_1, 0, field_15C_voice_pitch_min, this);
    }
}

void FlyingSlig::BlowUp_436510()
{
    MusicController::sub_47FD60(0, this, 0, 0);
    auto pGibs = alive_new<Gibs>();
    if (pGibs)
    {
        pGibs->ctor_40FB40(1, field_B8_xpos, field_BC_ypos, field_C4_velx, field_C8_vely, field_CC_sprite_scale, 0);
    }

    auto pBlood = alive_new<Blood>();
    if (pBlood)
    {
        pBlood->ctor_40F0B0(field_B8_xpos, field_BC_ypos - (FP_FromInteger(30) * field_CC_sprite_scale), FP_FromInteger(0), FP_FromInteger(0), field_CC_sprite_scale, 20);
    }

    New_Particles_426C70(field_B8_xpos, field_BC_ypos - (FP_FromInteger(30) * field_CC_sprite_scale), field_CC_sprite_scale, 3, 128u, 128u, 128u);
    SFX_Play_46FA90(64u, 128, field_CC_sprite_scale);
    SFX_Play_46FA90(47u, 90, field_CC_sprite_scale);

    field_20_animation.field_4_flags.Clear(AnimFlags::eBit2_Animate);
    field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);

    field_18C = FP_FromInteger(0);
    field_C8_vely = FP_FromInteger(0);
    field_C4_velx = FP_FromInteger(0);
    field_190 = FP_FromInteger(0);
    field_188_ySpeed = FP_FromInteger(0);
    field_184_xSpeed = FP_FromInteger(0);
    field_10C_health = FP_FromInteger(0);
    SetBrain(&FlyingSlig::AI_Death_1_4364E0);
    field_14C_timer = sGnFrame_5C1B84 + 40;
}

__int16 FlyingSlig::sub_436730()
{
    if (CanChase_436850(sControlledCharacter_5C1B8C))
    {
        ToSpottedEnemy_435E70();
        return 1;
    }
    else if (CanHearAbe_4369C0() && !BrainIs(&FlyingSlig::AI_GetAlerted_3_435750))
    {
        ToAlerted_4357E0();
        return 1;
    }
    else if (Event_Is_Event_In_Range_422C30(kEventAbeOhm, field_B8_xpos, field_BC_ypos, field_D6_scale))
    {
        ToPanicMoving_435A50();
        return 1;
    }
    else
    {
        if (sActiveHero_5C1B68 &&
            sActiveHero_5C1B68->field_10C_health < FP_FromInteger(0) &&
            FP_Abs(field_B8_xpos - sActiveHero_5C1B68->field_B8_xpos) < FP_FromInteger(640) &&
            FP_Abs(field_BC_ypos - sActiveHero_5C1B68->field_BC_ypos) < FP_FromInteger(240))
        {
            ToAbeDead_436010();
            return 1;
        }
        return 0;
    }

}

__int16 FlyingSlig::CanHearAbe_4369C0()
{
    return
        sActiveHero_5C1B68 == Event_Is_Event_In_Range_422C30(kEventSuspiciousNoise, field_B8_xpos, field_BC_ypos, field_D6_scale) ||
        sActiveHero_5C1B68 == Event_Is_Event_In_Range_422C30(kEventSpeaking, field_B8_xpos, field_BC_ypos, field_D6_scale);
}

void FlyingSlig::ToSpottedEnemy_435E70()
{
    if (field_118_data.field_10_data.field_10_prechase_delay)
    {
        Say_436A50(SligSpeak ::Freeze_8, 0);
        field_14C_timer = (Math_NextRandom() & 7) + sGnFrame_5C1B84 + field_118_data.field_10_data.field_10_prechase_delay;
        SetBrain(&FlyingSlig::AI_SpottedEnemy_9_435E40);
    }
    else
    {
        Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Freeze_8, 0, field_15C_voice_pitch_min, this);
        ToChase_435E10();
    }
}

void FlyingSlig::ToAbeDead_436010()
{
    SetBrain(&FlyingSlig::AI_AbeDead_11_435FD0);
    field_14C_timer = sGnFrame_5C1B84 + 70;
}

void FlyingSlig::ToAlerted_4357E0()
{
    Say_436A50(SligSpeak ::What_9, 0);
    SetBrain(&FlyingSlig::AI_GetAlerted_3_435750);
    field_14C_timer = sGnFrame_5C1B84 + field_118_data.field_10_data.field_14_listen_time;
}

void FlyingSlig::ToPanicMoving_435A50()
{
    MusicController::sub_47FD60(8, this, 0, 0);
    field_14C_timer = (Math_NextRandom() & 7) + sGnFrame_5C1B84 + 12;
    SetBrain(&FlyingSlig::AI_PanicMoving_7_435990);
}

__int16 FlyingSlig::IsTurning_436AE0()
{
    return 
        field_106_current_motion == eFlyingSligMotions::M_IdleToTurn_2_4388B0 ||
        field_106_current_motion == eFlyingSligMotions::M_QuickTurn_15_4387F0 ||
        field_106_current_motion == eFlyingSligMotions::M_DownMovementToTurn_4_438CC0 ||
        field_106_current_motion == eFlyingSligMotions::M_UpMovementToTurn_6_439030;
}

BYTE** FlyingSlig::ResBlockForMotion_4350F0(int /*motion*/)
{
    if (field_15E == 0)
    {
        return field_10_resources_array.ItemAt(0);
    }
    else
    {
        field_15E = 0;
        return field_10_resources_array.ItemAt(0);
    }
}

void FlyingSlig::ToChantShake_436270()
{
    SFX_Play_46FA90(17, 0);
    VSetMotion_4081C0(eFlyingSligMotions::M_Possession_9_434290);
    SetBrain(&FlyingSlig::AI_DePossession_14_436180);
    field_14C_timer = sGnFrame_5C1B84 + 45;
}

void FlyingSlig::ToPossesed_436130()
{
    Sfx_Slig_GameSpeak_4C04F0(SligSpeak::Help_10, 0, field_15C_voice_pitch_min, this);
    VSetMotion_4081C0(eFlyingSligMotions::M_Possession_9_434290);
    SetBrain(&FlyingSlig::AI_Possession_13_4360F0);
    field_14C_timer = sGnFrame_5C1B84 + 35;
}

const int sFlyingSligFrameTables_552408[41] =
{
    116888,
    116912,
    117084,
    116988,
    117584,
    117012,
    117616,
    117188,
    117132,
    117524,
    117060,
    117316,
    117276,
    117444,
    117376,
    116936,
    117036,
    117336,
    117356,
    117396,
    117464,
    117424,
    117552,
    117492,
    117296,
    117752,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};


void FlyingSlig::vUpdateAnimRes_4350A0()
{
    BYTE** ppRes = ResBlockForMotion_4350F0(field_106_current_motion);
    if (!ppRes)
    {
        field_106_current_motion = eFlyingSligMotions::M_Idle_0_4385E0;
        ppRes = FlyingSlig::ResBlockForMotion_4350F0(field_106_current_motion);
    }
    field_20_animation.Set_Animation_Data_409C80(sFlyingSligFrameTables_552408[field_106_current_motion], ppRes);
}

void FlyingSlig::PatrolDelay_435860()
{
    if (BrainIs(&FlyingSlig::AI_ChasingEnemy_4_435BC0))
    {
        field_14C_timer = (Math_NextRandom() & 7) + sGnFrame_5C1B84 + field_118_data.field_10_data.field_E_give_up_chase_delay;
        SetBrain(&FlyingSlig::AI_Idle_5_435820);
        return;
    }

    field_14C_timer = field_118_data.field_10_data.field_6_patrol_pause_min + sGnFrame_5C1B84;
    if (field_118_data.field_10_data.field_6_patrol_pause_min <= field_118_data.field_10_data.field_8_patrol_pause_max)
    {
        SetBrain(&FlyingSlig::AI_Idle_5_435820);
        return;
    }

    field_14C_timer += Math_NextRandom() % (field_118_data.field_10_data.field_6_patrol_pause_min - field_118_data.field_10_data.field_8_patrol_pause_max);
    SetBrain(&FlyingSlig::AI_Idle_5_435820);
}

__int16 FlyingSlig::CanThrowGrenade_43A490()
{
    return 
        field_106_current_motion == eFlyingSligMotions::M_Idle_0_4385E0 ||
        field_106_current_motion == eFlyingSligMotions::M_HorizontalMovement_1_4386A0 ||
        field_106_current_motion == eFlyingSligMotions::M_DownMovement_3_438AA0 ||
        field_106_current_motion == eFlyingSligMotions::M_UpMovement_5_438DD0 ||
        field_106_current_motion == eFlyingSligMotions::M_IdleToHorizontalMovement_16_438730 ||
        field_106_current_motion == eFlyingSligMotions::M_EndHorizontalMovement_10_4387D0 ||
        field_106_current_motion == eFlyingSligMotions::M_BeginUpMovement_11_438E40 ||
        field_106_current_motion == eFlyingSligMotions::M_UpToHorizontalMovement_13_438F60 ||
        field_106_current_motion == eFlyingSligMotions::M_HorizontalToDownMovement_12_438B10 ||
        field_106_current_motion == eFlyingSligMotions::M_DownToHorizontalMovement_14_438BF0 ||
        field_106_current_motion == eFlyingSligMotions::M_EndDownMovement_18_438C90 ||
        field_106_current_motion == eFlyingSligMotions::M_BeginDownMovement_17_438B80;
}

void FlyingSlig::ToLaunchingGrenade_435F50()
{
    if (!vIsFacingMe_4254A0(sControlledCharacter_5C1B8C) && !IsTurning_436AE0())
    {
        if (field_18C == FP_FromInteger(0))
        {
            field_17E_flags.Set(Flags_17E::eBit6);
        }
        field_17E_flags.Toggle(Flags_17E::eBit4);
    }
    SetBrain(&FlyingSlig::AI_LaunchingGrenade_10_435F10);
}

void FlyingSlig::HandlePlayerControls_439340()
{
    /* OG issue - these local statics are never used ??
    if (!(byte_5BC5F4 & 1))
    {
        byte_5BC5F4 |= 1u;
        dword_5BC5F8 = Math_FixedPoint_Divide_496B70(0x800000, field_2B8);
    }
    if (!(byte_5BC5F4 & 2))
    {
        dword_5BC5F0 = 0x3F0000;
        byte_5BC5F4 |= 2u;
    }
    */

    field_17E_flags.Clear(Flags_17E::eBit5_Throw);
    field_17E_flags.Clear(Flags_17E::eBit6);
    field_17E_flags.Clear(Flags_17E::eBit7_DoAction);

    field_184_xSpeed = FP_FromInteger(0);
    field_188_ySpeed = FP_FromInteger(0);

    if (sInputObject_5BD4E0.isHeld(InputCommands::eThrowItem))
    {
        field_17E_flags.Set(Flags_17E::eBit5_Throw);
    }

    if (sInputObject_5BD4E0.isHeld(InputCommands::eDoAction))
    {
        field_17E_flags.Set(Flags_17E::eBit7_DoAction);
    }

    if (!field_17E_flags.Get(Flags_17E::eBit1_Speaking_flag1))
    {
        field_17E_flags.Set(Flags_17E::eBit1_Speaking_flag1);
        field_17E_flags.Set(Flags_17E::eBit10_Speaking_flag2);

        field_160_voice_pitch_min = 0;

        if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak1_555104))
        {
            field_17D_next_speak = SligSpeak::Hi_0;
        }
        else if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak3_555100))
        {
            field_17D_next_speak = sInputObject_5BD4E0.Is_Demo_Playing_45F220() != 0 ? SligSpeak::GetEm_2 : SligSpeak::Freeze_8;
        }
        else if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak4_5550FC))
        {
            field_17D_next_speak = sInputObject_5BD4E0.Is_Demo_Playing_45F220() != 0 ? SligSpeak::Freeze_8 : SligSpeak::GetEm_2;
        }
        else if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak2_5550F8))
        {
            field_17D_next_speak = SligSpeak::HereBoy_1;
        }
        else if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak6_555108))
        {
            field_17D_next_speak = SligSpeak::Bullshit_5;
        }
        else if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak7_555114))
        {
            field_17D_next_speak = SligSpeak::LookOut_6;
        }
        else if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak5_55510C))
        {
            field_17D_next_speak = SligSpeak::Bullshit2_7;
        }
        else if (sInputObject_5BD4E0.isHeld(sInputKey_GameSpeak8_555110))
        {
            field_17D_next_speak = SligSpeak::Laugh_3;
        }
        else
        {
            field_17E_flags.Clear(Flags_17E::eBit1_Speaking_flag1);
            field_17E_flags.Clear(Flags_17E::eBit10_Speaking_flag2);
        }
    }

    if (sInputObject_5BD4E0.isPressed(InputCommands::eUp))
    {
        if (sInputObject_5BD4E0.isPressed(InputCommands::eLeft))
        {
            field_184_xSpeed = (-field_2B8_max_speed_up * FP_FromDouble(0.707));
            field_188_ySpeed = (-field_2B8_max_speed_up * FP_FromDouble(0.707));
            return;
        }
        if (sInputObject_5BD4E0.isPressed(InputCommands::eRight))
        {
            field_184_xSpeed = (field_2B8_max_speed_up * FP_FromDouble(0.707));
            field_188_ySpeed = (-field_2B8_max_speed_up * FP_FromDouble(0.707));
            return;
        }
        field_184_xSpeed = FP_FromInteger(0);
        field_188_ySpeed = -field_2B8_max_speed_up;
    }
    else if (sInputObject_5BD4E0.isPressed(InputCommands::eDown))
    {
        if (sInputObject_5BD4E0.isPressed(InputCommands::eLeft))
        {
            field_184_xSpeed = (-field_2B8_max_speed_up * FP_FromDouble(0.707));
            field_188_ySpeed = (field_2B8_max_speed_up * FP_FromDouble(0.707));
        }
        else if (sInputObject_5BD4E0.isPressed(InputCommands::eRight))
        {
            field_184_xSpeed = (field_2B8_max_speed_up * FP_FromDouble(0.707));
            field_188_ySpeed = (field_2B8_max_speed_up * FP_FromDouble(0.707));
        }
        else
        {
            field_184_xSpeed = FP_FromInteger(0);
            field_188_ySpeed = field_2B8_max_speed_up;
        }
    }
    else if (sInputObject_5BD4E0.isPressed(InputCommands::eLeft))
    {
        field_188_ySpeed = FP_FromInteger(0);
        field_184_xSpeed = -field_2B8_max_speed_up;
    }
    else if (sInputObject_5BD4E0.isPressed(InputCommands::eRight))
    {
        field_188_ySpeed = FP_FromInteger(0);
        field_184_xSpeed = field_2B8_max_speed_up;
    }

}

__int16 FlyingSlig::sub_437C70(PathLine* pLine)
{

    field_100_pCollisionLine = pLine;
    if (!field_100_pCollisionLine)
    {
        return 0;
    }

    field_1A4_rect.x = FP_FromInteger(field_100_pCollisionLine->field_0_rect.x);
    field_1A4_rect.y = FP_FromInteger(field_100_pCollisionLine->field_0_rect.y);
    field_1A4_rect.w = FP_FromInteger(field_100_pCollisionLine->field_0_rect.w);
    field_1A4_rect.h = FP_FromInteger(field_100_pCollisionLine->field_0_rect.h);


    field_1EC_pNextLine = sCollisions_DArray_5C1128->Get_Line_At_Idx_418070(field_100_pCollisionLine->field_C_next);
    field_1F0_pPrevLine = sCollisions_DArray_5C1128->Get_Line_At_Idx_418070(field_100_pCollisionLine->field_A_previous);

    field_198_line_length = FP_FromInteger(field_100_pCollisionLine->field_12_line_length);

    field_17E_flags.Set(Flags_17E::eBit11_bNoPrevLine, field_1F0_pPrevLine == nullptr);
    field_17E_flags.Set(Flags_17E::eBit12_bNoNextLine, field_1EC_pNextLine == nullptr);

    field_182_bound1 = FindLeftOrRightBound_43B0A0(field_1A4_rect.w, field_1A4_rect.h);
    field_180_bound2 = FindLeftOrRightBound_43B0A0(field_1A4_rect.x, field_1A4_rect.y);
    field_1BC = Math_496F70(field_1A4_rect.y - field_1A4_rect.h, field_1A4_rect.w - field_1A4_rect.x);

    field_1C0 = field_1BC + FP_FromInteger(128);

    if (field_1C0 >= FP_FromInteger(256))
    {
        field_1C0 -= FP_FromInteger(256);
    }
    return 1;
}

__int16 FlyingSlig::FindLeftOrRightBound_43B0A0(FP xOrY, FP wOrH)
{
    const FP kGridSize = ScaleToGridSize_4498B0(field_CC_sprite_scale);

    const FP left = xOrY - kGridSize;
    const FP top = wOrH - kGridSize;
    const FP right =  xOrY + kGridSize;
    const FP bottom = wOrH + kGridSize;

    // TODO: Check left is really Abs'd
    short found_type = 0;
    if (sPath_dword_BB47C0->TLV_Get_At_4DB4B0(FP_GetExponent(FP_Abs(left)), FP_GetExponent(top), FP_GetExponent(right), FP_GetExponent(bottom), TlvTypes::SligBoundLeft_32))
    {
        found_type = TlvTypes::SligBoundLeft_32;
    }
    else if (sPath_dword_BB47C0->TLV_Get_At_4DB4B0(FP_GetExponent(left), FP_GetExponent(top), FP_GetExponent(right), FP_GetExponent(bottom), TlvTypes::SligBoundRight_45))
    {
        found_type = TlvTypes::SligBoundRight_45;
    }
    return found_type;
}

void FlyingSlig::vPossessed_434FB0()
{
    field_114_flags.Set(Flags_114::e114_Bit4_bPossesed);
    field_17E_flags.Set(Flags_17E::eBit1_Speaking_flag1);

    field_2A0_abe_level = gMap_5C3030.sCurrentLevelId_5C3030;
    field_2A2_abe_path = gMap_5C3030.sCurrentPathId_5C3032;
    field_2A4_abe_camera = gMap_5C3030.sCurrentCamId_5C3034;
    
    field_2A8_max_x_speed = FP_FromDouble(5.5) * field_CC_sprite_scale;
    field_2AC_up_vel = FP_FromDouble(-5.5) * field_CC_sprite_scale;
    field_2B0_down_vel = FP_FromDouble(5.5) * field_CC_sprite_scale;
    field_2B4_max_slow_down = FP_FromDouble(0.25) * field_CC_sprite_scale;
    field_2B8_max_speed_up = FP_FromDouble(0.7) * field_CC_sprite_scale;

    ToPossesed_436130();
}

__int16 FlyingSlig::sub_436C60(PSX_RECT* /*pRect*/, __int16 /*op1*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

BOOL FlyingSlig::sub_436B20()
{
    PathLine* pLastNextOrPrevLine = nullptr;

    FP lastNextSegmentLength = FP_FromInteger(9999);
    FP totalNextSegmentLength = {};

    PathLine* pNextLine = sCollisions_DArray_5C1128->Get_Line_At_Idx_418070(field_100_pCollisionLine->field_C_next);
    if (pNextLine)
    {
        while (pNextLine != field_100_pCollisionLine)
        {
            if (sub_436C60(&pNextLine->field_0_rect, 0))
            {
                field_17E_flags.Set(Flags_17E::eBit4);
                pLastNextOrPrevLine = pNextLine;
                if (pNextLine)
                {
                    lastNextSegmentLength = totalNextSegmentLength;
                }
                break;
            }
            else
            {
                totalNextSegmentLength += FP_FromInteger(pNextLine->field_12_line_length);
                pNextLine = sCollisions_DArray_5C1128->Get_Line_At_Idx_418070(pNextLine->field_C_next);
                if (!pNextLine)
                {
                    break;
                }
            }
        }
    }

    FP totalPrevSegmentLength = {};
    PathLine* pPrevLine = sCollisions_DArray_5C1128->Get_Line_At_Idx_418070(field_100_pCollisionLine->field_A_previous);
    if (pPrevLine)
    {
        while (pPrevLine != field_100_pCollisionLine)
        {
            if (sub_436C60(&pPrevLine->field_0_rect, 0))
            {
                if (totalPrevSegmentLength < lastNextSegmentLength)
                {
                    field_17E_flags.Clear(Flags_17E::eBit4);
                    pLastNextOrPrevLine = pPrevLine;
                }
                break;
            }
            else
            {
                totalPrevSegmentLength += FP_FromInteger(pPrevLine->field_12_line_length);
                pPrevLine = sCollisions_DArray_5C1128->Get_Line_At_Idx_418070(pPrevLine->field_A_previous);
                if (!pPrevLine)
                {
                    break;
                }
            }
        }
    }

    return pLastNextOrPrevLine != nullptr;
}

void FlyingSlig::sub_4373B0()
{
    const FP calc = Math_496F70(field_BC_ypos - sControlledCharacter_5C1B8C->field_BC_ypos, sControlledCharacter_5C1B8C->field_B8_xpos - field_B8_xpos);
    FP value1 = FP_Abs(field_1BC - calc);
    if (value1 > FP_FromInteger(128))
    {
        value1 = FP_FromInteger(256) - value1;
    }

    FP value2 = FP_Abs(field_1C0 - calc);
    if (value2 > FP_FromInteger(128))
    {
        value2 = FP_FromInteger(256) - value2;
    }

    if (value1 >= value2)
    {
        field_17E_flags.Clear(Flags_17E::eBit4);
    }
    else
    {
        field_17E_flags.Set(Flags_17E::eBit4);
    }
}

void FlyingSlig::vSetMotion_43B1B0(__int16 newMotion)
{
    field_106_current_motion = newMotion;
    vUpdateAnimRes_4350A0();
}

__int16 FlyingSlig::CollisionUp_43A640(FP velY)
{
    const FP y2 = field_BC_ypos - (field_CC_sprite_scale * FP_FromInteger(20)) + velY;

    FP xOff1 = {};
    FP xOff2 = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        xOff1 = (field_CC_sprite_scale * FP_FromInteger(17));
        xOff2 = ((field_CC_sprite_scale * FP_FromInteger(17)) / FP_FromInteger(3));
    }
    else
    {
        xOff2 = (field_CC_sprite_scale * FP_FromInteger(17));
        xOff1 = ((field_CC_sprite_scale * FP_FromInteger(17)) / FP_FromInteger(3));
    }

    FP hitX = {};
    FP hitY = {};
    PathLine* pLine = nullptr;
    __int16 bCollision = sCollisions_DArray_5C1128->Raycast_417A60(
        field_B8_xpos - xOff1,
        field_BC_ypos,
        field_B8_xpos - xOff1,
        y2,
        &pLine,
        &hitX,
        &hitY,
        (field_D6_scale != 0 ? 0x20000 : 0x40000) | (field_D6_scale != 0 ? 1 : 0x10) | (field_D6_scale != 0 ? 8 : 0x80));
    
    if (!bCollision)
    {
        bCollision = sCollisions_DArray_5C1128->Raycast_417A60(
            xOff2 + field_B8_xpos,
            field_BC_ypos,
            xOff2 + field_B8_xpos,
            y2,
            &pLine,
            &hitX,
            &hitY,
            (field_D6_scale != 0 ? 0x20000 : 0x40000) | (field_D6_scale != 0 ? 1 : 16) | (field_D6_scale != 0 ? 8 : 128));
    }

    if (bCollision)
    {
        if (FP_Abs(field_184_xSpeed) < FP_FromDouble(0.1) && field_106_current_motion != eFlyingSligMotions::M_UpKnockback_20_439110)
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_UpKnockback_20_439110);
        }

        if (static_cast<int>(sGnFrame_5C1B84) > field_154)
        {
            Sfx_Slig_GameSpeak_4C04F0(sGnFrame_5C1B84 & 1 ? SligSpeak::Ouch2_14 : SligSpeak::Ouch1_13, 127, Math_RandomRange_496AB0(256, 512), this);
            field_154 = (Math_NextRandom() & 3) + sGnFrame_5C1B84 + 10;
            auto pBurst = alive_new<ParticleBurst>();
            if (pBurst)
            {
                pBurst->ctor_41CF50(
                    field_B8_xpos,
                    hitY + (FP_FromInteger(7) * field_CC_sprite_scale),
                    5u,
                    field_CC_sprite_scale,
                    BurstType::eSmallPurpleSparks_6,
                    9);
            }
        }

        Slig_SoundEffect_4BFFE0(sGnFrame_5C1B84 & 1 ? 12 : 13, this);

        field_BC_ypos += velY + hitY - y2;
        return 1;
    }
    return 0;
}

__int16 FlyingSlig::CollisionDown_43A9E0(FP velY)
{
    const FP y2 = (field_CC_sprite_scale * FP_FromInteger(10)) + field_BC_ypos + velY;

    FP xOff1 = {};
    FP xOff2 = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        xOff1 = (field_CC_sprite_scale * FP_FromInteger(17));
        xOff2 = ((field_CC_sprite_scale * FP_FromInteger(17)) / FP_FromInteger(3));
    }
    else
    {
        xOff1 = ((field_CC_sprite_scale * FP_FromInteger(17)) / FP_FromInteger(3));
        xOff2 = (field_CC_sprite_scale * FP_FromInteger(17));
    }

    FP hitX = {};
    FP hitY = {};
    PathLine* pLine = nullptr;
    __int16 bCollision = sCollisions_DArray_5C1128->Raycast_417A60(
        field_B8_xpos - xOff1,
        field_BC_ypos,
        field_B8_xpos - xOff1,
        y2,
        &pLine,
        &hitX,
        &hitY,
        (field_D6_scale != 0 ? 0x20000 : 0x40000) | (field_D6_scale != 0 ? 1 : 0x10));

    if (!bCollision)
    {
        bCollision = sCollisions_DArray_5C1128->Raycast_417A60(
            xOff2 + field_B8_xpos,
            field_BC_ypos,
            xOff2 + field_B8_xpos,
            y2,
            &pLine,
            &hitX,
            &hitY,
            (field_D6_scale != 0 ? 0x20000 : 0x40000) | (field_D6_scale != 0 ? 1 : 0x10));
    }

    if (bCollision)
    {
        if (FP_Abs(field_184_xSpeed) < FP_FromDouble(0.1) && field_106_current_motion != eFlyingSligMotions::M_DownKnockback_19_4390D0)
        {
            VSetMotion_4081C0(eFlyingSligMotions::M_DownKnockback_19_4390D0);
        }

        if (static_cast<int>(sGnFrame_5C1B84) > field_154)
        {
            Sfx_Slig_GameSpeak_4C04F0(sGnFrame_5C1B84 & 1 ? SligSpeak::Ouch2_14 : SligSpeak::Ouch1_13, 127, Math_RandomRange_496AB0(256, 512), this);
            field_154 = (Math_NextRandom() & 3) + sGnFrame_5C1B84 + 10;
        }

        field_BC_ypos += velY + hitY - y2;
        return 1;
    }
    return 0;
}

__int16 FlyingSlig::CollisionLeftRight_43AC80(FP velX)
{
    FP newX = {};
    if (velX <= FP_FromInteger(0))
    {
        newX = field_B8_xpos - (field_CC_sprite_scale * FP_FromInteger(17));
    }
    else
    {
        newX = (field_CC_sprite_scale * FP_FromInteger(17)) + field_B8_xpos;
    }

    const FP xOff = velX + newX;
    const FP yOff2 = field_BC_ypos - (field_CC_sprite_scale * FP_FromInteger(20));
    const FP yOff1 = (field_CC_sprite_scale * FP_FromInteger(20));

    FP hitX = {};
    FP hitY = {};
    PathLine* pLine = nullptr;
    __int16 bCollision = sCollisions_DArray_5C1128->Raycast_417A60(
        field_B8_xpos,
        field_BC_ypos - yOff1,
        xOff,
        yOff2,
        &pLine,
        &hitX,
        &hitY,
        (field_D6_scale != 0 ? 0x20000 : 0x40000) | (field_D6_scale != 0 ? 6 : 96));

    FP sparkX = {};
    if (bCollision)
    {
        FP k25Directed = {};
        if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
        {
            k25Directed = FP_FromInteger(-25);
        }
        else
        {
            k25Directed = FP_FromInteger(25);
        }
        sparkX = (k25Directed * field_CC_sprite_scale) + field_B8_xpos;
        Slig_SoundEffect_4BFFE0(sGnFrame_5C1B84 & 1 ? 12 : 13, this);
    }
    else
    {
        bCollision = sCollisions_DArray_5C1128->Raycast_417A60(
            field_B8_xpos,
            (field_CC_sprite_scale * FP_FromInteger(10)) + field_BC_ypos,
            xOff,
            (field_CC_sprite_scale * FP_FromInteger(10)) + field_BC_ypos,
            &pLine,
            &hitX,
            &hitY,
            (field_D6_scale != 0 ? 0x20000 : 0x40000) | (field_D6_scale != 0 ? 6 : 96));

        if (bCollision)
        {
            FP k25Directed = {};
            if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
            {
                k25Directed = FP_FromInteger(-25);
            }
            else
            {
                k25Directed = FP_FromInteger(25);
            }
            sparkX = (k25Directed * field_CC_sprite_scale) + field_B8_xpos;
        }
    }

    if (bCollision)
    {
        if (static_cast<int>(sGnFrame_5C1B84) > field_154)
        {
            Sfx_Slig_GameSpeak_4C04F0(sGnFrame_5C1B84 & 1 ? SligSpeak::Ouch2_14 : SligSpeak::Ouch1_13, 127, Math_RandomRange_496AB0(256, 512), this);
            field_154 = (Math_NextRandom() & 3) + sGnFrame_5C1B84 + 10;
            auto pBurst = alive_new<ParticleBurst>();
            if (pBurst)
            {
                pBurst->ctor_41CF50(sparkX, hitY + (FP_FromInteger(16) * field_CC_sprite_scale), 5u, field_CC_sprite_scale, BurstType::eSmallPurpleSparks_6, 9);
            }
        }
        field_B8_xpos += velX + hitX - xOff;
        return 1;
    }

    return 0;
}

void FlyingSlig::sub_436450()
{
    field_C4_velx = FP_FromInteger(0);
    field_C8_vely = FP_FromInteger(0);

    field_184_xSpeed = FP_FromInteger(0);
    field_188_ySpeed = FP_FromInteger(0);

    if ((FP_Abs(field_B8_xpos - field_1C8) < FP_FromInteger(1)) &&
        (FP_Abs(field_BC_ypos - field_1CC) < FP_FromInteger(1)))
    {
        VSetMotion_4081C0(eFlyingSligMotions::M_LeverPull_7_439150);
    }
    else
    {
        SetBrain(&FlyingSlig::AI_FlyingSligSpawn_15_4362C0);
    }
}

__int16 FlyingSlig::TryPullLever_439DB0()
{
    if (BrainIs(&FlyingSlig::AI_FlyingSligSpawn_15_4362C0))
    {
        return 0;
    }

    FP kGridSizeDirected = {};
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
    {
        kGridSizeDirected = -ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }
    else
    {
        kGridSizeDirected = ScaleToGridSize_4498B0(field_CC_sprite_scale);
    }
    
    const FP k15Scaled = FP_FromInteger(15) * field_CC_sprite_scale;
    const FP k2ScaledDirected = (kGridSizeDirected * FP_FromInteger(2));

    // TODO: These can be replaced with std::min/std::max
    FP rect_w_fp = {};
    if (field_B8_xpos + kGridSizeDirected <= field_B8_xpos + k2ScaledDirected)
    {
        rect_w_fp = field_B8_xpos + kGridSizeDirected;
    }
    else
    {
        rect_w_fp = field_B8_xpos + k2ScaledDirected;
    }

    FP rect_x_fp = {};
    if (field_B8_xpos + k2ScaledDirected <= field_B8_xpos + kGridSizeDirected)
    {
        rect_x_fp = field_B8_xpos + kGridSizeDirected;
    }
    else
    {
        rect_x_fp = (k2ScaledDirected) + field_B8_xpos;
    }

    FP rect_h_fp = {};
    if (field_BC_ypos - k15Scaled <= k15Scaled + field_BC_ypos)
    {
        rect_h_fp = field_BC_ypos - k15Scaled;
    }
    else
    {
        rect_h_fp = k15Scaled + field_BC_ypos;
    }

    FP rect_y_fp = {};
    if (k15Scaled + field_BC_ypos <= field_BC_ypos - k15Scaled)
    {
        rect_y_fp = field_BC_ypos - k15Scaled;
    }
    else
    {
        rect_y_fp = k15Scaled + field_BC_ypos;
    }

    // TODO: Can be replaced with FP_Rect and PSX_RECT
    const short rect_w = FP_GetExponent(rect_w_fp);
    const short rect_x = FP_GetExponent(rect_x_fp);
    const short rect_h = FP_GetExponent(rect_h_fp);
    const short rect_y = FP_GetExponent(rect_y_fp);

    for (int i = 0; i < gBaseGameObject_list_BB47C4->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObject_list_BB47C4->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->field_4_typeId == Types::eLever_139)
        {
            auto pAliveObj = static_cast<BaseAliveGameObject*>(pObj);

            PSX_RECT bObjRect = {};
            pAliveObj->vGetBoundingRect_424FD0(&bObjRect, 1);
            if (rect_w <= bObjRect.w &&
                rect_x >= bObjRect.x &&
                rect_y >= bObjRect.y &&
                rect_h <= bObjRect.h)
            {
                if (field_20_animation.field_4_flags.Get(AnimFlags::eBit5_FlipX))
                {
                    if (field_B8_xpos < pAliveObj->field_B8_xpos)
                    {
                        return FALSE;
                    }
                    field_1C8 = (FP_FromInteger(45) * field_CC_sprite_scale) + pAliveObj->field_B8_xpos;
                }
                else
                {
                    if (field_B8_xpos > pAliveObj->field_B8_xpos)
                    {
                        return FALSE;
                    }
                    field_1C8 = pAliveObj->field_B8_xpos - (FP_FromInteger(47) * field_CC_sprite_scale);
                }

                field_1CC = pAliveObj->field_BC_ypos - (FP_FromInteger(23) * field_CC_sprite_scale);
                field_158_obj_id = pAliveObj->field_8_object_id;
                sub_436450();
                return TRUE;
            }
        }
    }
    return FALSE;
}

void FlyingSlig::sub_437AC0(FP arg1, FP_Point* pPoint)
{
    FP unknown = arg1;
    if (arg1 == FP_FromInteger(0))
    {
        pPoint->field_0_x = field_B8_xpos;
        pPoint->field_4_y = field_BC_ypos;
        return;
    }

    if (arg1 > FP_FromInteger(0))
    {
        if (field_194 + arg1 > field_198_line_length)
        {
            if (!field_17E_flags.Get(Flags_17E::eBit2) && field_1EC_pNextLine)
            {
                unknown = field_194 + arg1 - field_198_line_length;
                if (sub_437C70(field_1EC_pNextLine))
                {
                    field_194 = FP_FromInteger(0);
                }
                else
                {
                    unknown = FP_FromInteger(0);
                    field_194 = field_198_line_length;
                }
            }
            else
            {
                unknown = FP_FromInteger(0);
                field_194 = field_198_line_length;
            }
        }
    }
    else
    {
        if (field_194 + arg1 < FP_FromInteger(0))
        {
            if (!field_17E_flags.Get(Flags_17E::eBit2) && field_1F0_pPrevLine)
            {
                unknown = field_194 + arg1;
                if (sub_437C70(field_1F0_pPrevLine))
                {
                    field_194 = field_198_line_length;
                }
                else
                {
                    unknown = FP_FromInteger(0);
                    field_194 = FP_FromInteger(0);
                }
            }
            else
            {
                unknown = FP_FromInteger(0);
                field_194 = FP_FromInteger(0);
            }
        }
    }

    field_194 += unknown;
    pPoint->field_0_x = (field_194 * ((field_1A4_rect.w - field_1A4_rect.x) / field_198_line_length)) + field_1A4_rect.x;
    pPoint->field_4_y = (field_194 * ((field_1A4_rect.h - field_1A4_rect.y) / field_198_line_length)) + field_1A4_rect.y;
}
