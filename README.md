# uls
Recode the system's utility ls.

Flags description:

-a: do not ignore entries starting with .
-A: do not list implied . and ..
-l: use a long listing format
-1: list one file per line.
-R: list subdirectories recursively
-C: list entries by columns

-S: sort by file size, largest first
-t: sort by modification time, newest first
-u: with -lt: sort by, and show, access time; with -l:  show  access
              time  and  sort  by name; otherwise: sort by access time, newest
              first
-c: with -lt: sort by, and show, ctime (time of last modification of
              file status information); with -l: show ctime and sort by  name;
              otherwise: sort by ctime, newest first
-U: do not sort; list entries in directory order

-G: in a long listing, don't print group names
-g: like -l, but do not list owner
-h: with -l and -s, print sizes like 1K 234M 2G etc.
-i: print the index number of each file
-n: like -l, but list numeric user and group IDs
-p: append / indicator to directories
-F: append indicator (one of */=>@|) to entries
--color: colorize the output
