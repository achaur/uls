#include "uls.h"

int main(int argc, char **argv) {
        //allocate struct for data and flags
    t_uls *data = (t_uls *)malloc(sizeof(t_uls));
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));
        //parse arguments
    mx_parse_argc(argc, argv, data, flags); 
        //read file tree
    t_file *tree = mx_get_tree(data->files, flags, argc, data->files_num, data->argcf);
        /*--- Try to print --- */
    mx_print_tree(tree, flags);
    mx_free_dir(tree);
    mx_clean_memory(data, flags);

    return errno;
}
