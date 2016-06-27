#Searching and extracting data from files#

##Commands Revisited##

Searching and extracting data from files.

Some example commands:
1. `find . -name "f?le*" -type f`

2. `grep [OPTION]... PATTERN  [FILE]...`
3. `grep DHCP $(find /var/log/ -type f)`
4. `grep -in dhcp $(find /var/log/ -type f)`
  1. `-i` -> case insensitive
  2. `-n` -> get the line number
5. `sort sort.txt`
  1. `-r` -> reverse
  2. `-k` -> sort by key (or column). Example `sort k2 sort.txt` -> Sort sort.txt with the second column
  3. `n` -> numerical
6. `cut` -> print selected part of a line
  1. `-c5-9 file.txt` -> return character 5-9
  2. `cut -c2,4,6 file.txt` -> return  the 2, 4 and 6th char  
  3. `cut -d" " -f2 file1.txt` -> cut where there is a space and give me the second field per line. (space is the delimiter)
  4. `cut -d" " -f2-5 file1.txt` -> give me the fields 2-5
  5. `4. `cut -d" " -f2- file1.txt` -> give me the fields from field 2
7. `wc` -> word count

##Command Line Pipes##

File descriptors:
0. stdin -> standard input(0)
1. stdout -> standard output(1)
2. stderr -> standard error(2)

INPUT(stdin 0) --------->COMMAND-------------->OUTPUT(stdout 1)
                                       |
                                       |
                                       |
                                 ERROR(stderr 2)

Piping vi `|` -> Make stdout of one command the stdin of the next command

1. `find . -type f | grep 1.txt`
2. `cut -d" " -f 3 file6.txt | cut -c2` -> from field 3 of everyline, get the second column (which is a character)
3. `wc -w file6.txt | cut -d" "  -f1` -> only get the word count and don't get the filename which word count normally gives you

