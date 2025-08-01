/**
 * @file Core.cpp
 * @author Fish_Joe (2328339747@qq.com)
 * @brief 系统核心源文件
 * @version 1.0
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Core.hpp"

namespace my_engineer {

// 实例化系统核心
CSystemCore SystemCore;

/**
 * @brief 初始化系统核心
 * 
 * @return EAppStatus 
 */
EAppStatus CSystemCore::InitSystemCore() {
    
    // 启动通信接口发送
    for (const auto &item : InterfaceIDMap) {
        item.second->StartTransfer();
    }


    // 初始化所有系统
    CSystemRemote::SSystemInitParam_Remote remoteInitParam;
    remoteInitParam.systemID = ESystemID::SYS_REMOTE;
    remoteInitParam.remoteDevID = EDeviceID::DEV_RC_DR16;
    SysRemote.InitSystem(&remoteInitParam);

    CSystemVision::SSystemInitParam_Vision visionInitParam;
    visionInitParam.systemID = ESystemID::SYS_VISION;
    visionInitParam.visionDevID = EDeviceID::DEV_VISION;
    SysVision.InitSystem(&visionInitParam);

    CSystemReferee::SSystemInitParam_Referee refereeInitParam;
    refereeInitParam.systemID = ESystemID::SYS_REFEREE;
    refereeInitParam.refereeDevID = EDeviceID::DEV_RM_REFEREE;
    SysReferee.InitSystem(&refereeInitParam);

    CSystemControllerLink::SSystemInitParam_ControllerLink controllerLinkInitParam;
    controllerLinkInitParam.systemID = ESystemID::SYS_CONTROLLER_LINK;
    controllerLinkInitParam.controllerLinkDevID = EDeviceID::DEV_CONTROLLER_LINK;
    SysControllerLink.InitSystem(&controllerLinkInitParam);

    CSystemESP32::SSystemInitParam_ESP32 esp32InitParam;
    esp32InitParam.systemID = ESystemID::SYS_ESP32;
    esp32InitParam.esp32DevID = EDeviceID::DEV_ESP32;
    SysESP32.InitSystem(&esp32InitParam);

    // 获取模块的指针
    pchassis_ = reinterpret_cast<CModChassis *>(ModuleIDMap.at(EModuleID::MOD_CHASSIS));
    pgimbal_ = reinterpret_cast<CModGimbal *>(ModuleIDMap.at(EModuleID::MOD_GIMBAL));
    // pgantry_ = reinterpret_cast<CModGantry *>(ModuleIDMap.at(EModuleID::MOD_GANTRY));
    // pclimber_ = reinterpret_cast<CModClimber *>(ModuleIDMap.at(EModuleID::MOD_CLIMBER));
    psubgantry_ = reinterpret_cast<CModSubGantry *>(ModuleIDMap.at(EModuleID::MOD_SUBGANTRY));
    parm_ = reinterpret_cast<CModArm *>(ModuleIDMap.at(EModuleID::MOD_ARM));
    // pmantis_ = reinterpret_cast<CModMantis *>(ModuleIDMap.at(EModuleID::MOD_MANTIS));

    proc_waitMs(1200); // 等待系统初始化完成

    coreStatus = APP_OK;

    return APP_OK;
}

/**
 * @brief 更新处理
 * 
 */
void CSystemCore::UpdateHandler_() {

    // 检查系统核心状态
    if (coreStatus == APP_RESET) return;

    // 检查遥控器系统状态
    if (SysRemote.systemStatus == APP_RESET) return;

    static bool last_use_Controller = false;
    static uint8_t zx_count = 0;
    static bool zx_flag = false;

    static uint8_t print_cnt = 0;
    if (print_cnt-- == 0) {
        print_cnt = 200;
        Print("------------------------------\n");
        Print("Arm_Yaw_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(parm_->armCmd.set_angle_Yaw), static_cast<int>(parm_->armInfo.angle_Yaw),
              static_cast<int>(parm_->armInfo.angle_Yaw - parm_->armCmd.set_angle_Yaw));
        Print("Arm_Pitch1_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(parm_->armCmd.set_angle_Pitch1), static_cast<int>(parm_->armInfo.angle_Pitch1),
              static_cast<int>(parm_->armInfo.angle_Pitch1 - parm_->armCmd.set_angle_Pitch1));
        Print("Arm_Pitch2_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(parm_->armCmd.set_angle_Pitch2), static_cast<int>(parm_->armInfo.angle_Pitch2),
              static_cast<int>(parm_->armInfo.angle_Pitch2 - parm_->armCmd.set_angle_Pitch2));
        Print("Arm_Roll_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(parm_->armCmd.set_angle_Roll), static_cast<int>(parm_->armInfo.angle_Roll),
              static_cast<int>(parm_->armInfo.angle_Roll - parm_->armCmd.set_angle_Roll));
        Print("Arm_EndPitch_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(parm_->armCmd.set_angle_end_pitch), static_cast<int>(parm_->armInfo.angle_end_pitch),
              static_cast<int>(parm_->armInfo.angle_end_pitch - parm_->armCmd.set_angle_end_pitch));
        Print("Arm_EndRoll_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(parm_->armCmd.set_angle_end_roll), static_cast<int>(parm_->armInfo.angle_end_roll),
              static_cast<int>(parm_->armInfo.angle_end_roll - parm_->armCmd.set_angle_end_roll));
        Print("Subgantry_Stretch_L_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(psubgantry_->subGantryCmd.setStretchPosit_L), static_cast<int>(psubgantry_->subGantryInfo.stretchPosit_L),
              static_cast<int>(psubgantry_->subGantryInfo.stretchPosit_L - psubgantry_->subGantryCmd.setStretchPosit_L));
        Print("Subgantry_Stretch_R_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(psubgantry_->subGantryCmd.setStretchPosit_R), static_cast<int>(psubgantry_->subGantryInfo.stretchPosit_R),
              static_cast<int>(psubgantry_->subGantryInfo.stretchPosit_R - psubgantry_->subGantryCmd.setStretchPosit_R));
        Print("Subgantry_Lift_L_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(psubgantry_->subGantryCmd.setLiftPosit_L), static_cast<int>(psubgantry_->subGantryInfo.liftPosit_L),
              static_cast<int>(psubgantry_->subGantryInfo.liftPosit_L - psubgantry_->subGantryCmd.setLiftPosit_L));
        Print("Subgantry_Lift_R_Cmd: %d, Info: %d, Err: %d\n",
              static_cast<int>(psubgantry_->subGantryCmd.setLiftPosit_R), static_cast<int>(psubgantry_->subGantryInfo.liftPosit_R),
              static_cast<int>(psubgantry_->subGantryInfo.liftPosit_R - psubgantry_->subGantryCmd.setLiftPosit_R));
    }

    bool zx = SysRemote.remoteInfo.keyboard.key_Z && SysRemote.remoteInfo.keyboard.key_X;
    if (SysRemote.remoteInfo.keyboard.key_Z && SysRemote.remoteInfo.keyboard.key_X) {
        zx_count++;
    }
    // 全部松开之后才清零计数器，否则会因为按下状态的抖动导致自定义控制器模式连续进出
    else if (SysRemote.remoteInfo.keyboard.key_Z || SysRemote.remoteInfo.keyboard.key_X == false) {
        zx_count = 0;
        zx_flag = false;
    }

    if (zx_count > 20 && zx_flag == false) {
        zx_flag = true;
        zx_count = 0;
        use_Controller_ = !use_Controller_;
        if (use_Controller_ == true) {
            // 根据当前在哪个自动任务中调整臂的初始角度
            if (currentAutoCtrlProcess_ == EAutoCtrlProcess::EXCHANGE) {

            }
            else {

            }
            SysControllerLink.robotInfo.controlled_by_controller = true;
            SysControllerLink.robotInfo.ask_return_flag = true;
            StopAutoCtrlTask_(); // 停止自动任务运行
        }
        if (use_Controller_ == false) {
            StartAutoCtrlTask_(EAutoCtrlProcess::RETURN_DRIVE);
        }
    }
    
    ControlFromEsp32_(); // ESP32控制

    if (use_Controller_ == true)
    {
        ControlFromController_();
    }
    else
    {
        // 左下右上键盘控制
        if (SysRemote.remoteInfo.remote.switch_L == 2
        && SysRemote.remoteInfo.remote.switch_R == 1)
        {
            ControlFromKeyboard_();
        }
        else
        {
            ControlFromRemote_();
        }
    }
    last_use_Controller = use_Controller_;
    
    if (SysRemote.ResetFlag)
    {
        RESET_SYSTEM();
    }

    // 拇指轮控制气泵
    if (SysRemote.remoteInfo.remote.thumbWheel > 50) {
        psubgantry_->subGantryCmd.setPumpOn_Left = true;
        psubgantry_->subGantryCmd.setPumpOn_Right = true;
        psubgantry_->subGantryCmd.setPumpOn_Arm = true;
    }
    else if (SysRemote.remoteInfo.remote.thumbWheel < -50) {
        psubgantry_->subGantryCmd.setPumpOn_Left = false;
        psubgantry_->subGantryCmd.setPumpOn_Right = false;
        psubgantry_->subGantryCmd.setPumpOn_Arm = false;
    }

}

/**
 * @brief 心跳处理
 * 
 */
void CSystemCore::HeartbeatHandler_() {
    // 检查系统核心状态
    if (coreStatus == APP_RESET) return;

    static auto lastRemoteState = APP_RESET;
    auto currentRemoteState = SysRemote.systemStatus;

    // 遥控器掉线
    if (lastRemoteState == APP_OK && currentRemoteState != APP_OK) {
        // 停止所有自动操作
        // StopAutoCtrlTask_();
        
        // 停止所有模块
        pchassis_->StopModule();
        pgimbal_->StopModule();
        psubgantry_->StopModule();
        parm_->StopModule();
        
    }

    lastRemoteState = currentRemoteState;
}

// 软件复位
void CSystemCore::RESET_SYSTEM() {

    pchassis_->StopModule();
    pgimbal_->StopModule();
    psubgantry_->StopModule();
    parm_->StopModule();

    // 给段延迟让电机收到停止指令
    static uint16_t resetCnt = 200;
    if (resetCnt-- != 0) {
        return ;
    }

    __set_FAULTMASK(1);
    NVIC_SystemReset();
}

EAppStatus CSystemCore::StartAutoCtrlTask_(EAutoCtrlProcess process) {

    if (currentAutoCtrlProcess_ != EAutoCtrlProcess::NONE)
        return APP_BUSY;

    StopAutoCtrlTask_();

    parm_->should_limit_yaw = 0;

    switch (process)
    {
        case EAutoCtrlProcess::NONE: {
            return APP_ERROR;
        }


        case EAutoCtrlProcess::EXCHANGE: {
            currentAutoCtrlProcess_ = EAutoCtrlProcess::EXCHANGE;
            xTaskCreate(StartExchangeTask, "Exchange Task",
                        512, this, proc_ModuleTaskPriority,
                        &autoCtrlTaskHandle_);
            return APP_OK;
        }

        case EAutoCtrlProcess::RETURN_DRIVE: {
            currentAutoCtrlProcess_ = EAutoCtrlProcess::RETURN_DRIVE;
            xTaskCreate(StartReturnDriveTask, "Return Drive Task",
                        512, this, proc_ModuleTaskPriority,
                        &autoCtrlTaskHandle_);
            return APP_OK;
        }

        case EAutoCtrlProcess::RETURN_ORIGIN: {
            currentAutoCtrlProcess_ = EAutoCtrlProcess::RETURN_ORIGIN;
            xTaskCreate(StartReturnOriginTask, "Return Origin Task",
                        512, this, proc_ModuleTaskPriority,
                        &autoCtrlTaskHandle_);
            return APP_OK;
        }

        case EAutoCtrlProcess::DOGHOLE: {
            currentAutoCtrlProcess_ = EAutoCtrlProcess::DOGHOLE;
            xTaskCreate(StartDogHoleTask, "Dog Hole Task",
                        512, this, proc_ModuleTaskPriority,
                        &autoCtrlTaskHandle_);
            return APP_OK;
        }

        case EAutoCtrlProcess::GROUND_ORE: {
            currentAutoCtrlProcess_ = EAutoCtrlProcess::GROUND_ORE;
            xTaskCreate(StartGroundOreTask, "Ground Ore Task",
                        512, this, proc_ModuleTaskPriority,
                        &autoCtrlTaskHandle_);
            return APP_OK;
        }

        case EAutoCtrlProcess::GOLD_ORE: {
            currentAutoCtrlProcess_ = EAutoCtrlProcess::GOLD_ORE;
            xTaskCreate(StartGoldOreTask, "Gold Ore Task",
                        512, this, proc_ModuleTaskPriority,
                        &autoCtrlTaskHandle_);
            return APP_OK;
        }

        case EAutoCtrlProcess::PUSH_ORE: {
            currentAutoCtrlProcess_ = EAutoCtrlProcess::PUSH_ORE;
            xTaskCreate(StartPushOreTask, "Push Ore Task",
                        512, this, proc_ModuleTaskPriority,
                        &autoCtrlTaskHandle_);
            return APP_OK;
        }

        case EAutoCtrlProcess::POP_ORE: {
            currentAutoCtrlProcess_ = EAutoCtrlProcess::POP_ORE;
            xTaskCreate(StartPopOreTask, "Pop Ore Task",
                        512, this, proc_ModuleTaskPriority,
                        &autoCtrlTaskHandle_);
            return APP_OK;
        }


        case EAutoCtrlProcess::SILVER_ORE: {
            currentAutoCtrlProcess_ = EAutoCtrlProcess::SILVER_ORE;
            xTaskCreate(StartSilverOreTask, "Silver Ore Task",
                        512, this, proc_ModuleTaskPriority,
                        &autoCtrlTaskHandle_);
            return APP_OK;
        }
        
        default: return APP_ERROR;
    }
}

EAppStatus CSystemCore::StopAutoCtrlTask_() {
    if (autoCtrlTaskHandle_ == nullptr) return APP_ERROR;

    vTaskDelete(autoCtrlTaskHandle_);
    autoCtrlTaskHandle_ = nullptr;
    currentAutoCtrlProcess_ = EAutoCtrlProcess::NONE;

    // 清除所有模块的自动控制标志
    psubgantry_->subGantryCmd.isAutoCtrl = false;
    pchassis_->chassisCmd.isAutoCtrl = false;
    pgimbal_->gimbalCmd.isAutoCtrl = false;
    parm_->armCmd.isAutoCtrl = false;

    return APP_OK;
}


}   // namespace my_engineer
