/*************************************************************************
	> File Name: Wechat.h
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Thu May 19 16:13:25 2022
 ************************************************************************/

#ifndef _WECHAT_H
#define _WECHAT_H

#define MAX 10
#define MAXUSER 1000

#define CHAT_SYN 0x001
#define CHAT_ACK 0x002
#define CHAT_FIN 0x004
#define CHAT_HEART 0x008
#define CHAT_MSG 0x010

struct Msg {
    int type;
    char from[20];
    char to[20];
    char msg[1024];
};

#define FL_SYNSENT 0x001
#define FL_ONLINE 0x002

struct User {
    char name[20];
    char ip[20];
    int flag; //用户当前的状态
    int fd;
    int cnt; //发出心跳的次数，当这个值到达10的时候，删除好友
};

void logout(int);

#define MSG_WIDTH 100
#define MSG_HEIGHT 25
#define HELP_WIDTH 15
#define INPUT_HEIGHT 5

#endif
