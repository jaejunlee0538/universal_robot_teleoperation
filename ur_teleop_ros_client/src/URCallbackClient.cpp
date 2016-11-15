//
// Created by ub1404 on 15. 8. 28.
//

#include <ros_client/URCallbackClient.h>

bool URCallbackClient::init(const char *robot_ip, const int port) {
    if (!this->udp_client.init(robot_ip, port)) {
        LOG_ERROR("UDP client init error");
        return false;
    }

    if (!udp_client.connect(true)) {
        LOG_ERROR("UDP client connect failed");
        return false;
    }
    return true;
}

bool URCallbackClient::spinOnce(void) {
    if (!udp_client.isConnected()) {
        return false;
    }

    //blocking call
    if (udp_client.spinOnce(-1) == commModule::SOCKET_INCOMING_DATA) {
        int n_read = udp_client.recvRawBytes(raw_buffer, MAX_BUFFER_SIZE);
        if (n_read == commModule::SOCKET_ERROR) {
            LOG_ERROR("recvRawBytes error after select succeed");
            return false;
        }

        AlignedByteBuffer byteBuffer;
        byteBuffer.copyFrom(raw_buffer, n_read);
        msglen_t msg_len;
        static_cast<ByteBuffer *>(&byteBuffer)->unload(msg_len);

        if (msg_len != byteBuffer.getRemainedBufferSize()) {
            LOG_ERROR("msg_len packet(%d) does not match with actual msg_len(%d)",
                      msg_len, byteBuffer.getRemainedBufferSize());
            return false;
        }

        msgtype_t msg_type;
        static_cast<ByteBuffer *>(&byteBuffer)->unload(msg_type);
        if (msg_type != ur5_message::ROBOT_STATE) {
            LOG_ERROR("undefined message type(%d)", msg_type);
            return false;
        }

        if (!static_cast<ByteBuffer *>(&byteBuffer)->unload(
                static_cast<SerializeInterface *>(&robot_state_data))) {
            LOG_ERROR("(%d)-type message unloading failed", msg_type);
            return false;
        }
        else {
            LOG_VERBOSE2("(%d)-type message received", msg_type);
            this->stateCallback(robot_state_data);  //callback
            return true;
        }
    }
}

bool URCallbackClient::sendJointCommand(ur5_message::JointCommandMessage &joint_cmd) {
    return this->sendCommand(ur5_message::JOINT_COMMAND, &joint_cmd);
}

bool URCallbackClient::sendConfigCommand(ur5_message::ConfigCommandMessage &config_cmd) {
    return this->sendCommand(ur5_message::CONFIG_COMMAND, &config_cmd);
}


bool URCallbackClient::sendCommand(msgtype_t msg_type, SerializeInterface *message) {
    if (!udp_client.isConnected()) {
        return false;
    }

    AlignedByteBuffer byteBuffer;
    msglen_t len = message->getByteLength() + sizeof(msgtype_t);

    //generate packet
    static_cast<ByteBuffer *>(&byteBuffer)->load(len);
    static_cast<ByteBuffer *>(&byteBuffer)->load(msg_type);
    static_cast<ByteBuffer *>(&byteBuffer)->load(message);

    if (udp_client.sendRawBytes(byteBuffer.getBuffer(), byteBuffer.getBufferSize()) == -1) {
        return false;
    }
    return true;
}