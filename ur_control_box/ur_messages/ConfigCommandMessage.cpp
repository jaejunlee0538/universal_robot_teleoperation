//
// Created by ub1404 on 15. 8. 18.
//
#include "ConfigCommandMessage.h"
#include "cmd_utils.h"

namespace ur5_message {
    using namespace ConfigCommandsTypes;

    bool ConfigCommandMessage::serialize(ByteBuffer *msg_out) {
        msg_out->load(func_calls);
        return true;
    }

    bool ConfigCommandMessage::__deserialize(ByteBuffer *msg_in) {
        if (msg_in->getRemainedBufferSize() != this->getByteLength()) {
            return false;
        }
        msg_in->unload(func_calls);
        return true;
    }

    void ConfigCommandMessage::setOpenInterface() {
        CLEAR_BIT(func_calls, CLOSE_INTERFACE);
        SET_BIT(func_calls, OPEN_INTERFACE);
    }

    void ConfigCommandMessage::setCloseInterface() {
        CLEAR_BIT(func_calls, OPEN_INTERFACE);
        SET_BIT(func_calls, CLOSE_INTERFACE);
    }

    void ConfigCommandMessage::setRobotReadyMode() {
        CLEAR_BIT(func_calls, SET_ROBOT_FREEDRIVE_MODE);
//            CLEAR_BIT(func_calls, SET_ROBOT_READY_MODE);
        CLEAR_BIT(func_calls, SET_ROBOT_RUNNING_MODE);
        SET_BIT(func_calls, SET_ROBOT_READY_MODE);
    }

    void ConfigCommandMessage::setRobotRunningMode() {
        CLEAR_BIT(func_calls, SET_ROBOT_FREEDRIVE_MODE);
        CLEAR_BIT(func_calls, SET_ROBOT_READY_MODE);
//            CLEAR_BIT(func_calls, SET_ROBOT_RUNNING_MODE);
        SET_BIT(func_calls, SET_ROBOT_RUNNING_MODE);
    }


    void ConfigCommandMessage::setRobotFreedriveMode() {
//            CLEAR_BIT(func_calls, SET_ROBOT_FREEDRIVE_MODE);
        CLEAR_BIT(func_calls, SET_ROBOT_READY_MODE);
        CLEAR_BIT(func_calls, SET_ROBOT_RUNNING_MODE);
        SET_BIT(func_calls, SET_ROBOT_FREEDRIVE_MODE);
    }

    void ConfigCommandMessage::setSecurityStop() {
        CLEAR_BIT(func_calls, UNLOCK_SECURITY_STOP);
        SET_BIT(func_calls, SET_SECURITY_STOP);
    }

    void ConfigCommandMessage::setUnlockSecurityStop() {
        CLEAR_BIT(func_calls, SET_SECURITY_STOP);
        SET_BIT(func_calls, UNLOCK_SECURITY_STOP);
    }

    void ConfigCommandMessage::setPowerOnRobot() {
        CLEAR_BIT(func_calls, POWER_OFF_ROBOT);
        SET_BIT(func_calls, POWER_ON_ROBOT);
    }

    void ConfigCommandMessage::setPowerOffRobot() {
        CLEAR_BIT(func_calls, POWER_ON_ROBOT);
        SET_BIT(func_calls, POWER_OFF_ROBOT);
    }

    bool ConfigCommandMessage::isCommandSet(ConfigCommandsTypes::ConfigCommandsType command) {
        return GET_BIT(func_calls, command);
    }


    ConfigCommandMessage ConfigCommandMessage::makeDummy() {
        this->func_calls = 312;
    }

    bool ConfigCommandMessage::operator!=(const ConfigCommandMessage &A) {
        return !operator==(A);
    }

    bool ConfigCommandMessage::operator==(const ConfigCommandMessage &A) {
        if (func_calls != A.func_calls)
            return false;
        return true;
    }
}
