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
    for (int i = 0; data->files[i] != NULL; i++)
        printf("%s\n", data->files[i]);

        //read file tree
    t_file *tree = mx_get_tree(data->files, flags);

    tree = tree->level;
    // int res = mx_get_filesnum(tree);

    // printf("Number of files: %d\n", res);
    // mx_get_cols(tree);
    // int total = 11, cols = 3;
    // int rows = mx_get_rows(cols, total);

    // printf("Total files: %d, rows: %d, cols: %d\n", total, rows, cols);

    printf("================\n");

    int cols = mx_get_cols(tree);

    printf("\nFINAL AMOUNT OF COLUMNS: %d\n", cols);
    //test what is it tree struct
    // tree = tree->level;
    // while (tree != NULL) {
    //     printf("Node name: %s\n", tree->name);
    //     printf("Node path: %s\n", tree->path);
    //     printf("Node level: %p\n\n", tree->level);
    //     tree = tree->next;
    // }

    /*---DEMO PRINT ---*/

    // //try to fill and print table
    // t_table *table = mx_allocate_table(3,3);

    // //fill 2-D string array table[row][col]
    // table->table[0][0] = mx_strdup("a");
    // table->table[1][0] = mx_strdup("b");
    // table->table[2][0] = mx_strdup("c");
    // table->table[0][1] = mx_strdup("qwertysdvsdv");
    // table->table[1][1] = mx_strdup("asdfg");
    // table->table[2][1] = mx_strdup("zxcvb");
    // table->table[0][2] = mx_strdup("tyu");
    // table->table[1][2] = mx_strdup("ghj");
    // table->table[2][2] = mx_strdup("bnm");

    // mx_print_table(table);

    return 0;
}
