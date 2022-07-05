/*************************************************************************
	> File Name: Udp_client.c
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Wed May 18 11:29:18 2022
 ************************************************************************/

#include "head.h"

extern int port;

int socket_udp() {

    int socketfd;

    if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }

    return socketfd;
}

int udp_connect(struct sockaddr_in *client) {
    int sockfd;

    if ((sockfd = socket_create_udp(port)) < 0) {
        return -1;
    }
    client->sin_port = htons(8888);
    if (connect(sockfd, (struct sockaddr *)client, sizeof(struct sockaddr)) < 0) {
        return -1;
    }

    return sockfd;
}
