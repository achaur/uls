#include "uls.h"

int main(int argc, char **argv) {
printf("Hello uls!\n");

    // char *path = mx_strdup(argv[1]);

    // t_file *fist = NULL;
    // fist = mx_scan_dir(path);

    //try to fill and print table
    t_table *table = malloc(sizeof(t_table));

    table->rows = 3;
    table->cols = 3;

    //allocate 2-D string array
    table->table = malloc(table->rows * sizeof(char**));
    for (int i = 0; i < table->rows; i++) {
        table->table[i] = malloc(table->cols * sizeof(char*));
    }
    //fill 2-D string array
    table->table[0][0] = mx_strdup("one");
    table->table[0][1] = mx_strdup("two");
    table->table[0][2] = mx_strdup("three");
    table->table[1][0] = mx_strdup("four");
    table->table[1][1] = mx_strdup("five");
    table->table[1][2] = mx_strdup("six");
    table->table[2][0] = mx_strdup("seven");
    table->table[2][1] = mx_strdup("eight");
    table->table[2][2] = mx_strdup("nine");

    mx_print_table(table);
    

    return 0;
}
