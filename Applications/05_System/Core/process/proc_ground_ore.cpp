/******************************************************************************
 * @brief        
 * 
 * @file         proc_ground_ore.cpp
 * @author       Fish_Joe (2328339747@qq.com)
 * @version      V1.0
 * @date         2025-03-19
 * 
 * @copyright    Copyright (c) 2025
 * 
 ******************************************************************************/

#include "Core.hpp"

namespace my_engineer {

/**
 * @brief 创建地面矿石任务
 * 
 * @param argument 
 */
void CSystemCore::StartGroundOreTask(void *arg) {

	if (arg == nullptr) proc_return();

	// 获取SystemCore句柄
	auto &core = *reinterpret_cast<CSystemCore *>(arg);
	auto &keyboard = SysRemote.remoteInfo.keyboard;
	auto cnt = 0;
	const auto timeout = 60000 / 5; // unit: ms

	while (keyboard.key_Ctrl) {

		if (keyboard.mouse_L) {

			/*step 1*/
			core.psubgantry_->subGantryCmd.setLiftPosit_L = 88.0f;
			core.psubgantry_->subGantryCmd.setLiftPosit_R = 88.0f;

			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 83.76f;
			core.parm_->armCmd.set_angle_Pitch2 = 29.73f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -93.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true;

			proc_waitMs(500);
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

			/*step 2*/
			core.parm_->armCmd.isAutoCtrl = true;
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.pgimbal_->gimbalCmd.isAutoCtrl = true;
			
			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 96.0f;
			core.parm_->armCmd.set_angle_Pitch2 = 18.799f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -93.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;
			proc_waitMs(1000);
			
			core.pgimbal_->gimbalCmd.set_posit_lift = 10.0f;         ///< Pull up the gimbal

			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 30.2f;
			core.parm_->armCmd.set_angle_Pitch2 = 22.0f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -90.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;
			proc_waitMs(250);

			core.use_Controller_ = true; // Enable controller usage
      
      		goto proc_exit;
		}

		if (keyboard.mouse_R) {

			/*step 1*/
			core.psubgantry_->subGantryCmd.setLiftPosit_L = 88.0f;
			core.psubgantry_->subGantryCmd.setLiftPosit_R = 88.0f;

			core.parm_->armCmd.set_angle_Pitch1 = 83.76f;
			core.parm_->armCmd.set_angle_Pitch2 = 29.73f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -93.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true;

			proc_waitMs(500);
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

			/*Step 2 */
			core.parm_->armCmd.isAutoCtrl = true;
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.pgimbal_->gimbalCmd.isAutoCtrl = true;
			
			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 96.0f;
			core.parm_->armCmd.set_angle_Pitch2 = 18.799f;
			core.parm_->armCmd.set_angle_Roll  = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -93.0f;
			core.parm_->armCmd.set_angle_end_roll  = 0.0f;
			// proc_waitUntil(core.parm_->armInfo.isAngleArrived_Pitch1 == true && core.parm_->armInfo.isAngleArrived_Pitch2 == true);
			proc_waitMs(1000);

			core.parm_->armCmd.set_angle_Pitch1 = 85.5f;
			core.parm_->armCmd.set_angle_Pitch2 = 26.79f;
			proc_waitMs(500);
			core.parm_->armCmd.set_angle_Roll  = -40.0f;
			proc_waitMs(500);
			proc_waitUntil(core.parm_->armInfo.isAngleArrived_Pitch1 == true && core.parm_->armInfo.isAngleArrived_Roll == true);
			core.parm_->armCmd.set_angle_Pitch1 = 96.0f;

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = false;
			proc_waitMs(250);
			core.parm_->armCmd.set_angle_Yaw = -25.0f;

			proc_waitMs(500);
			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true;

			core.psubgantry_->subGantryCmd.setLiftPosit_L = 52.2f;
			core.psubgantry_->subGantryCmd.setLiftPosit_R = 52.2f;

			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 88.36f;
			core.parm_->armCmd.set_angle_Pitch2 = 26.8f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -93.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;
			proc_waitMs(500);
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
			core.parm_->armCmd.set_angle_Pitch1 = 96.0f;
			core.parm_->armCmd.set_angle_Pitch2 = 18.799f;
			core.parm_->armCmd.set_angle_Roll  = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -93.0f;
			core.parm_->armCmd.set_angle_end_roll  = 0.0f;
			// proc_waitUntil(core.parm_->armInfo.isAngleArrived_Pitch1 == true && core.parm_->armInfo.isAngleArrived_Pitch2 == true);
			proc_waitMs(1000);
			core.pgimbal_->gimbalCmd.set_posit_lift = 100.0f;         ///< Pull up the gimbal

			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 30.2f;
			core.parm_->armCmd.set_angle_Pitch2 = 22.0f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -90.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;
			proc_waitMs(250);

			core.use_Controller_ = true; // Enable controller usage

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
