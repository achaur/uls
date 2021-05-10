#include "uls.h"

static bool mx_check_file(char *argv) {
    struct stat buffer;
    return (stat (argv, &buffer) == 0);
}

static void flags_init(t_flags *flags) {
    flags->R = false;
    flags->S = false;
    flags->t = false;
    flags->u = false;
    flags->c = false;
    flags->U = false;
    flags->l = false;
    flags->a = false;
    flags->A = false;
    flags->G = false;
    flags->g = false;
    flags->h = false;
    flags->i = false;
    flags->n = false;
    flags->p = false;
    flags->one = false;
    flags->F = false;
    flags->C = false;
    flags->color = false;
}

static void flags_get(t_flags *flags, char *str) {
    for (int i = 1; str[i] != '\0'; i++) {
        switch (str[i]) {
            case 'R':
                flags->R = true;
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
                flags->U = true;
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
            case 'g':
                flags->g = true;
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
            case 'F':
                flags->F = true;
                break;
            case 'C':
                flags->C = true;
                break;
            default:
                mx_invalid_flag(str[i]);
                break;
        }
    }
}

static void get_files_names(int argc, char **argv, t_uls *data) {
    data->files = (char **)malloc(sizeof(char *) * (data->files_num ) + 10);
    int k = 0;
    int count = 0;

    for (int i = 0; i < data->files_num; i++) {
            data->files[k++] = mx_strdup(argv[data->indexes_of_files[count++]]);
    }
        //terminate array with NULL-string
    data->files[k] = NULL;
}

void mx_parse_argc(int argc, char **argv, t_uls *data, t_flags *flags) {
    flags_init(flags);
    bool tmp = false;
    data->files_num = 0;
    data->argcf = 0;
    int arg_so_far = 1;
    data->indexes_of_files = (int *)malloc(sizeof(int *));//allocating a memory for an array for storing
                                                        //indexes of right files
    int k = 0; 

    for (; arg_so_far < argc; arg_so_far++) {
        if (argv[arg_so_far][0] == '-' && tmp == false) {
            if (mx_strcmp(argv[arg_so_far], "--color") == 0)
                flags->color = true;
            else
                flags_get(flags, argv[arg_so_far]);
            data->argcf++;
        }    
        else {
            if (mx_check_file(argv[arg_so_far])) {
                data->indexes_of_files[k++] = arg_so_far;
                data->files_num++;
                tmp = true;
            }
            else {
                write(2, "uls: ", mx_strlen("uls: "));
                perror(argv[arg_so_far]);
                // mx_invalid_file(argv[arg_so_far]);
                tmp = true;
            }
        }   
    }
    get_files_names(argc, argv, data);
}
