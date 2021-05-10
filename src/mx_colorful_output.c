#include "uls.h"

// static void print_dir(t_file *file) {
//     if ((file->filestat.st_mode & MX_IWOTH) == MX_IWOTH
//         && (file->filestat.st_mode & MX_ISVTX) == MX_ISVTX)
//         mx_printstr(DIR_T);
//     else if ((file->filestat.st_mode & MX_IWOTH) == MX_IWOTH
//              && (file->filestat.st_mode & MX_IXOTH) == MX_IXOTH)
//         mx_printstr(DIR_X);
//     else
//         mx_printstr(BLU);
// }

// static void print_reg_file(t_file *file) {
//     if ((file->filestat.st_mode & MX_ISUID) == MX_ISUID)
//         mx_printstr(BLK_F_RED_B );
//     else if ((file->filestat.st_mode & MX_ISGID) == MX_ISGID)
//         mx_printstr(BLK_F_CYAN_B);
//     else if ((file->filestat.st_mode & MX_IXUSR) == MX_IXUSR)
//         mx_printstr(RED);
//     else
//         mx_printstr(RESET);
// }

// char *mx_colorful_output(t_file *file, t_flags *flags) {
//     if (flags->color) {
//         if ((file->filestat.st_mode & MX_IFIFO) == MX_IFIFO)
//             mx_printstr(YEL);
//         else if ((file->filestat.st_mode & MX_IFCHR) == MX_IFCHR)
//             mx_printstr(CHR);
//         else if ((file->filestat.st_mode & MX_IFDIR) == MX_IFDIR)
//             print_dir(file);
//         else if ((file->filestat.st_mode & MX_IFBLK) == MX_IFBLK)
//             mx_printstr(BLOCK);
//         else if ((file->filestat.st_mode & MX_IFREG) == MX_IFREG)
//             print_reg_file(file);
//         else if ((file->filestat.st_mode & MX_IFLNK) == MX_IFLNK)
//             mx_printstr(MAG);
//         else if ((file->filestat.st_mode & MX_IFSOCK) == MX_IFSOCK)
//             mx_printstr(GRN);
//         // mx_printstr(file->name);
//         // mx_printstr(RESET);
//     }
//     return file->name;
// }

