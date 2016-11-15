//
// Created by ub1404 on 15. 8. 19.
//

#ifndef UR5_URCOMM_H
#define UR5_URCOMM_H

#include "urrobot/utils/logger.h"
#include "urrobot/transport/socket/SocketInterface.h"
#include "urrobot/transport/serialize/ByteBufferEndian.h"
#include "urrobot/transport/serialize/SerializeInterface.h"
#include "urrobot/ur5/ur_messages/URMessages.h"
#include <map>

namespace ur_comm {

#define UR_COMM_PORT 30005

    using commModule::SocketInterface;
    using commModule::SOCKET_INCOMING_DATA;
    using commModule::SOCKET_ERROR;
    using commModule::SOCKET_TIMEOUT;
    using serialize_module::SerializeInterface;
    using serialize_module::ByteBuffer;
    using serialize_module::AlignedByteBuffer;

    class URComm {
    public:
        URComm();

        void setSocket(SocketInterface *_sock);

        void registerMessageType(msgtype_t msg_type, SerializeInterface *container);

        void processAllIncomingMessage(int poll_timeout_ms = 0);

        void sendMessage(msgtype_t msg_type, SerializeInterface *message);

        bool isConnected() {
            if (!sock)
                return false;
            return sock->isConnected();
        }

    public:
        const static int MAX_BUFFER_SIZE = 1024;
    protected:
        SocketInterface *sock;

        std::map<msgtype_t, SerializeInterface *> message_map;

        char raw_buffer[MAX_BUFFER_SIZE];
    };

}


#endif //UR5_URCOMM_H