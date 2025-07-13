/******************************************************************************
 * @brief        	
 * 
 * @file         proc_pop.cpp
 * @author       Fish_Joe (2328339747@qq.com)
 * @version      V1.0
 * @date         2025-05-10
 * 
 * @copyright    Copyright (c) 2025
 * 
 ******************************************************************************/

#include "Core.hpp"

namespace my_engineer {

/**
 * @brief 创建POP任务
 * 
 * @param argument 
 */
void CSystemCore::StartPopOreTask(void *arg) {

	if (arg == nullptr) proc_return();

	// 获取SystemCore句柄
	auto &core = *reinterpret_cast<CSystemCore *>(arg);
	auto &keyboard = SysRemote.remoteInfo.keyboard;
	auto cnt = 0;
	const auto timeout = 60000 / 5; // unit: ms

	while (keyboard.key_Ctrl) {

		if (keyboard.mouse_L) {

			/*step 1*/
			core.psubgantry_->subGantryCmd.setStretchPosit_L = 170.9f;
			core.psubgantry_->subGantryCmd.setLiftPosit_L = 0.0f;
			proc_waitMs(250);
			/*Set RoboticArm*/
			core.parm_->armCmd.set_angle_Yaw   = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 82.8f;
			core.parm_->armCmd.set_angle_Pitch2 = 27.06f;
			core.parm_->armCmd.set_angle_Roll  = 90.0f;
			core.parm_->armCmd.set_angle_end_pitch = -92.0f;
			core.parm_->armCmd.set_angle_end_roll  = -2.0f;
			proc_waitMs(250);
			core.psubgantry_->subGantryCmd.setPumpOn_Arm = false;
			core.psubgantry_->subGantryCmd.setPumpOn_Left = true;

			/*step 2*/
			proc_waitUntilWithTimeout(
				(core.parm_->armInfo.isAngleArrived_Pitch1 == true &&
				core.parm_->armInfo.isAngleArrived_Pitch2 == true), 5000
			);
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.parm_->armCmd.isAutoCtrl = true;
			// core.pgimbal_->gimbalCmd.isAutoCtrl = true;      

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true;
			core.psubgantry_->subGantryCmd.setPumpOn_Left = true;
			proc_waitMs(250);
			
			/*Set RoboticArm*/
			core.parm_->armCmd.set_angle_Yaw   = -22.47f;
			core.parm_->armCmd.set_angle_Pitch1 = 82.8f;
			core.parm_->armCmd.set_angle_Pitch2 = 27.06f;
			core.parm_->armCmd.set_angle_Roll  = 90.0f;
			core.parm_->armCmd.set_angle_end_pitch = -92.0f;
			core.parm_->armCmd.set_angle_end_roll  = -2.0f;
			proc_waitMs(250);

			/* Wait for User Confirmation */
			cnt = timeout;
			core.psubgantry_->subGantryCmd.isAutoCtrl = false;
			core.parm_->armCmd.isAutoCtrl = false;
			core.pgimbal_->gimbalCmd.isAutoCtrl = false;
			while (cnt--) {
				if (keyboard.key_Ctrl) {
					if (keyboard.mouse_L) break;
					if (keyboard.mouse_R) goto proc_exit;
				}
				proc_waitMs(5);
			}
			if (cnt == 0) goto proc_exit;

			/*step 3*/
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.parm_->armCmd.isAutoCtrl = true;
			// core.pgimbal_->gimbalCmd.isAutoCtrl = true;

			core.psubgantry_->subGantryCmd.setPumpOn_Left = false;
			proc_waitMs(250);

			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 30.2f;
			core.parm_->armCmd.set_angle_Pitch2 = 22.0f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -90.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;

			proc_waitMs(250);
			core.psubgantry_->subGantryCmd.setStretchPosit_L = 0.0f;
			proc_waitMs(500);

			core.use_Controller_ = true;

			goto proc_exit;
		}

		if (keyboard.mouse_R) {

			/*step 1*/
			core.psubgantry_->subGantryCmd.setStretchPosit_R = 117.0f;
			core.psubgantry_->subGantryCmd.setLiftPosit_R = 0.0f;
			proc_waitMs(250);
			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 72.4f;
			core.parm_->armCmd.set_angle_Pitch2 = 19.81f;
			core.parm_->armCmd.set_angle_Roll = -90.0f;
			core.parm_->armCmd.set_angle_end_pitch = -93.0f;
			core.parm_->armCmd.set_angle_end_roll = -0.0f;
			proc_waitMs(250);
			core.psubgantry_->subGantryCmd.setPumpOn_Arm = false; // 关闭机械臂气泵
			core.psubgantry_->subGantryCmd.setPumpOn_Right = true; // 启动右气泵

			/*step 2*/
			proc_waitUntilWithTimeout(
				(core.parm_->armInfo.isAngleArrived_Pitch1 == true &&
				core.parm_->armInfo.isAngleArrived_Pitch2 == true), 5000
			);
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.parm_->armCmd.isAutoCtrl = true;
			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true; // 启动机械臂气泵
			core.psubgantry_->subGantryCmd.setPumpOn_Right = true; // 启动右气泵
			proc_waitMs(250);
			
			core.parm_->armCmd.set_angle_Yaw = 16.5f;
			core.parm_->armCmd.set_angle_Pitch1 = 72.4f;
			core.parm_->armCmd.set_angle_Pitch2 = 19.81f;
			core.parm_->armCmd.set_angle_Roll = -90.0f;
			core.parm_->armCmd.set_angle_end_pitch = -93.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;
			proc_waitMs(250);

			/* Wait for User Confirmation */
			cnt = timeout;
			core.parm_->armCmd.isAutoCtrl = false;      // Unlock Arm
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

			/*step 3*/
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.parm_->armCmd.isAutoCtrl = true;

			core.psubgantry_->subGantryCmd.setPumpOn_Right = true;
			proc_waitMs(250);

			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_Pitch1 = 30.2f;
			core.parm_->armCmd.set_angle_Pitch2 = 22.0f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -90.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;

			proc_waitMs(250);
			core.psubgantry_->subGantryCmd.setStretchPosit_R = 0.0f;
			proc_waitMs(500);

			core.use_Controller_ = true;

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
		