#include "uls.h"

int main(int argc, char **argv) {
    t_uls *data = (t_uls *)malloc(sizeof(t_uls));
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));

    mx_parse_argc(argc, argv, data, flags);
    // mx_flags_init(flags);
    // if (argc == 1) 
    //     mx_one_arg(argc, argv);
    // else {
    //     mx_get_flags(argc, argv, data, flags);
    //     mx_get_files_names(argc, argv, data);
    // }   

    for (int i = 0; i < data->files_num; i++) {
        printf("%s\n", data->files[i]);
    }
    return 0;
}
