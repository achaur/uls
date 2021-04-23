#include "uls.h"

int main(int argc, char **argv) {
printf("Hello uls!\n");

    char *path = mx_strdup(argv[1]);

    t_file *fist = NULL;
    fist = mx_scan_dir(path);

    return 0;
}
