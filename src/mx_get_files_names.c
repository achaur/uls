#include "uls.h"

static bool mx_check_file(char *argv) {
    struct stat buffer;
    return (stat (argv, &buffer) == 0);
}

void mx_get_files_names(int argc, char **argv, t_uls *data) {
    int files_num = argc - 1 - data->argcf;
    data->files = (char **)malloc(sizeof(char *) * (files_num + 1));
    int k = 0;
    int count = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            data->files[k++] = mx_strdup(argv[i]);
        }
    }
}
