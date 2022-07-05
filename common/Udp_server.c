/*************************************************************************
	> File Name: Udp_server.c
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Wed May 18 10:39:11 2022
 ************************************************************************/

#include "head.h"

extern int subfd;

int socket_create_udp(int port) {

    int listener;
    if ((listener = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);
    
    unsigned long opt = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(listener, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }

    return listener;
}

int udp_accept(int fd, struct User *user) {
    int new_fd, ret;
    struct sockaddr_in client;
    struct Msg request, response;
    socklen_t len = sizeof(client);
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));

    ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len);
    
    if (ret != sizeof(request)) {
        response.type = CHAT_FIN;
        strcpy(response.msg, "Login Request Error!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;
    }

    /*
    if (check_online(&request)) {
        response.type = CHAT_FIN;
        strcpy(response.msg, "Login Request Error!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;
    }
    */
    if (request.type & CHAT_FIN) {
        return -1;
    } else if ((request.type & CHAT_SYN) && (request.type & CHAT_ACK)) {
        DBG(GREEN"<Acceptor>"NONE" : SYNACK recived!\n");
    } else if (request.type != CHAT_SYN) {
        response.type = CHAT_FIN;
        strcpy(response.msg, "Error Request!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        DBG(YELLOW"Request.from = %s, Request.msg = %s"NONE"\n", request.from, request.msg);
        return -1;   
    }

    DBG(GREEN"<Acceptor>"NONE" : [%s] %s...\n", request.from, request.msg);

    //if (!strlen(request.from)) strcpy(user->name, request.from);
    user->flag = FL_ONLINE;
    user->cnt = 10;
    new_fd = udp_connect(&client);
    
    if (new_fd < 0) {
        perror("udp_connect");
        return -1;
    }

    user->fd = new_fd;
    char buff[512] = {0};
    sprintf(buff, "%s Login success!\n", user->name);
    strcpy(response.msg, buff);
    response.type = CHAT_ACK | CHAT_SYN;
    send(new_fd, (void *)&response, sizeof(response), 0);

    return new_fd;
}









