/*************************************************************************
	> File Name: wechat.c
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Wed May 18 14:57:49 2022
 ************************************************************************/

#include "head.h"

char *config = "./chat.conf";

int port = 0;
char name[20] = {0};
char msg[512] = {0};
struct User *users;
int subfd;
WINDOW *msg_win, *sub_msg_win, *input_win, *sub_input_win, *help_win, *sub_help_win;
int msg_num;

int main(int argc, char **argv) {

    int opt, listener, epollfd, new_fd;
    pthread_t c_discover, heart_beat_tid, reactor_tid, send_tid;
    while ((opt = getopt(argc, argv, "p:n:m:")) != -1) {
        switch(opt) {
            case 'p': {
                port = atoi(optarg);
                break;
            }
            case 'm': {
                strcpy(msg, optarg);
                break;
            }
            case 'n': {
                strcpy(name, optarg);
                break;
            }
            default:
                fprintf(stderr, "Usage : %s -n name -p port, -m msg\n", argv[0]);
                exit(1);
        }
    }

    signal(SIGINT, logout);
    
    initscr();
    keypad(sub_input_win, TRUE);
    echo();
    cbreak();
    init_ui();

    if (!strlen(name)) strncpy(name, get_value(config, "name"), 20);
    if (!strlen(msg)) strncpy(msg, get_value(config, "msg"), sizeof(msg));
    if (!port) port = atoi(get_value(config, "port"));

    DBG(BLUE"<Starting...>"NONE"name = %s, port = %d, msg = %s\n", name, port, msg);
    
    if ((listener = socket_create_udp(port)) < 0) {
        perror("socket_create_udp");
        exit(1);
    }

    DBG(BLUE"<Starting...>"NONE"listener %d ok!\n", listener);
    
    if ((epollfd = epoll_create(1)) < 0) {
        perror("epoll_create");
        exit(1);
    }


    if ((subfd = epoll_create(1)) < 0) {
        perror("epoll_create");
        exit(1);
    }
    
    struct epoll_event ev, events[MAX];
    users = (struct User *)calloc(MAXUSER, sizeof(struct User));

    ev.events = EPOLLIN;
    ev.data.fd = listener;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0) {
        perror("epoll_ctl");
        exit(1);
    }

    pthread_create(&c_discover, NULL, client_discover, NULL);
    pthread_create(&heart_beat_tid, NULL, heart_beat, NULL);
    pthread_create(&reactor_tid, NULL, reactor, NULL);
    pthread_create(&send_tid, NULL, send_chat, NULL);
    while (1) {
        int nfds = epoll_wait(epollfd, events, MAX, -1);

        DBG(LIGHT_CYAN"KING::"NONE""RED"<Main Reactor>"NONE" : Got Events...\n");

        if (nfds < 0) {
            perror("epoll_wait");
            exit(1);
        }

        for (int i = 0; i < nfds; i++) {
            struct User newuser;
            strcpy(newuser.name, name);
            if ((new_fd = udp_accept(listener, &newuser)) < 0) {
                fprintf(stderr, "error in udp_accept!\n");
                continue;
            }

            // 添加到从反应堆
            add_to_reactor(subfd, &newuser);
            DBG(LIGHT_CYAN"KING::"NONE""RED"<Main Reactor>"NONE" : Adding client to sub reactor...\n");
        }
    }

    return 0;
}


void logout(int signum) {
    struct Msg l_msg;
    l_msg.type = CHAT_FIN;
    strcpy(l_msg.from, name);
    strcpy(l_msg.msg, "left the chat room.......");
    for (int i = 0; i < MAXUSER; i++) {
        if (users[i].flag & FL_ONLINE) {
            send(users[i].fd, &l_msg, sizeof(l_msg), 0);
        }
    }

    DBG("\n"YELLOW"<%s>"NONE""RED" : logout from wechat system...."NONE"\n", name);
    exit(0);

    return ;
}
