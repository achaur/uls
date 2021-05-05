# uls
Recode the system's utility ls.

Ideas for speedup: use less mallocs

FIX ERRORS: WHEN THERE IS NO VALIND ARGUMENTS AT ALL, EXIT
NOW: IF THERE IS NO VALID ARGUMENTS - IN PRINTS DEFAULT DIRECTORY

To-do for minimal version:
 - free memory//done
 - proper error handling//done
 - if output is piped, use -1 as default instead of -C +
 - read links properly +
 - calculate size for -l flag +
 - print files itself if they are arguments +

 To-do for creative version:
 - recursive output
 - sort by name
 - recursive sorting
 - additional sorting flags
 - add -d flag (list directory itself)
 - add -m flag (print all files as comma-separated)
 - add -o flag (like l+G)
 - add -x flag (list by lines instead of columns) (may be hard)
 - add colourful output
 - help and version flags

