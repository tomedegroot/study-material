#File Naming Basics And Look A Look At File Commands

##Case sensitivity

File names and file extensions are case sensitive

##Spaces

Space are interpreted by the shell. So if you want to create a file name with space, there are two ways:

1. `vi 'this file has spaces'` (quotes)
2. `vi this\ file\ has\ spaces` (escaping)

##File names limit:

1. EXT: 255 chars

##Files starting with a .

These hidden files, used for configuration. They are excluded from the view with a basic ls command (use the `-a` flag)

##File Globbing in Bash

1. What is the wild card for 1 symbol? -> `?` -> `ls bo?k` will get book
2. What is the wild card for 0,1 or multiple symbols? -> `*` -> `ls b*k` will get book
3. How can a range be expressed **with reference** to the file names? -> `ls b[oa]k` -> means 'bok' or 'bak', bash can only expand if it finds the filenames
4. How can a range be expressed without reference to the file names? Use `{}`, so:
  1. `touch {a,b,c}` -> expands to a,b and c
  2. `touch {a..d}` -> expands to a,b,c and d
  3. `touch {ed,ld}*` -> expand to everything that starts with either 'ed' or 'ld'

**Since there (must be a reference to a file names){http://tomecat.com/jeffy/tttt/glob.html} for square brackets ([]) to work, touching files which are non existent will not work with square brackets, you need to use the curly brackets for that.**

**Globbing is sometimes work the same as REGEX, but they are not the same.**

##ls

ls lists, options:

1. `-a` -> all, including . files
2. `-d` -> only show directories
3. `-f` -> append indicator (one of */=>@|) to entries. So you can easily see it is a dir or socket for example
  1. `/` -> dir
  2. `@` -> symbolic link
4. `-R` -> recursive

##cp

`cp [OPTIONS] SOURCE DESTINATION`
  1. `-i` -> interactive, prompt before overwrite
  2. `-p` -> preserve permissions. By default, if you copy a file it gets the same permissions and owner as the folder you are copying to. With `-p` you keep the same permissions and owner as the original file

