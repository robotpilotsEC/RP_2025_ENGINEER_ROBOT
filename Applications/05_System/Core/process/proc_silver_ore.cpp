/******************************************************************************
 * @brief        
 * 
 * @file         proc_silver_ore.cpp
 * @author       Fish_Joe (2328339747@qq.com)
 * @version      V1.0
 * @date         2025-07-13
 * 
 * @copyright    Copyright (c) 2025
 * 
 ******************************************************************************/

#include "Core.hpp"

namespace my_engineer {

/******************************************************************************
 * @brief    银矿任务
 ******************************************************************************/
void CSystemCore::StartSilverOreTask(void *arg) {

	if (arg == nullptr) proc_return();

	/* Get System Core Handle */
	auto &core = *reinterpret_cast<CSystemCore *>(arg);
	auto &keyboard = SysRemote.remoteInfo.keyboard;
	const auto timeout = 60000 / 5;    // unit: ms
	auto cnt = 0;

	core.parm_->armCmd.isAutoCtrl = true;
	core.psubgantry_->subGantryCmd.isAutoCtrl = true;
	core.pgimbal_->gimbalCmd.isAutoCtrl = true;

	/*step 1*/
	core.pgimbal_->gimbalCmd.set_posit_lift = GIMBAL_LIFT_PHYSICAL_RANGE;    ///< Pull up the gimbal

	core.psubgantry_->subGantryCmd.setLiftPosit_L = SUB_GANTRY_LIFT_PHYSICAL_RANGE_L;
	core.psubgantry_->subGantryCmd.setLiftPosit_R = SUB_GANTRY_LIFT_PHYSICAL_RANGE_R;
	core.parm_->armCmd.set_angle_Yaw = 0.0f;
	core.parm_->armCmd.set_angle_Pitch1 = 88.36f;
	core.parm_->armCmd.set_angle_Pitch2 = 26.8f;
	core.parm_->armCmd.set_angle_Roll = 0.0f;
	core.parm_->armCmd.set_angle_end_pitch = -93.0f;
	core.parm_->armCmd.set_angle_end_roll = 0.0f;

	core.psubgantry_->subGantryCmd.setPumpOn_Arm = true; ///< Set the arm pump on

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
	proc_waitMs(250);
	
	// /* Wait for User Confirmation */
	// cnt = timeout;
	// core.parm_->armCmd.isAutoCtrl = false; 
	// core.psubgantry_->subGantryCmd.isAutoCtrl = false;
	// core.pgimbal_->gimbalCmd.isAutoCtrl = false;   
	// while (cnt--) {
	//   if (keyboard.key_Ctrl) {
	//     if (keyboard.mouse_L) break;
	//     if (keyboard.mouse_R) goto proc_exit;
	//   }
	//   proc_waitMs(5);
	// }
	// if (cnt == 0) goto proc_exit;

	// /*step 3*/
	// core.parm_->armCmd.isAutoCtrl = true;
	// core.psubgantry_->subGantryCmd.isAutoCtrl = true;
	// core.pgimbal_->gimbalCmd.isAutoCtrl = true;

	do {
		proc_waitMs(1);
		if(core.parm_->armInfo.angle_Pitch1 >= 67.0f)
			core.parm_->armCmd.set_angle_Pitch1 -= 30.0f / core.freq;
		if(core.parm_->armInfo.angle_Pitch2 <= 47.2f)
			core.parm_->armCmd.set_angle_Pitch2 += 24.0f / core.freq;
	} while (core.parm_->armCmd.set_angle_Pitch1 >= 67.0f && core.parm_->armCmd.set_angle_Pitch2 <= 47.2f);
	core.parm_->armCmd.set_angle_Pitch1 = 67.0f;
	core.parm_->armCmd.set_angle_Pitch2 = 47.2f;
	// /* Wait for User Confirmation */
	// cnt = timeout;
	// core.parm_->armCmd.isAutoCtrl = false;  
	// core.psubgantry_->subGantryCmd.isAutoCtrl = false; 
	// core.pgimbal_->gimbalCmd.isAutoCtrl = false;   
	// while (cnt--) {
	//   if (keyboard.key_Ctrl) {
	//     if (keyboard.mouse_L) break;
	//     if (keyboard.mouse_R) goto proc_exit;
	//   }
	//   proc_waitMs(5);
	// }
	// if (cnt == 0) goto proc_exit;

	/*step 4*/
	// core.parm_->armCmd.isAutoCtrl = true;
	// core.psubgantry_->subGantryCmd.isAutoCtrl = true;
	// core.pgimbal_->gimbalCmd.isAutoCtrl = true;

	// core.pgimbal_->gimbalCmd.setStep_Pitch = 1;         ///< Pull up the gimbal

	// core.parm_->armCmd.setAngle_joint1_yaw = 0.0f;
	// core.parm_->armCmd.setAngle_joint2_pitch = 30.2f;
	// core.parm_->armCmd.setAngle_joint3_pitch = 22.0f;
	// core.parm_->armCmd.setAngle_joint4_roll = 0.0f;
	// core.parm_->armCmd.setAngle_joint5_pitch = -90.0f;
	// core.parm_->armCmd.setAngle_joint6_roll = 0.0f;

	// core.psubgantry_->subGantryCmd.setPosit_Lift_R = 49.8f;
	// core.psubgantry_->subGantryCmd.setPosit_Lift_L = 52.5f;
	// proc_waitUntil(core.psubgantry_->subGantryInfo.isPositArrived_Lift_R == true 
	//               && core.psubgantry_->subGantryInfo.isPositArrived_Lift_L == true);
	// proc_waitMs(250);

/* Process Exit */
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
