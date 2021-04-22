#include "uls.h"

static void mx_check_flags(t_uls *data, char *argv, int *count) {
    int k = 0;
    int len_argv = mx_strlen(argv);
    int j = 1, i, cout;
    
    while (j < len_argv) {
        i = 0;
        cout = 0;
        while (FLAGS[i] != '\0' && i < FLAGS_NUM) {
            if (argv[j] == FLAGS[i]) {
                data->flags[k++] = argv[j++];
                (*count)++;
                cout++;
            }
            i++;
        }
        if (cout == 0)
            mx_invalid_flag(argv[j]);
    }
}

void mx_get_flags(int argc, char **argv, t_uls *data) {
    int k = 0;
    int count = 0;
    data->argcf = 0;

    data->flags = (char *)malloc(sizeof(char)); 
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '\0') {
            mx_check_flags(data, argv[i], &count);
            data->argcf++;
        }
    }
    // printf("%d\n", data->argcf);
    // printf("%s\n", data->flags);
    data->flags_num = count;
}
