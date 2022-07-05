/*************************************************************************
	> File Name: chat_ui.h
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Tue Jul  5 15:30:06 2022
 ************************************************************************/

#ifndef _CHAT_UI_H
#define _CHAT_UI_H

#include <ncurses.h>
#include "Wechat.h"

void gotoxy(int, int);
void gotoxy_putc(int, int, char);
void gotoxy_puts(int, int, char*);
void w_gotoxy_putc(WINDOW*, int, int, char);
void w_gotoxy_puts(WINDOW*, int, int, char*);
void init_ui();
void print_message(WINDOW*, struct Msg*, int);
void show_help();
WINDOW *create_newwin(int, int, int, int);


#endif
