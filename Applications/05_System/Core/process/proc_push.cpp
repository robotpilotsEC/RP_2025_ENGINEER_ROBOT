/******************************************************************************
 * @brief        
 * 
 * @file         proc_push.cpp
 * @author       Fish_Joe (2328339747@qq.com)
 * @version      V1.0
 * @date         2025-05-10
 * 
 * @copyright    Copyright (c) 2025
 * 
 ******************************************************************************/

#include "Core.hpp"

namespace my_engineer {

/******************************************************************************
 * @brief    储矿
 ******************************************************************************/
void CSystemCore::StartPushOreTask(void *arg) {

	if (arg == nullptr) proc_return();

	// 获取SystemCore句柄
	auto &core = *reinterpret_cast<CSystemCore *>(arg);
	auto &keyboard = SysRemote.remoteInfo.keyboard;
	auto cnt = 0;
	const auto timeout = 60000 / 5; // unit: ms

	while (keyboard.key_Ctrl) {

		if (keyboard.mouse_L) {

			/*step 1*/
			core.psubgantry_->subGantryCmd.setStretchPosit_L = 50.0f;
			core.psubgantry_->subGantryCmd.setLiftPosit_L = SUB_GANTRY_LIFT_PHYSICAL_RANGE_L;
			proc_waitMs(250);

			/*Set Arm*/
			if(core.parm_->armInfo.angle_Pitch1 <= 20.0f && core.parm_->armInfo.angle_Pitch2 <= 10.0f){
				core.parm_->armCmd.set_angle_Yaw = 0.0f;
				core.parm_->armCmd.set_angle_Pitch1 = 77.08f;
				core.parm_->armCmd.set_angle_Pitch2 = 30.1f;
				core.parm_->armCmd.set_angle_Roll = 90.0f;
				core.parm_->armCmd.set_angle_end_pitch = -98.0f;
				core.parm_->armCmd.set_angle_end_roll = 0.0f;
			}
			else{
				core.parm_->armCmd.set_angle_Roll = 90.0f;
				proc_waitUntilWithTimeout(
					core.parm_->armInfo.isAngleArrived_Roll == true, 5000
				);
				core.parm_->armCmd.set_angle_Yaw = 0.0f;
				core.parm_->armCmd.set_angle_Pitch1 = 77.08f;
				core.parm_->armCmd.set_angle_Pitch2 = 30.1f;
				core.parm_->armCmd.set_angle_end_pitch = -98.0f;
				core.parm_->armCmd.set_angle_end_roll = 0.0f;

				
			}

			proc_waitMs(250);
			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true; // 启动机械臂气泵
			core.psubgantry_->subGantryCmd.setPumpOn_Left = false; // 关闭左气泵

			/* Step 2 */
			proc_waitUntilWithTimeout(
				core.parm_->armInfo.isAngleArrived_Pitch1 == true &&
				core.parm_->armInfo.isAngleArrived_Pitch2 == true, 5000
			);
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.parm_->armCmd.isAutoCtrl = true;
			core.pgimbal_->gimbalCmd.isAutoCtrl = true;

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true; // 启动机械臂气泵
			core.psubgantry_->subGantryCmd.setPumpOn_Left = true; // 启动左气泵
			proc_waitMs(500);
			core.parm_->armCmd.set_angle_Yaw = -21.35f;
			proc_waitMs(250);
			core.psubgantry_->subGantryCmd.setStretchPosit_L = 200.0f;

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

			/* Step 3 */
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.parm_->armCmd.isAutoCtrl = true;
			core.pgimbal_->gimbalCmd.isAutoCtrl = true;

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = false; // 关闭机械臂气泵
			proc_waitMs(500);

			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			proc_waitUntil(core.parm_->armInfo.isAngleArrived_Yaw == true);
			core.parm_->armCmd.set_angle_Pitch1 = 30.2f;
			core.parm_->armCmd.set_angle_Pitch2 = 22.0f;
			core.parm_->armCmd.set_angle_Roll = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -90.0f;
			core.parm_->armCmd.set_angle_end_roll = 0.0f;

			proc_waitMs(250);
			core.psubgantry_->subGantryCmd.setStretchPosit_L = 0.0f;

			goto proc_exit;
		}

		if (keyboard.mouse_R) {

			/*step 1*/
			core.psubgantry_->subGantryCmd.setStretchPosit_R = 0.0f;
			core.psubgantry_->subGantryCmd.setLiftPosit_R = SUB_GANTRY_LIFT_PHYSICAL_RANGE_R;
			proc_waitMs(250);

			/*Set Arm*/
			if(core.parm_->armInfo.angle_Pitch1 <= 20.0f && core.parm_->armInfo.angle_Pitch2 <= 10.0f) {
				core.parm_->armCmd.set_angle_Pitch1 = 59.062f;
				core.parm_->armCmd.set_angle_Pitch2 = 55.524f;
				proc_waitUntilWithTimeout(
					core.parm_->armInfo.isAngleArrived_Pitch1 == true &&
					core.parm_->armInfo.isAngleArrived_Pitch2 == true, 5000
				);
			}

			do {
				core.parm_->armCmd.set_angle_Roll -= 120.0f / core.freq;
				proc_waitMs(1);
			} while (core.parm_->armCmd.set_angle_Roll > -90.824f);
			core.parm_->armCmd.set_angle_Pitch1 = 59.062f;
			core.parm_->armCmd.set_angle_Pitch2 = 46.524f;
			core.parm_->armCmd.set_angle_Yaw = 0.0f;
			core.parm_->armCmd.set_angle_end_pitch = -110.970f;
			core.parm_->armCmd.set_angle_end_roll = -17.280f;

			proc_waitUntilWithTimeout(
				core.parm_->armInfo.isAngleArrived_Pitch1 == true &&
				core.parm_->armInfo.isAngleArrived_Pitch2 == true, 5000
			);

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = true; // 启动机械臂气泵
			core.psubgantry_->subGantryCmd.setPumpOn_Right = true; // 启动右气泵
			proc_waitMs(250);

			core.parm_->armCmd.set_angle_Yaw = -6.2f;
			proc_waitMs(250);
			core.psubgantry_->subGantryCmd.setStretchPosit_R = 70.00f;

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

			/* Step 3 */
			core.psubgantry_->subGantryCmd.isAutoCtrl = true;
			core.parm_->armCmd.isAutoCtrl = true;
			core.pgimbal_->gimbalCmd.isAutoCtrl = true;

			core.psubgantry_->subGantryCmd.setPumpOn_Arm = false; // 关闭机械臂气泵
			proc_waitMs(500);

			/*Set Arm*/
			core.parm_->armCmd.set_angle_Yaw = 10.f;
			proc_waitMs(250);
			core.parm_->armCmd.set_angle_Pitch1 = 50.0f;
			core.parm_->armCmd.set_angle_Pitch2 = 40.0f;
			core.parm_->armCmd.set_angle_Roll = -2.178f;
			core.parm_->armCmd.set_angle_end_pitch = -69.355f;
			core.parm_->armCmd.set_angle_end_roll = 0.000f;
			core.psubgantry_->subGantryCmd.setStretchPosit_R = 0.0f;
			proc_waitMs(250);
			core.parm_->armCmd.set_angle_Yaw = 0.0f;

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
