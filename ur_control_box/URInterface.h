//
// Created by ub1404 on 15. 8. 18.
//

#ifndef URINTERFACE_H
#define URINTERFACE_H

#include "urrobot/utils/logger.h"
#include "urrobot/ur5/ur_messages/URMessages.h"
#include "urrobot/ur5/control_box_driver/URComm.h"
#include "urrobot/transport/socket/UDPServer.h"
#include "urrobot/utils/LoopInterface.h"
#include "VelocityPControl.h"
namespace ur_control_box {
    using commModule::UDPServer;
    using ur5_message::config_command::ConfigCommandMessage;
    using ur5_message::joint_command::JointCommandMessage;
    using ur5_message::robot_state_message::RobotStateMessage;
    using ur5_message::joint_control::TargetJointPosition;
    using ur5_message::CONFIG_COMMAND;
    using ur5_message::JOINT_COMMAND;
    using ur5_message::ROBOT_STATE;
    using ur5_message::TARGET_JOINT_POSITION_COMMAND;
    using ur_comm::URComm;

    class URInterface : public LoopInterface {
    public:
        URInterface();

        bool init();

        void turnOffRobot();

        void controlLoop();

        bool isConnected();

        bool isJointsMoving() ;
    private:
        void readCommands();

        void sendRobotState();

        void conductCommands();

        void updateRobotState();

        void conductConfigCommands();

        void conductJointCommands();

        void extraButtonHandler();
    private:
        URComm ur_comm;
        ConfigCommandMessage msg_config_cmd;
        JointCommandMessage msg_joint_cmd;
        TargetJointPosition msg_target_joint_pos;
        RobotStateMessage msg_robot_state;

        UDPServer server_sock;
        uint32_t loop_count;

        VelocityPControl joint_p_controller[6];
    };
}


#endif //URINTERFACE_H
