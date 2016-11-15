//
// Created by ub1404 on 15. 8. 18.
//

#ifndef UR5_URMESSAGES_H
#define UR5_URMESSAGES_H
#include "JointCommandMessage.h"
#include "ConfigCommandMessage.h"
#include "RobotStateMessage.h"

typedef int32_t msglen_t;
typedef int32_t msgtype_t;

namespace ur5_message{

    enum UR5MessageType{
        CONFIG_COMMAND = 1,
        JOINT_COMMAND,
        TARGET_JOINT_POSITION_COMMAND,
        ROBOT_STATE
    };

#define UR_COMM_PORT 30005
}


#endif //UR5_URMESSAGES_H
