//
// Created by ub1404 on 15. 8. 14.
//

#ifndef COMMMODULE_UDPSOCKET_H
#define COMMMODULE_UDPSOCKET_H
#include "SocketInterface.h"

namespace commModule {
    class UDPSocket : public SocketInterface {
    public:
        UDPSocket();

        ~UDPSocket();

        /*
         *
         * return -1, when error.
         * return sent length, otherwise.
         */
        int sendRawBytes(const char *buffer, int buf_size);

        /*
         * If incoming data is bigger than buffer size, the packet is discarded.
         * Enough size of buffer should be handed to this method.
         *
         * return -1, when error(lack of buffer).
         * return received length, otherwise.
         */
        int recvRawBytes(char *buffer, int buf_size);

    protected:
        /*
         * Waiting for socket event(Error, Timeout, Incoming data, Connection Request).
         * Especially, Connection Request is a manually made functionality.
         *
         * if timeout_ms > 0, poll will return after timeout_ms msec.
         * if timeout_ms is 0, poll return instantaneously.
         * if timeout_ms < 0, poll will act as blocking function.
         *
         * return SOCKET_ERROR, when error.
         * return SOCKET_TIMEOUT, when timeout.
         * return SOCKET_CONNECTION_REQUEST, when handshake packet has been received.
         * return SOCKET_INCOMING_DATA, when there is data to be read.
         */
        int poll(int timeout_ms);

        /*
         * Send handshake packet to _addr_target.
         *
         */
        bool sendHandShake();

    public:
        const static int MAX_READ_BUFFER_SIZE = 1024;
    protected:
        SOCKADDR_IN _addr_last_recv;
        SOCKADDR_IN _addr_target;

        char _read_buffer[MAX_READ_BUFFER_SIZE];
        int _read_len;

        const static int32_t UDP_HANDSHAKE = 123;
    };
}


#endif //COMMMODULE_UDPSOCKET_H
