#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>



int FoxSendData2Server(int socket_fd,char *data, int len)	
{
	int byte;	
			               
	byte=send(socket_fd, data, len, 0);

	return byte;
}

int FoxClientInit()
{
	int i, byte;
	int ret;
	static struct sockaddr_in srv_addr;
	int socket_fd;
	
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
//		perror("cannot create communication socket");
		printf("%s\n","FoxClientInit: socket fail\n");
		return -1;
	}

	return socket_fd;	
}


int FoxClientConnect(char *ip, int socket_fd, int port)
{
	int i, byte;
	int ret;
	static struct sockaddr_in srv_addr;	

	bzero(&srv_addr,sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port);
	srv_addr.sin_addr.s_addr = inet_addr(ip);

//connect server
	ret = connect(socket_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if(ret == -1)
		{
			printf("FoxClientConnect: cannot connect to the server, port = %d\n", port);
	//		close(socket_fd);
			return -1;
		}

	return 0;
	
}

int main(int argc , char *argv[])
{
	int socket_fd = FoxClientInit();
	if(socket_fd < 0)
		{
			printf("FoxClientInit fail..\n");
			return -1;
		}

	printf("connect %s\n", argv[1]);
	FoxClientConnect(argv[1], socket_fd, 50888);
	printf("connect %s success\n", argv[1]);

	while(1)
		{
			char data[1024];
			if(FoxSendData2Server(socket_fd, data, sizeof(data)) < 0)
				break;
		}

	printf("exit\n");

	return 0;
}


