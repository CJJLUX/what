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
    char buf[BUFSIZE];
    int count = 0;
    int num = 0;
    int len = 0;
    char ip_str[32]=  {0};

    server_sockfd = socket(PF_INET, SOCK_DGRAM, 0/*IPPROTO_UDP*/); 
    if (server_sockfd < 0) {
        handle_error("#######socket()");
    }

    int val = 1;
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) < 0) {
        perror("setsockopt()");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr_size = sizeof(server_addr);

    if (bind(server_sockfd, (struct sockaddr *)&server_addr, server_addr_size) < 0)
        handle_error("#########bind()");
    printf("======bind-success=====\n");

    while(1) {
        count++;
        num++;
        memset(buf, 0, sizeof(buf));
        len = recvfrom(server_sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, &server_addr_size);
        if (len > 2) {
            sleep(1);
            printf("============recv-start==============\n");
            //大整数转点分式
            inet_ntop(AF_INET, &server_addr.sin_addr, ip_str,32);
            printf("MESSAGE FROM %s:%d--\n", ip_str, ntohs(server_addr.sin_port));
            printf("recv: %s\n", buf);
            if (count > 100) {//every 100 byte to print
                printf("have recv %d byte\n", 100*num);
                count = 0;
            }
        }else{
            printf("##########no-recvfrom#####\n");
        }
    }

    exit(0);
}

