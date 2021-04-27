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

    //test what is it tree struct
    // tree = tree->level;
    // while (tree != NULL) {
    //     printf("Node name: %s\n", tree->name);
    //     printf("Node path: %s\n", tree->path);
    //     printf("Node level: %p\n\n", tree->level);
    //     tree = tree->next;
    // }

        /*--- Try to print --- */
        //get rows and cols
    int rows, cols, filesnum;
    mx_get_rows_cols(&rows, &cols, &filesnum, tree, flags);
    // printf("%d columns and %d rows\n", cols, rows);
        //allocate table for them
    t_table *table = mx_allocate_table(rows, cols);
    table->filesnum = filesnum;
        //fill table
    mx_fill_table(table, tree);
        //print table
    mx_print_table(table);
    // printf("\nPrint finished\n");
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
