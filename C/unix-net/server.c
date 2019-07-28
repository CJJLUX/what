#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT   9999 
#define BUFSIZE     1024

//#define   NET_ADDRESS

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

#ifdef NET_ADDRESS
    if (argc > 1) {
        net_address = atoi(argv[1]);
    }else{
        handle_error("#######argv is error######");
    }
#endif

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_sockfd < 0) {
        handle_error("#######socket()");
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
#ifdef NET_ADDRESS
    server_addr.sin_addr.s_addr = net_address;
#endif
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr_size = sizeof(server_addr);
    ret = bind(server_sockfd, (struct sockaddr *)&server_addr, server_addr_size); 
    if (ret < 0) {
        handle_error("#########bind()");
    }

    printf("======listen-start=======\n");
    ret = listen(server_sockfd, 3); //the three mean which the queue of pending connections
    if (ret < 0) {
        handle_error("#######listen()");
    }
    
    printf("======accept-start=======\n");
    socklen_t sin_size = sizeof(struct sockaddr_in);
    ret = accept(server_sockfd,(struct sockaddr *)&server_addr, &sin_size);
    if (ret < 0) {
        handle_error("#########accept()"); 
    }
    printf("==========accept-successed=======\n");

    while(1) {
        count++;
        num++;
        memset(buf, 0, sizeof(buf));
        len = recv(server_sockfd, buf, sizeof(buf), 0);
        if (len > 2) {
            sleep(2);
            printf("============recv-start==============");
            printf("recv: %s\n", buf);
            if (count > 100) {//every 100 byte to print
                printf("have recv %d byte\n", 100*num);
                count = 0;
            }else{
                printf("============recv-no-byte==============");
            }
        }
    }

    exit(0);
}

