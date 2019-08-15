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
    int client_sockfd;
    struct sockaddr_in server_addr;
    socklen_t   server_addr_size;
    uint32_t  net_address;
    int ret = -1;
    char buf[BUFSIZE] = "holle world";
    int count = 0;
    int num = 0;
    int len = 0;

    client_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (client_sockfd < 0) {
        handle_error("#######socket()");
    }
    printf("socket build success\n");

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    server_addr_size = sizeof(server_addr);
    ret = connect(client_sockfd, (struct sockaddr *)&server_addr, server_addr_size);
    if (ret < 0) {
        handle_error("#######connect()");
    }
    printf("=======connect successed========\n");

    while(1) {
        count++;
        num++;
        memset(buf, 0, sizeof(buf));
        //sprintf(buf, "holle world unix socket%d\n", num);
        len = send(client_sockfd, buf, sizeof(buf), 0);
        if (len > 1) {
            printf("==============send-start==============\n");
            printf("%s\n", buf);
            sleep(2);
            if (count > 100) {//every 100 byte to print
                printf("have send %d byte\n", 100*num);
                count = 0;
            }
        }
    }

    exit(0);
}

