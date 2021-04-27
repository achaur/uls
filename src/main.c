#include "uls.h"

int main(int argc, char **argv) {
        //allocate struct for data and flags
    t_uls *data = (t_uls *)malloc(sizeof(t_uls));
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));
        //parse arguments
    mx_parse_argc(argc, argv, data, flags);
        //read file tree
    t_file *tree = mx_get_tree(data->files, flags);

        /*--- Try to print --- */
        t_file *temp = tree;
    while (temp != NULL) {
        printf("%s:\n", temp->name);
        mx_print_dir(temp, flags);
        if(temp->next != NULL)
            printf("\n");
        temp = temp->next;
    }

    mx_free_dir(tree);
    
    return 0;
}
