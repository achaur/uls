#ifndef _ULS_H
#define _ULS_H

#include "libmx.h"

#include <stdio.h>
#include <string.h>

//for stat
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

//for dir functions
#include <dirent.h>

#include <sys/errno.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
// #include <sys/acl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <ctype.h>

#define MX_IFMT   0170000  /* type of file mask */
#define MX_IFIFO  0010000  /* named pipe (fifo) */
#define MX_IFCHR  0020000  /* character special */
#define MX_IFDIR  0040000  /* directory */
#define MX_IFBLK  0060000  /* block special */
#define MX_IFREG  0100000  /* regular */
#define MX_IFLNK  0120000  /* symbolic link */
#define MX_IFSOCK 0140000  /* socket */
#define MX_IFWHT  0160000  /* whiteout */
#define MX_ISUID  0004000  /* set user id on execution */
#define MX_ISGID  0002000  /* set group id on execution */
#define MX_ISVTX  0001000  /* save swapped text even after use */
#define MX_IRWXU  0000700  /* RWX mask for owner */
#define MX_IRUSR  0000400        /* R ead permission, owner */
#define MX_IWUSR  0000200        /* W rite permission, owner */
#define MX_IXUSR  0000100        /* X execute/search permission, owner */
#define MX_IRWXG  0000070  /* RWX mask for group */
#define MX_IRGRP  0000040        /* R ead permission, group */
#define MX_IWGRP  0000020        /* W rite permission, group */
#define MX_IXGRP  0000010        /* X execute/search permission, group */
#define MX_IRWXO  0000007  /* RWX mask for other */
#define MX_IROTH  0000004        /* R ead permission, other */
#define MX_IWOTH  0000002        /* W rite permission, other */
#define MX_IXOTH  0000001        /* X execute/search permission, other */

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
    int size;
    char *name;
    int flags_num;
    char **files;
    int files_num;
    int argcf;
    int *indexes_of_files;
}              t_uls;

//structure which holds uls flags
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
    struct passwd *pwd;         //standard struct to hold user account information
    struct group *grp;          //standard struct to hold group information
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

void mx_one_arg(int argc, char **argv);

    /*--- Parsing arguments---*/
void mx_parse_argc(int argc, char **argv, t_uls *data, t_flags *flags);

    /*--- Parsing file/dir tree---*/
t_file *mx_scan_dir(char *path);

    /*--- Utils ---*/
bool mx_is_root(const char *dir);
char *mx_get_fullpath(const char *path, const char *file);

    /*--- Errors ---*/
void mx_invalid_flag(char c);
void mx_printerr(const char *s);
void mx_invalid_file (char *argv);

/*--- Print ---*/
//how much spaces between columns
#define TAB_SIZE    2
void mx_print_table(t_table *table);
t_table *mx_allocate_table(int rows, int cols);

#endif

char *mx_get_links_num(char *file_name);
char *mx_get_user_rights(t_file *file, t_flags *flags);
int mx_get_user_id(t_file *file, t_flags *flags);
