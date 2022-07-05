/*************************************************************************
	> File Name: heart_beat.c
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Wed May 25 10:13:15 2022
 ************************************************************************/

#include "head.h"

extern struct User *users;
extern char name[20];

void *heart_beat(void *arg) {
	struct Msg heart;
	heart.type = CHAT_HEART;
    strcpy(heart.from, name);
	while (1) {
		for (int i = 0; i < MAXUSER; i++) {
			if (users[i].flag) {
				if (users[i].cnt <= 0) {
					DBG(YELLOW"<%s>"NONE""RED" is removed by heart beat..."NONE"\n", users[i].name);
					users[i].flag = 0;
					del_from_reactor(users[i].fd);
					DBG(LIGHT_CYAN"king::"NONE""YELLOW"<%s>"NONE""RED" is removed from sub reactor..."NONE"\n", users[i].name);
					close(users[i].fd);
				}
				send(users[i].fd, (void *)&heart, sizeof(heart), 0);
				users[i].cnt--;
			}
		}
		sleep(30);
	}
	return NULL;
}
