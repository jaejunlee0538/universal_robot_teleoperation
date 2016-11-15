//
// Created by ub1404 on 15. 8. 18.
//
#include <commons/socket/SocketInterface.h>


void getMyIP(char* buffer)
{
#if _SOCK_OS_ == LINUX
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;

    /* I want IP address attached to "eth0" */
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

    ioctl(fd, SIOCGIFADDR, &ifr);

    close(fd);

    strcpy(buffer, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

#else
//...
#endif

}


int sock_cmp_addr(const SOCKADDR *sa1, const SOCKADDR *sa2,
                  SOCKLEN_T salen)
{
    if (sa1->sa_family != sa2->sa_family)
        return(-1);

    switch (sa1->sa_family) {
        case AF_INET: {
            return(memcmp( &((SOCKADDR_IN *) sa1)->sin_addr,
                           &((SOCKADDR_IN *) sa2)->sin_addr,
                           sizeof(IN_ADDR)));
        }

#ifdef	IPV6
	case AF_INET6: {
		return(memcmp( &((struct sockaddr_in6 *) sa1)->sin6_addr,
					   &((struct sockaddr_in6 *) sa2)->sin6_addr,
					   sizeof(struct in6_addr)));
	}
#endif

//#ifdef	AF_UNIX
//        case AF_UNIX: {
//            return(strcmp( ((struct sockaddr_un *) sa1)->sun_path,
//                           ((struct sockaddr_un *) sa2)->sun_path));
//        }
//#endif
//
//#ifdef	HAVE_SOCKADDR_DL_STRUCT
//	case AF_LINK: {
//		return(-1);		/* no idea what to compare here ? */
//	}
//#endif
    }
    return (-1);
}

namespace commModule{
    SocketInterface::SocketInterface(){
        setDisconnected();
    }

    bool SocketInterface::isConnected(){
        return _connected;
    }

    void SocketInterface::setDisconnected()
    {
        this->_connected = false;
    }

    void SocketInterface::setConnected()
    {
        this->_connected = true;
    }

}