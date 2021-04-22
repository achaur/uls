#include "uls.h"

void mx_invalid_file (char *argv) {
    mx_printerr("uls: ");
    mx_printerr(argv);
    mx_printerr(": No such file or directory\n");
    // errno = 1;
    // exit(1);
}   
