//
// Created by ub1404 on 15. 8. 14.
//

#include <commons/socket/UDPSocket.h>
#include <commons/utils/logger.h>

namespace commModule{
    UDPSocket::UDPSocket() {

    }

    UDPSocket::~UDPSocket() {

    }

    int UDPSocket::sendRawBytes(const char *buffer, int buf_size) {
        int ret;
        ret = (int) SEND_TO(this->_sock, buffer, buf_size, 0, (SOCKADDR * ) & _addr_target, sizeof(_addr_target));
        if (ret == SOCKET_ERROR) {
            LOG_ERROR("send_to failed");
        }
        return ret;
    }

    int UDPSocket::recvRawBytes(char *buffer, int buf_size) {
        if (_read_len > buf_size) {
            LOG_ERROR("received bytes length is bigget than buf_size");
            return SOCKET_ERROR;
        }
        memcpy(buffer, this->_read_buffer, _read_len);
        return _read_len;
    }

    int UDPSocket::poll(int timeout_ms) {
        int num_fd;

        timeval * _timeout = NULL;
        timeval timeout;
        // If timeout_ms < 0 , _timeout is left NULL and select will be blocking function.
        if(timeout_ms>=0){
            timeout.tv_sec = timeout_ms / 1000;
            timeout.tv_usec = (timeout_ms % 1000) * 1000;
            _timeout = &timeout;
        }

        fd_set read, except;
        FD_ZERO(&read);
        FD_ZERO(&except);
        FD_SET(this->_sock, &read);
        FD_SET(this->_sock, &except);

        num_fd = SELECT(this->_sock + 1, &read, 0, &except, _timeout);
        if (num_fd > 0) {
            if (FD_ISSET(this->_sock, &read)) {
                //ready to read
                SOCKLEN_T sz_addr_target;
                SOCKADDR_IN from_addr;
                sz_addr_target = sizeof(from_addr);
                _read_len = (int) RECV_FROM(this->_sock, _read_buffer, MAX_READ_BUFFER_SIZE, 0, (SOCKADDR * ) & from_addr,
                                            &sz_addr_target);
                if(!this->isConnected())
                {
                    if(_read_len == sizeof(UDPSocket::UDP_HANDSHAKE))
                    {
                        //check it is handshake packet.
                        int32_t * p_data = (int32_t*)_read_buffer;
                        if(ntohl(*p_data) == UDPSocket::UDP_HANDSHAKE)
                        {
                            _addr_last_recv = from_addr;
                            return SOCKET_CONNECTION_REQUEST;
                        }
                        else
                        {
                            LOG_WARN("It is not a handshake packet");
                            return SOCKET_ERROR;
                        }
                    }
                }
                else
                {
                    if(::memcmp(&from_addr, &_addr_target, sizeof(SOCKADDR_IN))==0)
                    {
                        return SOCKET_INCOMING_DATA;
                    }
                    else{
                        LOG_WARN("Different data source(%s), while desired source(%s)",
                                 inet_ntoa(from_addr.sin_addr),inet_ntoa(_addr_target.sin_addr));

                        return SOCKET_ERROR;
                    }
                }

                if (_read_len > MAX_READ_BUFFER_SIZE) {
                    LOG_ERROR("received bytes length(%d) is bigger than MAX_READ_BUFFER_SIZE(%d)",
                              _read_len, MAX_READ_BUFFER_SIZE);
                    return SOCKET_ERROR;
                }

                return SOCKET_ERROR;
            }
            else if (FD_ISSET(this->_sock, &except)) {
                //error
                LOG_ERROR("exception while selecting sock");
                return SOCKET_ERROR;
            }
            else {
                //No flag is set.
                LOG_ERROR("select ended up with no flag");
                return SOCKET_ERROR;
            }
        }
        else if (num_fd == 0) {
            //Timeout
//            LOG_VERBOSE2("select timeout");
            return SOCKET_TIMEOUT;
        }
        else {
            //Select failed
            LOG_ERROR("select failed");
            return SOCKET_ERROR;
        }
    }

    bool UDPSocket::sendHandShake()
    {
        uint32_t handshake_net = htonl(UDPSocket::UDP_HANDSHAKE);
        LOG_INFO("Send Handshake");
        if(this->sendRawBytes((char *) &handshake_net, sizeof(UDPSocket::UDP_HANDSHAKE))==-1)
            return false;
        return true;
    }
}