/*************************************************************************
	> File Name: common.c
	> Author: King_meng
	> Mail: 1936538304@qq.com
	> Created Time: Wed May 18 15:12:09 2022
 ************************************************************************/

#include "head.h"

char conf_value_ans[512] = {0};

char *get_value(const char *path, const char *key) {
    FILE *fp = NULL;
    char *line = NULL, *sub;
    ssize_t nread, len;
    if (path == NULL || key == NULL) {
        fprintf(stderr, "argument error\n");
        exit(1);
    }

    if ((fp = fopen(path, "r")) == NULL) {
        fprintf(stderr, "file open error\n");
        exit(1);
    }

    while ((nread = getline(&line, &len, fp)) != -1) {
        if ((sub = strstr(line, key)) == NULL) continue;
    
        if (line[strlen(key)] == '=' && sub == line) {
            strcpy(conf_value_ans, line + strlen(key) + 1);
            conf_value_ans[strlen(conf_value_ans) - 1] = '\0';
        }
        
    }
    free(line);
    fclose(fp);
    return conf_value_ans;
}
