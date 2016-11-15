//
// Created by ub1404 on 15. 8. 14.
//

#include <commons/socket/UDPClient.h>
#include <commons/utils/logger.h>
namespace commModule{

    UDPClient::UDPClient() {

    }

    UDPClient::~UDPClient() {

    }

    bool UDPClient::init(const char *ip_address, int port) {
        this->_sock = SOCKET(PF_INET, SOCK_DGRAM, 0);
        if (this->_sock == SOCKET_ERROR) {
            //Socket() error
            LOG_ERROR("Socket init error");
            return false;
        }
        memset(&this->_addr_target, 0, sizeof(this->_addr_target));
        this->_addr_target.sin_family = AF_INET;
        this->_addr_target.sin_addr.s_addr = INET_ADDR(ip_address);
        this->_addr_target.sin_port = htons(port);
        LOG_INFO("UDPClient initialized");
        return true;
    }

    bool UDPClient::connect(bool blocking) {
        if (!this->isConnected()) {
            this->sendHandShake();
            this->_is_waiting_handshake = true;

            if(blocking)
            {
                int retry_count = 50;
                while(retry_count--)
                {
                    this->spinOnce(100);
                    if(this->isConnected())
                    {
                        return true;
                    }
                    if(retry_count % 10 == 0)
                    {
                        this->sendHandShake();
                    }
                }
            }
        }
        else {
            LOG_WARN("Connection already eastablished");
            this->_is_waiting_handshake = false;
            return true;
        }

        return false;
    }

    void UDPClient::stopWaitingHandShake()
    {
        this->_is_waiting_handshake = false;
    }

    int UDPClient::spinOnce(int poll_timeout_ms){
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
                    if(this->_is_waiting_handshake){
                        if(::memcmp(&_addr_last_recv, &_addr_target, sizeof(SOCKADDR_IN))==0)
                        {
                            LOG_INFO("Connection established");
                            this->setConnected();
                        }
                        else
                        {
                            LOG_WARN("Handshake from unknown server");
                        }
                    }
                }
                else
                {
                    LOG_WARN("Additional connection request");
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

    bool UDPClient::destroyConnection()
    {
        LOG_INFO("Server disconnected");
        this->setDisconnected();
    }


    void UDPClient::setConnected()
    {
        this->_is_waiting_handshake = false;
        SocketInterface::setConnected();
    }

    void UDPClient::setDisconnected()
    {
        this->_is_waiting_handshake = false;
        SocketInterface::setDisconnected();
    }
}