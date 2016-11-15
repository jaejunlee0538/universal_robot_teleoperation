//
// Created by ub1404 on 15. 8. 28.
//

#ifndef UR_ROBOT_URCALLBACKCLIENT_H
#define UR_ROBOT_URCALLBACKCLIENT_H

#include <commons/utils/logger.h>
#include <commons/socket/UDPClient.h>
#include <commons/serialize/ByteBufferEndian.h>
#include <commons/serialize/SerializeInterface.h>
#include <ur_messages/URMessages.h>
#include "URCallbackClientInterface.h"

using commModule::UDPClient;
using serialize_module::SerializeInterface;
using serialize_module::ByteBuffer;
using serialize_module::AlignedByteBuffer;

class URCallbackClient : public URCallbackClientInterface {
public:
    virtual bool init(const char *robot_ip, const int port);

    /*
     * Implementation of URCallbackClientInterface::spinOnce.
     *
     */
    virtual bool spinOnce(void);

    /*
     * Implementation of URCallbackClientInterface::sendJointCommand.
     * Transfer joint command through socket to real robot.
     */
    bool sendJointCommand(ur5_message::JointCommandMessage &joint_cmd);

    /*
     * Implementation of URCallbackClientInterface::sendConfigCommand.
     * Transfer config command through socket to real robot.
     */
    bool sendConfigCommand(ur5_message::ConfigCommandMessage &config_cmd);

protected:
    bool sendCommand(msgtype_t msg_type, SerializeInterface *message);

private:
    const static int MAX_BUFFER_SIZE = 1024;
    ur5_message::RobotStateMessage robot_state_data;
    UDPClient udp_client;
    char raw_buffer[MAX_BUFFER_SIZE];
};


#endif //UR_ROBOT_URCALLBACKCLIENT_H
