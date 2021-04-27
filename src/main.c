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
    while (tree != NULL) {
        printf("%s:\n", tree->name);
        mx_print_dir(tree, flags);
        if(tree->next != NULL)
            printf("\n");
        tree = tree->next;
    }
    return 0;
}
