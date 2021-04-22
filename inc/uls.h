#pragma once

#include "libmx.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define _XOPEN_SOURCE
#define FLAGS     "@1AaCcFfGhlmpRrSTtu\0"
#define FLAGS_NUM 20
#define RED       "\x1B[31m"
#define GRN       "\x1B[32m"
#define YEL       "\x1B[33m"
#define BLU       "\x1B[34m"
#define MAG       "\x1B[35m"
#define RESET     "\x1B[0m"
#define BLK_F_RED_B "\x1B[0;30;41m"
#define BLK_F_CYAN_B "\x1B[0;30;46m"
#define BLOCK "\x1B[0;34;46m"
#define CHR "\x1B[0;34;43m"
#define DIR_T "\x1B[0;30;42m"
#define DIR_X "\033[0;30;43m"

typedef struct s_uls {
    char *flags;
    int size;
    char *name;
    int flags_num;
    char **files;
    int files_num;
    int argcf;
}              t_uls;

//structure, which contains file/directory properties
// typedef struct s_fstat {
//     int size;
//     char *name;
//     char *flags;
// }              t_fstat;

// element of linked-list tree
typedef struct  s_node {
    t_uls *fstat;
    struct s_node *level;
    //pointer to next recursive level
    //if node element is a directory, points to next level linked list
    //if node element is a file, points to NULL
    struct s_node *next;
}               t_node;

typedef struct  s_arg {
    t_node *node;
    struct s_arg *next;
}               t_arg;

void mx_one_arg(int argc, char **argv);

//parsing
void mx_get_flags(int argc, char **argv, t_uls *data);
void mx_get_files_names(int argc, char **argv, t_uls *data);

//errors
void mx_invalid_flag(char c);
void mx_printerr(const char *s);
void mx_invalid_file (char *argv);
