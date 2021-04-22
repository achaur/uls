#include "uls.h"

int main(int argc, char **argv) {
    t_uls *data = (t_uls *)malloc(sizeof(t_uls));

    if (argc == 1) 
        mx_one_arg(argc, argv);
    else {
        mx_get_flags(argc, argv, data);
        mx_get_files_names(argc, argv, data);
    }
        
    return 0;
}
