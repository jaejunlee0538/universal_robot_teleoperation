//
// Created by ub1404 on 15. 8. 14.
//

#ifndef COMMMODULE_UDPCLIENT_H
#define COMMMODULE_UDPCLIENT_H
#include "UDPSocket.h"


namespace commModule {
    class UDPClient : public UDPSocket {
    public:
        UDPClient();

        ~UDPClient();

        /*
         * Initialize udp socket.
         * Note that success of init does not mean that socket is connected.
         *
         */
        bool init(const char *ip_address, int port);

        /*
         * Send handshake to server and set '_is_waiting_handshake' flag.
         * If this flag is set, spinOnce will make (virtual)connection with target from which
         * handshake packet was received.
         *
         * After calling `connect`, you can check if the connection has been established by calling  'isConnected'.
         * If connection is established, '_is_waiting_handshake' flag automatically is cleared.
         */
        bool connect(bool blocking=true);

        /*
         * Clear '_is_waiting_handshake' flag.
         */
        void stopWaitingHandShake();

        /*
         * Wait for incoming data through udp socket.
         *
         * if poll_timeout_ms < 0, spinOnce will be blocked until next socket event.
         * Otherwise, spinOnce is guaranteed to be returned in poll_timeout_ms msec.
         *
         */
        int spinOnce(int poll_timeout_ms);

        /*
         * Destroy connection.
         */
        bool destroyConnection();

    protected:
        void setConnected();

        void setDisconnected();
    protected:
        bool _is_waiting_handshake;
    };
}

#endif //COMMMODULE_UDPCLIENT_H
