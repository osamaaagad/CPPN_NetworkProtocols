#ifndef SOCKETS_H
#define SOCKETS_H
#if defined(__cplusplus) /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/******** includes *************/
#include <unistd.h>  /* UNIX Standard Definitions 	   */
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>/* ERROR Number Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <fcntl.h>   /* File Control Definitions           */
#include <arpa/inet.h>



/********   Structs&Enums  *************/
/**
 *
 */
typedef enum socket_network  {
	E_SOCKET_TCP=0,/**< SOCKET_TCP */
	E_SOCKET_MQTT, /**< SOCKET_MQTT */
	E_SOCKET_HTTP /**< SOCKET_HTTP */
}socket_network_t;

typedef enum ConnState {
	E_SOCKET_NOT_CONNECTED=0,/**< E_SOCKET_NOT_CONNECTED */
	E_SOCKET_ESTABLISHED, /**< E_SOCKET_ESTABLISHED */
}ConnState_t;

int socketCreate();

int socketConnect( int client_fd ,const char * ip,unsigned int port , socket_network_t soc_nw);

int socket_Receive(int client_fd,  char * buffer_ptr , unsigned int bufferSize);

int socket_Send(int client_fd, const char * buffer_ptr , unsigned int bufferSize);

int  socket_close(int client_fd);

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
}
#endif

#endif//SOCKETS_H