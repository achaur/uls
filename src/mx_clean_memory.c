#include "uls.h"

void mx_clean_memory(t_uls *data) {
    if (data->files)
        mx_del_strarr(&data->files);
    if (data->name)
        free(data->name);
    if (data->indexes_of_files)
        free(data->indexes_of_files);
}
