#ifndef _ULS_H
#define _ULS_H

#include <stdio.h>
#include "libmx.h"

//for stat
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

//for dir functions
#include <dirent.h>

typedef struct s_flags {
    bool r;/*SORTING FLAGS TO IMPLEMENT*/
    bool S;
    bool t;
    bool u;
    bool c;
    bool U;
    bool l;/*PRINT FLAGS TO IMPLEMENT*/
    bool a;
    bool A;
    bool G;
    bool h;
    bool i;
    bool n;
    bool p;
    bool one;
}              t_flags;

//structure which holds file tree
typedef struct  s_file {
    struct stat filestat;       //standard struct to hold file data
    char *name;                 //file name
    char *path;                 //path to file
    struct s_file *level;       //pointer to next level (sub-directory)
    struct s_file *next;        //pointer to next level in this directory
}               t_file;


/*--- Parsing ---*/
t_file *mx_scan_dir(char *path);

/*--- Utils ---*/
bool mx_is_root(const char *dir);
char *mx_get_fullpath(const char *path, const char *file);

#endif
