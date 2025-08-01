/*
 * @Description: 
 * @Author: Sassinak
 * @version: 
 * @Date: 2025-07-23 17:26:29
 * @LastEditors: Sassinak
 * @LastEditTime: 2025-07-27 15:03:26
 */

/******************************************************************************
 * @brief        
 * 
 * @file         proc_return_drive.cpp
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
 * @brief    返回任务
 ******************************************************************************/
void CSystemCore::StartReturnDriveTask(void *arg) {

	if (arg == nullptr) proc_return();

	/* Get System Core Handle */
	auto &core = *reinterpret_cast<CSystemCore *>(arg);
	const auto timeout = 60000 / 5;    // unit: ms
	auto cnt = 0;

	core.parm_->armCmd.isAutoCtrl = true;
	core.psubgantry_->subGantryCmd.isAutoCtrl = true;
	core.pgimbal_->gimbalCmd.isAutoCtrl = true;
	
	/*Set SubGantry*/
	core.psubgantry_->subGantryCmd.setStretchPosit_L = 0.0f;
	core.psubgantry_->subGantryCmd.setLiftPosit_L = 0.0f;
	core.psubgantry_->subGantryCmd.setStretchPosit_R = 0.0f;
	core.psubgantry_->subGantryCmd.setLiftPosit_R = 0.0f;
	
	/*Set Arm*/
	core.parm_->armCmd.set_angle_Yaw = -0.585f;
	core.parm_->armCmd.set_angle_Pitch1 = 20.644f;
	core.parm_->armCmd.set_angle_Pitch2 = 29.297f;
	core.parm_->armCmd.set_angle_Roll = -2.178f;
	core.parm_->armCmd.set_angle_end_pitch = -60.745f;
	core.parm_->armCmd.set_angle_end_roll = -0.720f;

	/*Set Gimbal*/
	core.pgimbal_->gimbalCmd.set_posit_lift = GIMBAL_LIFT_PHYSICAL_RANGE;  ///< Pull up the gimbal

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
