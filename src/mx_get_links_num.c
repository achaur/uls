#include "uls.h"

char *mx_get_links_num(char *file_name) {
    struct stat st;

    stat(file_name, &st);
    struct passwd *pwd = getpwuid(st.st_uid);
    struct group *grp = getgrgid(pwd->pw_gid);
    printf("%s\n", mx_itoa(st.st_nlink));
    printf("%s\n", mx_itoa(st.st_uid));
    printf("%s\n", pwd->pw_name);
    printf("%s\n", mx_itoa(pwd->pw_gid));
    printf("%s\n", grp->gr_name);

    

    return "1";
    
}
