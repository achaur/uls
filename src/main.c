#include "uls.h"

int main(int argc, char **argv) {
    printf("Hello uls!\n");

        //allocate struct for data and flags
    t_uls *data = (t_uls *)malloc(sizeof(t_uls));
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));

        //parse arguments
    mx_parse_argc(argc, argv, data, flags);

            //print out file arguments
    printf("\tArguments:\n");
    for (int i = 0; i < data->files_num; i++)
        printf("%s\n", data->files[i]);

        //scan directories recursively
    char *path = mx_strdup(argv[1]);
    t_file *fist = NULL;
    fist = mx_scan_dir(path);

    return 0;
}
