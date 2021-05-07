#include "libmx.h"

int mx_strcicmp(const char *s1, const char *s2) {
    while ((*s1 != '\0') || (*s2 != '\0')) {
        if (mx_tolower(*s1) != mx_tolower(*s2))
            return mx_tolower(*s1) - mx_tolower(*s2);
        s1++;
        s2++;
    }
    return 0;
}
