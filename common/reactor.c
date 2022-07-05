/*************************************************************************
	> File Name: reactor.c
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Thu May 19 17:36:17 2022
 ************************************************************************/

#include "head.h"

extern struct User *users;
extern int subfd;
extern WINDOW *msg_win, *sub_msg_win, *input_win, *sub_input_win, *help_win, *sub_help_win;

void add_event_ptr(int epollfd, int fd, int events, struct User *user) {
	struct epoll_event ev;
	ev.events = events;
	ev.data.ptr = (void *)user;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
	return ;
}


int add_to_reactor(int fd, struct User *user) {
    int sub = user->fd;
    users[sub] = *user;

    add_event_ptr(fd, users[sub].fd, EPOLLIN | EPOLLET, &users[sub]);

    return 0;
}

void del_from_reactor(int fd) {
	
	epoll_ctl(subfd, EPOLL_CTL_DEL, fd, NULL);

	return ;
}

void *reactor(void *arg) {
	struct epoll_event events[20];
	struct Msg msg;
	while (1) {

		int nfds = epoll_wait(subfd, events, 20, -1);

		if (nfds < 0) exit(1);

		for (int i = 0; i < nfds; i++) {
			int fd = ((struct User *)(events[i].data.ptr))->fd;
			recv(fd, &msg, sizeof(msg), 0);
            if (msg.type != CHAT_HEART && msg.type != CHAT_ACK) print_message(sub_msg_win, &msg, 1);
			users[i].cnt = 10;
			if (msg.type & CHAT_HEART) {
				DBG(YELLOW"<%s>"NONE" : ❥(^_-) ---> "YELLOW"<My Me>"NONE"\n", users[fd].name);
				msg.type = CHAT_ACK;
				send(fd, &msg, sizeof(msg), 0);
			} else if (msg.type & CHAT_ACK) {
				DBG(YELLOW"<My Me>"NONE" : ❤ ---> "YELLOW"<%s>"NONE"\n", users[fd].name);
			} else if (msg.type & CHAT_FIN) {
				DBG(YELLOW"<%s>"NONE""RED" : @ Goodbye !!!"NONE"\n", users[fd].name);
				// epoll_ctl delete from sub reactor
				del_from_reactor(fd);
				close(fd);
				users[fd].flag = 0;
				DBG(YELLOW"<%s>"NONE""RED" : @ is leaving !"NONE"\n", users[fd].name);
				DBG(LIGHT_CYAN"king::"NONE""YELLOW"<%s>"NONE""RED" is removed from sub reactor..."NONE"\n", users[fd].name);
			} else if (msg.type & CHAT_MSG) {
				DBG(YELLOW"<%s>"NONE" : %s\n", msg.from, msg.msg);
			} else {
				DBG("*\n");
			}
		}
	}
	return NULL;
}

