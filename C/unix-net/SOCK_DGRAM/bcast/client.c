#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT   9999 
#define BUFSIZE     1024

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


int main(int argc, char **argv)
{
    int server_sockfd;
    struct sockaddr_in server_addr;
    socklen_t   server_addr_size;
    uint32_t  net_address;
    int ret = -1;
    unsigned char buf[BUFSIZE];
    int num = 0;
    int len = 0;
    unsigned char ip_str[32]=  {0};

    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_UDP*/); 
    if (server_sockfd < 0) {
        handle_error("#######socket()");
    }

    int optval = 1;
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_BROADCAST,&optval, sizeof(optval)) < 0) {
        handle_error("#########setsockopt()");
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "255.255.255.255", &server_addr.sin_addr);
    server_addr_size = sizeof(server_addr);

    while(1) {
        num++;

        memset(buf, '\0', sizeof(buf));
        sprintf(buf, "hello world%d\n", num);

        if (sendto(server_sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, server_addr_size) > 2)

            sleep(1);
        printf("============sendto-start==============\n");
        puts("OK======");
    }

    exit(0);
}

