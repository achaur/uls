#include "uls.h"

char *mx_get_size(t_file *fist, t_flags *flags) {
    stat(fist->name, &fist->filestat);

    if (flags->l && !flags->h)
        return mx_itoa(fist->filestat.st_size);
    else if (flags->l && flags->h) {
        if (fist->filestat.st_size < 1000) 
            // return mx_itoa(fist->filestat.st_size); Ubuntu ls -lh dispay
            return mx_strjoin(mx_itoa(fist->filestat.st_size), "B");//macos ls-lh display
        else if (999 < fist->filestat.st_size && fist->filestat.st_size < 1000000) 
            return mx_strjoin(mx_strjoin(mx_strjoin(mx_itoa(fist->filestat.st_size / 1000), "."), mx_itoa(fist->filestat.st_size % 1000)), "K");
        else if (999999 < fist->filestat.st_size && fist->filestat.st_size < 1000000000)
            return mx_strjoin(mx_strjoin(mx_strjoin(mx_itoa(fist->filestat.st_size / 1000000), "."), mx_itoa(fist->filestat.st_size % 1000000)), "M");
        else if (999999999 < fist->filestat.st_size && fist->filestat.st_size < 1000000000000)
            return mx_strjoin(mx_strjoin(mx_strjoin(mx_itoa(fist->filestat.st_size / 1000000000), "."), mx_itoa(fist->filestat.st_size % 1000000000)), "G");
        else if (999999999999 < fist->filestat.st_size && fist->filestat.st_size < 1000000000000000)
            return mx_strjoin(mx_strjoin(mx_strjoin(mx_itoa(fist->filestat.st_size / 1000000000000), "."), mx_itoa(fist->filestat.st_size % 1000000000000)), "T");
    }
    return NULL;
}
