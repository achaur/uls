#include "uls.h"

int main(int argc, char **argv) {
    printf("Hello uls!\n");

        //allocate struct for data and flags
    t_uls *data = (t_uls *)malloc(sizeof(t_uls));
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));

        //parse arguments
    mx_parse_argc(argc, argv, data, flags);

            //print out file arguments
    printf("\tArguments:\n");
    for (int i = 0; i < data->files_num; i++)
        printf("%s\n", data->files[i]);

        //scan directories recursively
    char *path = mx_strdup(argv[1]);
    t_file *fist = NULL;
    fist = mx_scan_dir(path);

    /*---DEMO PRINT ---*/

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
