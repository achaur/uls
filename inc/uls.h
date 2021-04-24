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


//structure which holds file tree
typedef struct  s_file {
    struct stat filestat;       //standard struct to hold file data
    char *name;                 //file name
    char *path;                 //path to file
    struct s_file *level;       //pointer to next level (sub-directory)
    struct s_file *next;        //pointer to next level in this directory
}               t_file;

//structure which holds table to print
typedef struct  s_table {
    int rows;                   //number of rows in table
    int cols;                   //number of columns in table
    int *max_col_size;          //array which holds max col width (for true intendation)
    char ***table;              //2-D array of strings (data to print)
}               t_table;

/*--- Parsing ---*/
t_file *mx_scan_dir(char *path);

/*--- Utils ---*/
bool mx_is_root(const char *dir);
char *mx_get_fullpath(const char *path, const char *file);

/*--- Print ---*/
//how much spaces between columns
#define TAB_SIZE    2

void mx_print_table(t_table *table);
t_table *mx_allocate_table(int rows, int cols);

#endif
