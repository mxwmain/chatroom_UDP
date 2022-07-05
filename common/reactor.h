/*************************************************************************
	> File Name: reactor.h
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Fri May 20 18:32:16 2022
 ************************************************************************/

#ifndef _REACTOR_H
#define _REACTOR_H


void add_event_ptr(int, int, int, struct User *);
int add_to_reactor(int, struct User *);
void *reactor(void *);
void del_from_reactor(int);

#endif
