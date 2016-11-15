//
// Created by ub1404 on 15. 8. 14.
//

#ifndef COMMMODULE_SOCKETINTERFACE_H
#define COMMMODULE_SOCKETINTERFACE_H

#if defined(__linux__)
#define _SOCK_OS_ LINUX
/*Linux Socket*/

#include "sys/socket.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "string.h"
#include "sys/select.h"
#include <sys/ioctl.h>
#include <net/if.h>


#define SOCKET(domain, type, protocol) socket(domain, type, protocol)
#define BIND(sockfd, addr, addrlen) bind(sockfd, addr, addrlen)
#define SET_NO_DELAY(sockfd, val) setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val))
#define SET_REUSE_ADDR(sockfd, val) setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))
#define LISTEN(sockfd, n) listen(sockfd, n)
#define ACCEPT(sockfd, addr, addrlen) accept(sockfd, addr, addrlen)
#define CONNECT(sockfd, dest_addr ,addrlen) connect(sockfd, dest_addr, addrlen)
#define SEND_TO(sockfd, buf, len, flags, dest_addr, addrlen) sendto(sockfd, buf, len, flags, dest_addr, addrlen)
#define SEND(sockfd, buf, len, flags) send(sockfd, buf, len, flags)
#define RECV_FROM(sockfd, buf, len, flags, src_addr, addrlen) recvfrom(sockfd, buf, len, flags, src_addr, addrlen)
#define RECV(sockfd, buf, len, flags) recv(sockfd, buf, len, flags)
#define SELECT(n, readfds, writefds, exceptfds, timeval) select(n, readfds, writefds, exceptfds, timeval)
#define CLOSE(fd) close(fd)

#define SOCKET_TYPE int
#define INET_ADDR(str) inet_addr(str)
#define SOCKLEN_T socklen_t
#define GETHOSTBYNAME(str) gethostbyname(str)

#define SOCKADDR_IN struct sockaddr_in
#define SOCKADDR struct sockaddr
#define IN_ADDR struct in_addr
#endif


#if defined(__WIN32__)
#if defined(_SOCK_OS_)
#error "Operating System Collision"
#endif

#define _SOCK_OS_ WINDOWS
/*Windows Socket*/
#include <winsock2.h>

#endif

#if not defined(_SOCK_OS_)
#error "Unsupported Operating System"
#endif

extern void getMyIP(char*);
extern int sock_cmp_addr(const SOCKADDR *sa1, const SOCKADDR *sa2, SOCKLEN_T salen);

namespace commModule{
    enum CommModuleReturnValue{
        SOCKET_TIMEOUT = -2,
        SOCKET_ERROR = -1,
        SOCKET_CONNECTION_REQUEST=5,
        SOCKET_INCOMING_DATA = 6
    };

    class SocketInterface {
    public:
        SocketInterface();

        /*
         * return sent bytes length
         */
        virtual int sendRawBytes(const char* buffer, int buf_size)=0;

        /*
         * return received bytes length
         */
        virtual int recvRawBytes(char* buffer, int buf_size)=0;

        virtual bool destroyConnection()=0;

        /*
         *
         * return SOCKET_ERROR, when error
         * return SOCKET_TIMEOUT, when select returned with timeout.
         * return SOCKET_INCOMING_DATA, when new data is available.
         *
         * if poll_timeout_ms < 0, work as blocking function.
         */
        virtual int spinOnce(int poll_timeout_ms)=0;

        bool isConnected();

    protected:


        /*
         *
         * return SOCKET_ERROR, when error
         * return SOCKET_TIMEOUT, when select returned with timeout.
         * return SOCKET_CONNECTION_REQUEST, when new connection request is received.
         * return SOCKET_INCOMING_DATA, when new data is available.
         *
         * if poll_timeout_ms < 0, work as blocking function.
         */
        virtual int poll(int timeout_ms)=0;

        void setDisconnected();

        void setConnected();

        SOCKET_TYPE _sock;
        bool _connected;
    };
}


#endif //COMMMODULE_SOCKETINTERFACE_H
