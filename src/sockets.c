#include "sockets.h"


int socketCreate() {

	int socId = -1;

	// Create client socket
	if ((socId = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket Creation:");
		exit(0);
	}

	return socId;
}

int socketConnect(int client_fd,const char * ip, unsigned int port,
		socket_network_t soc_nw) {

	struct sockaddr_in serv_addr;
	struct hostent *server;


	//set server parameters
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if (soc_nw == E_SOCKET_HTTP) {
		/* lookup the ip address */
		server = gethostbyname(ip);
		if (server == NULL)
			perror("ERROR, no such host");
		memcpy(&serv_addr.sin_addr.s_addr, server->h_addr,server->h_length);

    } else {

        serv_addr.sin_addr.s_addr = inet_addr(ip);

    }

    if (connect(client_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        perror("connction failed!");
    }
			
                

	return client_fd;

}

int socket_Receive(int client_fd,  char * buffer_ptr,
		unsigned int bufferSize) {
	int readBytes = 0;
	
		//receive packets from server
		readBytes = read(client_fd, buffer_ptr, bufferSize);
	
	return readBytes;
}

int socket_Send(int client_fd, const char * buffer_ptr,
		unsigned int bufferSize) {

	int bytesToSend = 0;

	bytesToSend = write(client_fd, buffer_ptr, bufferSize);
	
	return bytesToSend;

}

int  socket_close(int client_fd){
	close(client_fd);
	client_fd = socketCreate();
	return client_fd;
}