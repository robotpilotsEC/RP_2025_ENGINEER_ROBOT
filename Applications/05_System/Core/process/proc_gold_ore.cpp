/******************************************************************************
 * @brief        
 * 
 * @file         proc_gold_ore.cpp
 * @author       Fish_Joe (2328339747@qq.com)
 * @version      V1.0
 * @date         2025-03-23
 * 
 * @copyright    Copyright (c) 2025
 * 
 ******************************************************************************/

#include "Core.hpp"

namespace my_engineer {

/******************************************************************************
 * @brief    金矿石任务
 ******************************************************************************/
void CSystemCore::StartGoldOreTask(void *arg) {

	if (arg == nullptr) proc_return();

	// 获取SystemCore句柄
	auto &core = *reinterpret_cast<CSystemCore *>(arg);
	auto &keyboard = SysRemote.remoteInfo.keyboard;
	auto cnt = 0;
	const auto timeout = 60000 / 5; // unit: ms

	core.parm_->armCmd.isAutoCtrl = true;
	core.psubgantry_->subGantryCmd.isAutoCtrl = true;
	core.psubgantry_->subGantryCmd.isAutoCtrl = true;

	core.pgimbal_->gimbalCmd.set_posit_lift = 0.0f;

	core.parm_->armCmd.set_angle_Yaw = 0.0f;
	core.parm_->armCmd.set_angle_Pitch1 = 0.0f;
	core.parm_->armCmd.set_angle_Pitch2 = 0.0f;
	core.parm_->armCmd.set_angle_Roll = 0.0f;
	core.parm_->armCmd.set_angle_end_pitch = 0.0f;
	core.parm_->armCmd.set_angle_end_roll = 0.0f;

	while (keyboard.key_Ctrl) {
		// 用刺雷
		if (keyboard.mouse_L) {

			/*Step 1*/
			core.psubgantry_->subGantryCmd.setLiftPosit_L = 0.0f;
			core.psubgantry_->subGantryCmd.setLiftPosit_R = 0.0f;
			core.psubgantry_->subGantryCmd.setStretchPosit_L = 0.0f;
			core.psubgantry_->subGantryCmd.setStretchPosit_R = 0.0f;
			core.psubgantry_->subGantryCmd.setPumpOn_Left = false;
			core.psubgantry_->subGantryCmd.setPumpOn_Right = false;

			core.pgimbal_->gimbalCmd.set_posit_lift = 0.0f;

			proc_waitMs(250);
			
			/* Wait for User Confirmation */
			cnt = timeout;
			core.parm_->armCmd.isAutoCtrl = false;
			core.psubgantry_->subGantryCmd.isAutoCtrl = false;
			core.pgimbal_->gimbalCmd.isAutoCtrl = false;
			while (cnt--) {
				if (keyboard.key_Ctrl) {
					if (keyboard.mouse_L) break;
					if (keyboard.mouse_R) goto proc_exit;
				}
				proc_waitMs(5);
			}
			if (cnt == 0) goto proc_exit;

			/*Step 2*/
			core.parm_->armCmd.isAutoCtrl = true;
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.pgimbal_->gimbalCmd.isAutoCtrl = true;

			core.psubgantry_->subGantryCmd.setStretchPosit_L = SUB_GANTRY_STRETCH_PHYSICAL_RANGE_L;
			core.psubgantry_->subGantryCmd.setStretchPosit_R = SUB_GANTRY_STRETCH_PHYSICAL_RANGE_R;
			core.psubgantry_->subGantryCmd.setPumpOn_Left = true;
			core.psubgantry_->subGantryCmd.setPumpOn_Right = true;
			proc_waitMs(250);

			/* Wait for User Confirmation */
			cnt = timeout;
			core.parm_->armCmd.isAutoCtrl = false;
			core.psubgantry_->subGantryCmd.isAutoCtrl = false;
			core.pgimbal_->gimbalCmd.isAutoCtrl = false;
			while (cnt--) {
				if (keyboard.key_Ctrl) {
					if (keyboard.mouse_L) break;
					if (keyboard.mouse_R) goto proc_exit;
				}
				proc_waitMs(5);
			}
			if (cnt == 0) goto proc_exit;

			/*Step 3*/
			core.parm_->armCmd.isAutoCtrl = true;
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.pgimbal_->gimbalCmd.isAutoCtrl = true;

			core.psubgantry_->subGantryCmd.setLiftPosit_L = SUB_GANTRY_LIFT_PHYSICAL_RANGE_L;
			core.psubgantry_->subGantryCmd.setLiftPosit_R = SUB_GANTRY_LIFT_PHYSICAL_RANGE_R;
			proc_waitUntilWithTimeout(
				(core.psubgantry_->subGantryInfo.isPositArrived_Lift_L &&
				 core.psubgantry_->subGantryInfo.isPositArrived_Lift_R),
				3000
			);
			proc_waitMs(500);

			core.psubgantry_->subGantryCmd.setStretchPosit_L = 0.0f;
			core.psubgantry_->subGantryCmd.setStretchPosit_R = 0.0f;
			proc_waitMs(250);

			/* Wait for User Confirmation */
			cnt = timeout;
			core.parm_->armCmd.isAutoCtrl = false;
			core.psubgantry_->subGantryCmd.isAutoCtrl = false;
			core.pgimbal_->gimbalCmd.isAutoCtrl = false;
			while (cnt--) {
				if (keyboard.key_Ctrl) {
					if (keyboard.mouse_L) break;
					if (keyboard.mouse_R) goto proc_exit;
				}
				proc_waitMs(5);
			}
			if (cnt == 0) goto proc_exit;

			/*Step 4*/
			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 0.0f;
			core.parm_->armCmd.set_angle_Pitch2 = 0.0f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = 0.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;
			proc_waitMs(250);

			goto proc_exit;
		}
		
		// 用机械臂
		if (keyboard.mouse_R) {
			/*Step 1*/
			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 0.0f;
			core.parm_->armCmd.set_angle_Pitch2 = 0.0f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = 0.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;

			core.psubgantry_->subGantryCmd.setLiftPosit_L = SUB_GANTRY_LIFT_PHYSICAL_RANGE_L;
			core.psubgantry_->subGantryCmd.setLiftPosit_R = SUB_GANTRY_LIFT_PHYSICAL_RANGE_R;
			core.psubgantry_->subGantryCmd.setStretchPosit_L = 0.0f;
			core.psubgantry_->subGantryCmd.setStretchPosit_R = 0.0f;

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true;

			proc_waitMs(250);

			/* 选择 0 或 15度*/
			cnt = timeout;
			core.parm_->armCmd.isAutoCtrl = false;
			core.psubgantry_->subGantryCmd.isAutoCtrl = false;
			core.pgimbal_->gimbalCmd.isAutoCtrl = false;
			while (cnt--) {
				if (keyboard.key_Ctrl) {
					if (keyboard.mouse_L) {
						core.parm_->armCmd.set_angle_Yaw = -13.5f;
						break;
					}
					else if (keyboard.mouse_R) {
						core.parm_->armCmd.set_angle_Yaw = 0.0f;
						break;
					}
				}
				proc_waitMs(5);
			}
			if (cnt == 0) goto proc_exit;

			/* Wait for User Confirmation */
			cnt = timeout;
			core.parm_->armCmd.isAutoCtrl = false;
			core.psubgantry_->subGantryCmd.isAutoCtrl = false;
			core.pgimbal_->gimbalCmd.isAutoCtrl = false;
			while (cnt--) {
				if (keyboard.key_Ctrl) {
					if (keyboard.mouse_L) break;
					if (keyboard.mouse_R) goto proc_exit;
				}
				proc_waitMs(5);
			}
			if (cnt == 0) goto proc_exit;

			/*Step 2*/
			core.parm_->armCmd.isAutoCtrl = true;
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.pgimbal_->gimbalCmd.isAutoCtrl = true;

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true;
			proc_waitMs(750);

			do {
				proc_waitMs(1);
				core.parm_->armCmd.set_angle_Pitch2 -= 14.0 / core.freq; 
			}while (core.parm_->armCmd.set_angle_Pitch2 > 63.55f);

			/* Wait for User Confirmation */
			cnt = timeout;
			core.parm_->armCmd.isAutoCtrl = false;
			core.psubgantry_->subGantryCmd.isAutoCtrl = false;
			core.pgimbal_->gimbalCmd.isAutoCtrl = false;
			while (cnt--) {
				if (keyboard.key_Ctrl) {
					if (keyboard.mouse_L) break;
					if (keyboard.mouse_R) goto proc_exit;
				}
				proc_waitMs(5);
			}
			if (cnt == 0) goto proc_exit;

			/*Step 3*/
			core.parm_->armCmd.isAutoCtrl = true;
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.pgimbal_->gimbalCmd.isAutoCtrl = true;

			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 30.2f;
			core.parm_->armCmd.set_angle_Pitch2 = 22.0f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -90.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;

			core.pgimbal_->gimbalCmd.set_posit_lift = 0.0f;

			goto proc_exit;
		}

		proc_waitMs(5);

	}

// 退出
proc_exit:
	core.parm_->armCmd.isAutoCtrl = false;
	core.psubgantry_->subGantryCmd.isAutoCtrl = false;
	core.pchassis_->chassisCmd.isAutoCtrl = false;
	core.pgimbal_->gimbalCmd.isAutoCtrl = false;
	core.autoCtrlTaskHandle_ = nullptr;
	core.currentAutoCtrlProcess_ = EAutoCtrlProcess::NONE;
	proc_return();

}

} // namespace my_engineer
