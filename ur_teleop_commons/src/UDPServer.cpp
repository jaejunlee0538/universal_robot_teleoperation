//
// Created by ub1404 on 15. 8. 14.
//

#include <commons/socket/UDPServer.h>
#include <commons/utils/logger.h>

namespace commModule{
    UDPServer::UDPServer() {

    }

    UDPServer::~UDPServer() {

    }

    bool UDPServer::init(int port) {
        this->_sock = SOCKET(PF_INET, SOCK_DGRAM, 0);
        if (this->_sock == SOCKET_ERROR) {
            //Socket() error
            LOG_ERROR("Socket init error");
            return false;
        }
        char my_ip[50] = {0,};
        getMyIP(my_ip);
        printf("IP : %s\n", my_ip);
        memset(&this->_addr_target, 0, sizeof(this->_addr_target));
        this->_addr_server.sin_family = AF_INET;
        this->_addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
        this->_addr_server.sin_port = htons(port);

        if (BIND(this->_sock, (SOCKADDR * ) & this->_addr_server, sizeof(this->_addr_server)) == SOCKET_ERROR) {
            //bind error
            LOG_ERROR("bind error");
            return false;
        }
        LOG_INFO("UDPServer initialized");
        return true;
    }

    int UDPServer::spinOnce(int poll_timeout_ms){
        int ret = SOCKET_ERROR;
        while(true)
        {
            ret = this->poll(poll_timeout_ms);
            if(ret == SOCKET_ERROR || ret == SOCKET_TIMEOUT){
                //Error or Timeout
                return ret;
            }

            if(ret == SOCKET_INCOMING_DATA)
            {
                return SOCKET_INCOMING_DATA;
            }

            if(ret == SOCKET_CONNECTION_REQUEST)
            {
                if(!this->isConnected())
                {
                    this->__makeConnection();
                }
                else
                {
                    LOG_WARN("additional connection request from %s",inet_ntoa(_addr_last_recv.sin_addr));
                    //only single connection is allowed.
                    //Do nothing.
                    /*
                     * two cases are possible
                     *  1. do nothing(new connection will be rejected)
                     *  2. destroy old one and accept new one.
                     */
                }
            }
        }
    }

    bool UDPServer::destroyConnection()
    {
        LOG_INFO("Client disconnected");
        this->setDisconnected();
        return true;
    }

    bool UDPServer::__makeConnection() {
        this->_addr_target = this->_addr_last_recv;
        this->sendHandShake();
        this->setConnected();
        LOG_INFO("Client connected - %s", inet_ntoa(_addr_target.sin_addr));
        return true;
    }
}