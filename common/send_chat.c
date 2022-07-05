/*************************************************************************
	> File Name: send_chat.c
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Thu May 26 09:12:42 2022
 ************************************************************************/

#include "head.h"

extern char name[20];
extern struct User *users;
extern WINDOW *msg_win, *sub_msg_win, *input_win, *sub_input_win, *help_win, *sub_help_win;

void *send_chat(void *arg) {
	struct Msg msg;
	strcpy(msg.from, name);
	msg.type = CHAT_MSG;
	while (1) {
		memset(msg.msg, 0, sizeof(msg.msg));
		//printf("Please Input :\n");
		//scanf("%s", msg.msg);
		wgetstr(sub_input_win, msg.msg);
        print_message(sub_msg_win, &msg, 0);
        werase(sub_input_win);
        for (int i = 0; i < MAXUSER; i++) {
			if (users[i].flag) {
				send(users[i].fd, &msg, sizeof(msg), 0);
			}
		}
	}
	return NULL;
}
