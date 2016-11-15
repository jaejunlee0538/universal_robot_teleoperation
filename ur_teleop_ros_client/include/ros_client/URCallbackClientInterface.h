//
// Created by ub1404 on 15. 8. 28.
//

#ifndef UR_ROBOT_URCLIENTINTERFACE_H
#define UR_ROBOT_URCLIENTINTERFACE_H

#include <commons/utils/logger.h>
#include <ur_messages/URMessages.h>

class URCallbackClientInterface{
public:
    /*
     * Implementation must include
     *   - connecting to the robot or simulator
     *
     */
    virtual bool init(const char *robot_ip, const int port) = 0;

    /*
     * Implementation of spinOnce must include
     *   - waiting for robot state message to come
     *   - call 'stateCallback' method with received state message
     *
     *   return true when usual case
     *   return false when there is problem in receiving message.
     */
    virtual bool spinOnce(void) = 0;

    /*
     * Should be implemented.
     */
    virtual bool sendJointCommand(ur5_message::JointCommandMessage &joint_cmd) = 0;

    /*
     * Should be implemented.
     */
    virtual bool sendConfigCommand(ur5_message::ConfigCommandMessage &config_cmd) = 0;

protected:
    /*
     * stateCallback method is
     */
    virtual bool stateCallback(ur5_message::RobotStateMessage robot_state) = 0;
};


#endif //UR_ROBOT_URCLIENTINTERFACE_H
