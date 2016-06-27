#Commands Revisited#

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
