#include "uls.h"

int main(int argc, char **argv) {
printf("Hello uls!\n");

    // char *path = mx_strdup(argv[1]);

    // t_file *fist = NULL;
    // fist = mx_scan_dir(path);

    //try to fill and print table
    t_table *table = mx_allocate_table(3,3);

    //fill 2-D string array table[row][col]
    table->table[0][0] = mx_strdup("a");
    table->table[1][0] = mx_strdup("b");
    table->table[2][0] = mx_strdup("c");
    table->table[0][1] = mx_strdup("qwertysdvsdv");
    table->table[1][1] = mx_strdup("asdfg");
    table->table[2][1] = mx_strdup("zxcvb");
    table->table[0][2] = mx_strdup("tyu");
    table->table[1][2] = mx_strdup("ghj");
    table->table[2][2] = mx_strdup("bnm");


    mx_print_table(table);

    return 0;
}
