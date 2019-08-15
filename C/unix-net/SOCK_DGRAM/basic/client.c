#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT   9999 
#define BUFSIZE     1024

#define   NET_ADDRESS

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


int main(int argc, char **argv)
{
    int server_sockfd;
    struct sockaddr_in server_addr;
    socklen_t   server_addr_size;
    uint32_t  net_address;
    int ret = -1;
    char buf[BUFSIZE];
    int count = 0;
    int num = 0;
    int len = 0;
    char ip_str[32]=  {0};

#ifdef NET_ADDRESS
    if (argc > 1) {
        net_address = inet_pton(AF_INET, argv[1], &server_addr.sin_addr); //点分式转大整数
    }else{
        handle_error("#######argv is error######");
    }
#endif

    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_UDP*/); 
    if (server_sockfd < 0) {
        handle_error("#######socket()");
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr_size = sizeof(server_addr);

    //if (bind(server_sockfd, (struct sockaddr *)&server_addr, server_addr_size) < 0)
    //    handle_error("#########bind()");
    while(1) {
        count++;
        num++;
        memset(buf, '\0', sizeof(buf));
        sprintf(buf, "hello world%d\n", num);
        if (sendto(server_sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, server_addr_size) > 2)
            sleep(1);
        printf("============recv-start==============\n");
        puts("OK======");
    }

    exit(0);
}

