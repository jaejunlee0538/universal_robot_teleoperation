//
// Created by ub1404 on 15. 8. 19.
//

#include "URComm.h"

namespace ur_comm {
    URComm::URComm() {
        this->sock = NULL;
    }

    void URComm::setSocket(SocketInterface *_sock) {
        this->sock = _sock;
    }

    void URComm::registerMessageType(msgtype_t msg_type, SerializeInterface *container) {
        if (message_map.find(msg_type) != message_map.end()) {
            LOG_WARN("(%d) typed message is already registered", msg_type);
        }
        message_map[msg_type] = container;
        LOG_INFO("(%d) typed message is registered", msg_type);
    }

    void URComm::processAllIncomingMessage(int poll_timeout_ms) {
        if (!sock) {
            LOG_VERBOSE1("no socket object");
            return;
        }

        if (!sock->isConnected()) {
            LOG_VERBOSE1("socket is not connected");
        }
        int spin_timeout = 0;
        int max_spin_count = 0;
        int spin_count = 0;
        if (poll_timeout_ms > 0) {
            spin_timeout = 1;
            max_spin_count = poll_timeout_ms;
        }
        while (sock->spinOnce(spin_timeout) == SOCKET_INCOMING_DATA) {
            if (spin_timeout) {
                if (max_spin_count < 0) {
                    LOG_DEBUG("processAllIncomingMessage timeout");
                    break;
                }
                max_spin_count--;
            }
            int n_read = sock->recvRawBytes(raw_buffer, MAX_BUFFER_SIZE);
            if (n_read == SOCKET_ERROR) {
                LOG_ERROR("recvRawBytes error after select succeed");
                break;
            }
            AlignedByteBuffer byteBuffer;

            byteBuffer.copyFrom(raw_buffer, n_read);
            msglen_t msg_len;
            static_cast<ByteBuffer *>(&byteBuffer)->unload(msg_len);

            if (msg_len != byteBuffer.getRemainedBufferSize()) {
                LOG_ERROR("msg_len packet(%d) does not match with actual msg_len(%d)",
                          msg_len, byteBuffer.getRemainedBufferSize());
                continue;
            }

            msgtype_t msg_type;
            static_cast<ByteBuffer *>(&byteBuffer)->unload(msg_type);
            if (message_map.find(msg_type) == message_map.end()) {
                LOG_ERROR("undefined message type(%d)", msg_type);
                continue;
            }

            if (!static_cast<ByteBuffer *>(&byteBuffer)->unload(message_map[msg_type])) {
                LOG_ERROR("(%d)-type message unloading failed", msg_type);
            }
            else {
                LOG_VERBOSE2("(%d)-type message received", msg_type);
            }
        }
    }

    void URComm::sendMessage(msgtype_t msg_type, SerializeInterface *message) {
        if (sock) {
            AlignedByteBuffer byteBuffer;

            msglen_t len = message->getByteLength() + sizeof(msgtype_t);

            //generate packet
            static_cast<ByteBuffer *>(&byteBuffer)->load(len);
            static_cast<ByteBuffer *>(&byteBuffer)->load(msg_type);
            static_cast<ByteBuffer *>(&byteBuffer)->load(message);

            if (sock->isConnected()) {
                if (sock->sendRawBytes(byteBuffer.getBuffer(), byteBuffer.getBufferSize()) == -1) {
                    LOG_ERROR("failed sending message");
                }
            }
            else {
                LOG_VERBOSE1("socket is not connected");
            }
        }
        else {
            LOG_VERBOSE1("no socket object");
        }
    }
}