/*************************************************************************
	> File Name: Udp_server.h
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Wed May 18 10:39:30 2022
 ************************************************************************/

#ifndef _UDP_SERVER_H
#define _UDP_SERVER_H

int socket_create_udp(int);
int udp_accept(int, struct User *);

#endif
