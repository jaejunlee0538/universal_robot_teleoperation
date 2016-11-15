//
// Created by ub1404 on 15. 8. 14.
//

#ifndef COMMMODULE_UDPSERVER_H
#define COMMMODULE_UDPSERVER_H
#include "UDPSocket.h"

namespace commModule {
    class UDPServer : public UDPSocket {
    public:
        UDPServer();

        ~UDPServer();
        bool init(int port);

        int spinOnce(int poll_timeout_ms);

        bool destroyConnection();
    protected:
        bool __makeConnection() ;

    protected:
        SOCKADDR_IN _addr_server;
    };
}

#endif //COMMMODULE_UDPSERVER_H
