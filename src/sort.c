    /*--- SORTING FLAGS TO IMPLEMENT ---
        -r : Reverse order
        -S : Sort by size
        -t : Sort by time modified (stat.st_mtime)
        -u : Sort by time accessed (stat.st_atime)
        -c : Sort by time of permissions modified (stat.st_ctime)
            about -c and -u flag: read 'man ls' carefully,
            there are some features about sorting
        -U : do not sort at all
        default sorting: alphabetical
    *--------------------------------------*/
#include "uls.h"

//sort by name
bool by_name(t_file *node1, t_file *node2) {
    if (mx_strcicmp(node1->name, node2->name) > 0)
        return true;
    else
        return false;
}

//Sort by size
bool by_size(t_file *node1, t_file *node2) {
    if (node1->filestat.st_size < node2->filestat.st_size)
        return true;
    else
        return false;
}

//Sort by time of permissions modified
bool by_ctime(t_file *node1, t_file *node2) {
    if (node1->filestat.st_ctime < node2->filestat.st_ctime)
        return true;
    else
        return false;
}

//Sort by time modified
bool by_mtime(t_file *node1, t_file *node2) {
    if (node1->filestat.st_mtime < node2->filestat.st_mtime)
        return true;
    else
        return false;
}

//Sort by time accessed
bool by_atime(t_file *node1, t_file *node2) {
    if (node1->filestat.st_atime < node2->filestat.st_atime)
        return true;
    else
        return false;
}

//sorting function
t_file *sort(t_file *dir, bool(*cmp)(t_file *, t_file *)) {
    for (t_file *i = dir; i->next != NULL; i = i->next) {
        for (t_file *j = dir; j->next != NULL; j = j->next) {
            if (cmp(j, j->next)) {
                    //swap names
                char *temp_name = j->next->name;
                j->next->name = j->name;
                j->name = temp_name;
                    //swap paths
                char *temp_path = j->next->path;
                j->next->path = j->path;
                j->path = temp_path;
                    //swap stat
                struct stat temp_stat = j->next->filestat;
                j->next->filestat = j->filestat;
                j->filestat = temp_stat;
                    //swap level
                t_file *temp_level = j->next->level;
                j->next->level = j->level;
                j->level = temp_level;
                }
        }
    }
    return dir;
}

t_file *mx_sort_dir(t_file *dir, t_flags *flags) {
    t_file *sorted = NULL;

    if (flags->U)
        //do not sort at all
        return dir;

    sorted = sort(dir, by_name);
    if(flags->S) {
        //sort by size
        sorted = sort(sorted, by_size);
    } else if (flags->t) {
        //sort by mtime
        sorted = sort(sorted, by_mtime);
    } else if (flags->u) {
        //sort by atime
        sorted = sort(sorted, by_atime);
    } else if (flags->c) {
        //sort by ctime
        sorted = sort(sorted, by_ctime);
    }

    return sorted;
}
