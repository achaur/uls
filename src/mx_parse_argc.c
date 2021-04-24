#include "uls.h"

static void flags_init(t_flags *flags) {
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

static void flags_get(t_flags *flags, char *str) {
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

static void get_files_names(int argc, char **argv, t_uls *data, int pos) {
    data->files_num = argc - 1 - data->argcf;
    data->files = (char **)malloc(sizeof(char *) * (data->files_num + 1));
    int k = 0;
    int count = 0;

    for (int i = pos; i < argc; i++) {
            // printf("arg: %s\n", argv[i]);
            data->files[k++] = mx_strdup(argv[i]);
    }
}

void mx_parse_argc(int argc, char **argv, t_uls *data, t_flags *flags) {
    flags_init(flags);
    bool tmp = false;
    data->argcf = 0; 
    int arg_so_far = 1;
    for (; arg_so_far < argc; arg_so_far++) {
        if (argv[arg_so_far][0] == '-' && tmp == false) {
            flags_get(flags, argv[arg_so_far]);
            data->argcf++;
        }    
        else {
            tmp = true;
            break;
        }
    }
    get_files_names(argc, argv, data, arg_so_far);
}
