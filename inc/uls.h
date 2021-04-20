#include <stdio.h>
#include "libmx.h"


typedef struct s_flags {
    bool l; 
    bool R; 
    bool a; 
    bool A; 
    bool G; 
    bool h;
    bool atsign;//@
    bool e;
    bool T;
    bool one;//1
    bool r;
    bool t;
    bool u;
    bool c;
    bool S;
}              t_flags;

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
