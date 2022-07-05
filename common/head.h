/*************************************************************************
	> File Name: head.h
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Wed May 18 11:12:02 2022
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/sem.h>
#include <ncurses.h>
#include <locale.h>


#include "Wechat.h"
#include "common.h"
#include "Udp_server.h"
#include "Udp_client.h"
#include "reactor.h"
#include "client_discover.h"
#include "heart_beat.h"
#include "send_chat.h"
#include "chat_ui.h"

#ifdef _D
#define DBG(fmt, args...) printf(fmt, ##args);
#else 
#define DBG(fmt, args...)
#endif

#define NONE         "\033[m"
#define RED          "\033[0;32;31m"
#define LIGHT_RED    "\033[1;31m"
#define GREEN        "\033[0;32;32m"
#define LIGHT_GREEN  "\033[1;32m"
#define BLUE         "\033[0;32;34m"
#define LIGHT_BLUE   "\033[1;34m"
#define DARY_GRAY    "\033[1;30m"
#define CYAN         "\033[0;36m"
#define LIGHT_CYAN   "\033[1;36m"
#define PURPLE       "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN        "\033[0;33m"
#define YELLOW       "\033[1;33m"
#define LIGHT_GRAY   "\033[0;37m"
#define WHITE        "\033[1;37m"

#endif
