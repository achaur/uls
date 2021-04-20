#include "libmx.h"

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <sys/errno.h>

//structure, which contains file/directory properties
typedef struct  s_fstat {
    /*some data*/
    int size;
    char *name;
}               t_fstat;

//element of linked-list tree
typedef struct  s_node {
    struct s_fstat *fstat;
//pointer to next recursive level
//if node element is a directory, points to next level linked list
//if node element is a file, points to NULL
    struct s_node *level;
    struct s_node *next;
}               t_node;

void mx_one_flag(int argc, char **argv);

