#include "uls.h"

static void mx_flags_init(t_flags *flags) {
    flags->r = false;
    flags->S = false;
    flags->t = false;
    flags->u = false;
    flags->c = false;
    flags->U = false;
    flags->l = false;
    flags->a = false;
    flags->A = false;
    flags->G = false;
    flags->h = false;
    flags->i = false;
    flags->n = false;
    flags->p = false;
    flags->one = false;
}

static void mx_flags_def(t_flags *flags, char *str) {
    for (int i = 1; str[i] != '\0'; i++) {
        printf("Flag: %c\n", str[i]);
        switch (str[i]) {
            case 'r':
                flags->r = true;
                break;
            case 'S':
                flags->S = true;
                break;
            case 't':
                flags->t = true;
                break;
            case 'u':
                flags->u = true;
                break;
            case 'c':
                flags->c = true;
                break;
            case 'U':
                flags->u = true;
                break;
            case 'l':
                flags->l = true;
                break;
            case 'a':
                flags->a = true;
                break;
            case 'A':
                flags->A = true;
                break;
            case 'G':
                flags->G = true;
                break;
            case 'h':
                flags->h = true;
                break;
            case 'i':
                flags->i = true;
                break;
            case 'n':
                flags->n = true;
                break;
            case 'p':
                flags->p = true;
                break;
            case '1':
                flags->one = true;
                break;
            default:
                mx_invalid_flag(str[i]);
                break;
        }
    }
    
}

static void mx_get_flags(int argc, char **argv, t_uls *data, t_flags *flags) {
    int k = 0;
    int count = 0;
    // data->argcf = 0; 

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '\0') {
            mx_flags_def(flags, argv[i]);
            // data->argcf++;
        }
    }
    data->flags_num = count;
}

static bool mx_check_file(char *argv) {
    struct stat buffer;
    return (stat (argv, &buffer) == 0);
}

static void mx_get_files_names(int argc, char **argv, t_uls *data) {
    data->files_num = argc - 1 - data->argcf;
    data->files = (char **)malloc(sizeof(char *) * (data->files_num + 1));
    int k = 0;
    int count = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            data->files[k++] = mx_strdup(argv[i]);
        }
    }
    
}

void mx_parse_argc(int argc, char **argv, t_uls *data, t_flags *flags) {
    mx_flags_init(flags);
    bool tmp = false;
    data->argcf = 0; 

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && tmp == false) {
            mx_get_flags(argc, argv, data, flags);
            data->argcf++;
        }    
        else {
            mx_get_files_names(argc, argv, data);
            bool tmp = true;
        }
    }
}
