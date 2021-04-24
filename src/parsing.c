#include "uls.h"

//create new node filled with data
static t_file *file_create_node(char *name, char *path) {
    t_file *node = (t_file*)malloc(sizeof(t_file));

        //get fullpath to file/directory
    char *fullpath = mx_get_fullpath(path, name);
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
        if(!mx_is_root(node->name)) {
            printf("%s is a directory\n", node->name);
            printf("\tGoing next level..\n");
            node->level = mx_scan_dir(fullpath);
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
static void file_push_back(t_file **file, char *name, char *path) {
    if (*file == NULL) {
        *file = file_create_node(name, path);
    return;
    }
        //find end of list
    t_file *current = *file;
    while(current->next != NULL)
        current = current->next;
        //fill data for next node
    current->next = file_create_node(name, path);
}

/*----- TO-DO:
        CHECK FOR -R FLAG, IF NOT SET, DON'T GO RECURSIVE
------------*/

//scan directory contents and fill data tree
t_file *mx_scan_dir(char *path) {
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

    if (!dir) {
        perror("directory not opened\n");
        // exit(1);
        return NULL;
    } else
        printf("directory opened\n");

    //read directory contents
    while ((entry = readdir(dir)) != NULL) {
        printf("Counter: %d, Filename: %s\n", counter++, entry->d_name);
        file_push_back(&filelist, entry->d_name, path);
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
