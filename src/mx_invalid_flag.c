#include "uls.h"

void mx_invalid_flag(char c) {
    mx_printerr("uls: illegal option -- ");
    write(2, &c, 1);
    mx_printerr("\nusage: uls [-l] [file ...]\n");
    exit(1);
}
