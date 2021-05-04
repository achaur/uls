#include "uls.h"

//prototype for recursive use
static t_file *scan_dir(char *path, t_flags *flags);

//create new node filled with data
//if called with first = 1, then read '.' and '..'
//for next calls, first = 0 and those dirs don't go recursive
static t_file *file_create_node(char *name, char *path, bool first, t_flags *flags) {
    t_file *node = (t_file*)malloc(sizeof(t_file));
        //get fullpath to file/directory
    char *fullpath = mx_get_fullpath(name, path);
        //try to read stat
    lstat(fullpath, &(node->filestat));
        //if not long listing, follow the link
    if(!flags->l && !flags->n) {
        if(S_ISLNK(node->filestat.st_mode))
            stat(fullpath, &(node->filestat));
    }
        //fill data stucture with name and path
        //if it is link, show where it points
    if(S_ISLNK(node->filestat.st_mode))
        node->name = mx_get_link(fullpath, name);
    else
        node->name = mx_strdup(name);
    node->path = mx_strdup(path);

    if(S_ISDIR(node->filestat.st_mode)) {
        if (first) {
                //if this is the first call of scandir, dont check for root directory
            node->level = scan_dir(fullpath, flags);
        } else if (flags->R) {
                //if not first call, check for recursion available
            if(!mx_is_root(node->name)) {
                node->level = scan_dir(fullpath, flags);
            } else
                node->level = NULL;
        } else {
                //no next level
            node->level = NULL;
        }
    } else {
            //no next level
        node->level = NULL;
    }
    node->next = NULL;
    //free memory
    mx_strdel(&fullpath);
    return node;
}

//push back data to file list
static void file_push_back(t_file **file, char *name, char *path, bool first, t_flags *flags) {
    if (*file == NULL) {
        *file = file_create_node(name, path, first, flags);
    return;
    }
        //find end of list
    t_file *current = *file;
    while(current->next != NULL)
        current = current->next;
        //fill data for next node
    current->next = file_create_node(name, path, first, flags);
}

//scan directory contents and fill data tree
static t_file *scan_dir(char *path, t_flags *flags) {
    t_file *filelist = NULL;
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    //read directory contents
    while ((entry = readdir(dir)) != NULL) {
        if (mx_is_root(entry->d_name)) {
            if (flags->a) {
                file_push_back(&filelist, entry->d_name, path, 0, flags);
            }
        } else if (mx_is_hidden(entry->d_name)) {
            if (flags->a || flags->A) {
                file_push_back(&filelist, entry->d_name, path, 0, flags);
            }
        } else {
            file_push_back(&filelist, entry->d_name, path, 0, flags);
        }
    }

    closedir(dir);
    /*--- ADD SORTING FUNCTION HERE ---
    *--------------------------------------*/

    return filelist;
}

//push back NULL shows that this is very first level
//of files data tree
t_file *mx_get_tree(char **files, t_flags *flags, int argc, int files_num, int argcf) {
    t_file *filelist = NULL;
        //if no arguments, use default one
    if (argc != 1 && files_num == 0 && argcf == 0) 
        exit(1);
    else if (*files == NULL) {
        file_push_back(&filelist, ".", NULL, 1, flags);
    } else
        for (int file = 0; files[file] != NULL; file++)
            file_push_back(&filelist, files[file], NULL, 1, flags);

    return filelist;
}
