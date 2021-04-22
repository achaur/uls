#include "uls.h"

static bool mx_check_file(char *argv) {
    struct stat buffer;
    return (stat (argv, &buffer) == 0);
}

void mx_get_files_names(int argc, char **argv, t_uls *data) {
    // printf("%d\n", data->argcf);
    int files_num = argc - 1 - data->argcf;
    // printf("%d\n", files_num);
    data->files = (char **)malloc(sizeof(char *)*files_num + 1);
    int k = 0;
    int count = 0;
    int i = 1;

    while (i < argc) {
        for (int i = 1; argv[i][0] != '-'; i++) {
            if (mx_check_file(argv[i])) {
                data->files[k] = (char *)malloc(sizeof(char) *mx_strlen(argv[i]) + 1);
                strcpy(data->files[k++], argv[i]);
                count++;
            } 
            else if (!mx_check_file(argv[i])){
                mx_invalid_file(argv[i]);
            }
        }   
    }
    data->files_num = count;
    // for (int i = 0; i < data->files_num; i++) {
    //     printf("%s\n", data->files[i]);
    // }
}
