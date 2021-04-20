#include "uls.h"

static char my_bubble_sort(char **arr, int size) {
    for (int i = 0; i < size - 1; i++)  
        for (int j = 0; j < size - i - 1; j++)
            if (strcmp(arr[j], arr[j + 1]) > 0){
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
    return (char) arr;
}

void mx_one_flag(int argc, char *argv[]) {
    struct stat st;
    DIR* pDir;
    struct dirent* pCurDir;
    char **d_names = (char **)malloc(sizeof(char *) * 9);
    int i = 0;
    int count = 0;
    
    if( ( pDir = opendir(".")) == NULL ){
        perror("read dir");
        exit(-1);
    } else {
        while((pCurDir = readdir(pDir)) != NULL) {
            if (pCurDir->d_name[0] != '.' &&
                    mx_strcmp(pCurDir->d_name, "..") != 0
                    && mx_strcmp(pCurDir->d_name, ".") != 0) {
                d_names[i] = (char *)malloc(sizeof(char) * strlen(pCurDir->d_name) + 1);
                strcpy(d_names[i], pCurDir->d_name);
                i++;
                count++;
            }
        }
    }
    my_bubble_sort(d_names, count);
    for (int i = 0; i < count; i++) {
        printf("%s %c", d_names[i], ' ');
    }
    printf("%c", '\n');
    for (int i = 0; i < count; i++) {
        free(d_names[i]);
    }
    free(d_names);
}
