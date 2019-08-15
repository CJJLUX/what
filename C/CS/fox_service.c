#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/tcp.h>

int FoxServerInit(unsigned int ipaddr, int port)
{
	int ret;
	int len;
	struct sockaddr_in srv_addr;
	int opt = 1;
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd < 0)
		{
			perror("cannot create communication socket");
			return -1;
		}

	int flags = fcntl(socket_fd, F_GETFD);
    flags |= FD_CLOEXEC;
    fcntl(socket_fd, F_SETFD, flags);
	
	//set server addr_param
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port);
	srv_addr.sin_addr.s_addr = ipaddr;	//
//	srv_addr.sin_addr.s_addr = INADDR_ANY;

	int on = 1;  
	setsockopt(socket_fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&on, sizeof(on)); 
	setsockopt(socket_fd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));
	
	setsockopt(socket_fd, SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
//	setsockopt(socket_fd, SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));

	//bind sockfd & addr
	ret = bind(socket_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));

	if(ret == -1)
		{
			perror("fox:cannot bind server socket\n");
			printf("port = %d\n", port);
			close(socket_fd);
			return -1;
		}

	//listen sockfd
	ret = listen(socket_fd, 1);
	if(ret == -1)
		{
			perror("fox:cannot listen the client connect request");
			close(socket_fd);
			return -1;
		}

	return socket_fd;
}

int FoxServerWait(int socket_fd)
{
	struct sockaddr_in clt_addr;
	//have connect request use accept
	int len = sizeof(clt_addr);
	int client_fd = accept(socket_fd, (struct sockaddr *)&clt_addr, &len);

	if(client_fd < 0)
		{
			perror("cannot accept client connect request");
//			close(socket_fd);
			return -1;
		}

	return client_fd;
}

size_t RecvFromClient(int client_fd, char *data, size_t len)
{
	size_t byte;
	
	if(client_fd < 0)
		return -1;

	byte = recv(client_fd,data, len, 0);

	return byte;  
}


#define MAX_LEN	5*1024*1024

int main(int argc, int argv[])
{
	int socket_fd = FoxServerInit(0, 50888);
	if(socket_fd < 0)
		{
			printf("FoxServerInit fail..\n");
			return 0;
		}

	printf("FoxServerWait.\n");
	int client_fd = FoxServerWait(socket_fd);
	printf("Got a client\n");

	struct timeval stime,etime;
	unsigned int total = 0;

	while(1)
		{
			if(total == 0)		
				gettimeofday(&stime, NULL);

			char data[1024];
			int Main_Len = RecvFromClient(client_fd, data, sizeof(data));
			if(Main_Len< 0)
				break;
			if(total < MAX_LEN)
				total += Main_Len;
			else
				{
			gettimeofday(&etime, NULL);
			unsigned long ms = (etime.tv_sec -stime.tv_sec)*1000.0+(etime.tv_usec-stime.tv_usec)/1000.0;
			printf("time = %d, speed = %d(byte/ms)\n", ms, MAX_LEN/ms);
			total = 0;
				}
						
		}

	printf("exit\n");
}

