#include "uls.h"

//prototype for recursive use
static t_file *scan_dir(char *path);

//create new node filled with data
//if called with first = 1, then read '.' and '..'
//for next calls, first = 0 and those dirs don't go recursive
static t_file *file_create_node(char *name, char *path, bool first) {
    t_file *node = (t_file*)malloc(sizeof(t_file));

        //get fullpath to file/directory
    char *fullpath = mx_get_fullpath(name, path);
    printf("Fullpath: %s\n", fullpath);
        //try to read stat
    
    /*--- ADD ERROR HANDLING HERE ---
        if stat() returns -1:
        errno = ENOENT - file or path not found
    --------------------------------*/

    int statnum = stat(fullpath, &(node->filestat));
    printf("Stat for %s returned %d\n", name, statnum);
        //fill data stucture with name and path
    node->name = mx_strdup(name);
    node->path = mx_strdup(path);
        //if directory, call recursive
    if(S_ISDIR(node->filestat.st_mode)) {
        if (first) {
            printf("%s is a directory\n", node->name);
            printf("\tGoing next level..\n");
            node->level = scan_dir(fullpath);
        } else if(!mx_is_root(node->name)) {
            printf("%s is a directory\n", node->name);
            printf("\tGoing next level..\n");
            node->level = scan_dir(fullpath);
        }
    } else {
        node->level = NULL;
    }
    node->next = NULL;

    //free memory
    mx_strdel(&fullpath);
    return node;
}

//push back data to file list
static void file_push_back(t_file **file, char *name, char *path, bool first) {
    if (*file == NULL) {
        *file = file_create_node(name, path, first);
    return;
    }
        //find end of list
    t_file *current = *file;
    while(current->next != NULL)
        current = current->next;
        //fill data for next node
    current->next = file_create_node(name, path, first);
}

/*----- TO-DO:
        CHECK FOR -R FLAG, IF NOT SET, DON'T GO RECURSIVE
------------*/

//scan directory contents and fill data tree
static t_file *scan_dir(char *path) {
    t_file *filelist = NULL;
    DIR *dir;
    struct dirent *entry;
    int counter = 0;

        //error handling prototype
    printf("Opening directory: %s\n", path);
    dir = opendir(path);

        /*--- ADD ERROR HANDLING HERE ---
        if opendir() returns -1:
        errno = ENOENT - file or path not found
        errno = ENOMEM - not enough memory
    --------------------------------*/

    //read directory contents
    while ((entry = readdir(dir)) != NULL) {
        printf("Counter: %d, Filename: %s\n", counter++, entry->d_name);
        file_push_back(&filelist, entry->d_name, path, 0);
    }

    closedir(dir);

            /*--- ADD ERROR HANDLING HERE ---
        if closedir() returns -1:
        errno = EBADF - wrong directory
    --------------------------------*/

    printf("\tClosing directory %s\n", path);

    /*--- ADD SORTING FUNCTION HERE ---
    *--------------------------------------*/

    return filelist;
}

t_file *mx_get_tree(char **files) {
    t_file *filelist = NULL;
        //if no arguments, use default one
    if (*files == NULL) {
        file_push_back(&filelist, ".", NULL, 1);
    } else
        for (int file = 0; files[file] != NULL; file++)
            file_push_back(&filelist, files[file], NULL, 1);

    return filelist;
}