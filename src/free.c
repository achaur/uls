#include "uls.h"

//recursively frees tree structure
void mx_free_dir(t_file *dir) {
    while (dir != NULL) {
        if (dir->name != NULL)
            mx_strdel(&(dir->name));
        if (dir->path != NULL)
            mx_strdel(&(dir->path)); 
    if (dir->level != NULL)
        mx_free_dir(dir->level);
    t_file *temp = dir->next;
    free(dir);
    dir = temp;
    }
    dir = NULL;
}

//frees table for print
void mx_free_table(t_table *table) {
    free(table->max_col_size);
    table->max_col_size = NULL;

    for (int row = 0; row < table->rows; row++) {
        for (int col = 0; col < table->cols; col++) {
            free(table->table[row][col]);
            table->table[row][col] = NULL;
        }
        free(table->table[row]);
        table->table[row] = NULL;
    }

    free(table->table);
    table->table = NULL;

    free(table);
    table = NULL;
}

void mx_clean_memory(t_uls *data, t_flags *flags) {
    if (data->files)
        mx_del_strarr(&data->files);
    if (data->indexes_of_files) {
        free(data->indexes_of_files);
        data->indexes_of_files = NULL;
    }
    free(data);
    data = NULL;
    free(flags);
    flags = NULL;
}
