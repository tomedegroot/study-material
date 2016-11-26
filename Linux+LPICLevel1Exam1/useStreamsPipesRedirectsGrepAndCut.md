#wc, split, cat, and diff commands

##cat
`cat FILE [FILES..]`

##wc

count -> `wc`

1. lines -> `-l`
2. chars -> `-m`
3. words -> `-w`

##split

Split a file (or stdin with piping).
The output will be files with names: xaa, xab, xac... if those filenames already exist, they will be overwritten.

`split [OPTIONS] [FILE]`

1. `-l` -> number of lines per output file. So if you have a file of 6 and you want to split it in 2 files, do `-l 3`

## diff

See the difference between files

`diff FILE1 FILE2`

A `<` in the output means the line exists in FILE1, but not in FILE2
A `>` in the output means the line exists in FILE2, not not in FILE1

#Streams (stdin, stdout, stderr) and Redirects

##3 streams:

stdin(0)  -> what you input on the command line
stdout(1) -> what you see on the screen
stderr(2) -> error on the screen

##Redirects:
1. `>`  -> redirect the stdout, ex: `echo "test" > file.txt`
2. `>>` -> append the stdout (create if destination doesn't exist), ex: `echo "test" >> file.txt`
3. `<`  -> redirect stdin (get the stdin from something else than the terminal), ex: `wc -w < newfile`
4. `|` -> piping, use the stdout of one command as the stdin of another, example: `cat < newfile | grep -w`

##stderr:

1. `2>error.log` -> redirect stderr to test file
2. `2>/dev/null` -> redirect error to the bitbucket (nothing)

##Combination

1.stdin and stderr in 2 files: `cat xaa xab nofile > mystdoutput 2>mystderror`
2. combine stdin and stderr in 1 file: `cat xaa xab nofile > mystdoutput 2>&1`

##Prevent overwriting of specific files

noclobber, makes sure you cannot overwrite an existing file with a redirect if the noclobber option is turned on

`set -o noclobber` -> turn noclobber ON
`set +o noclobber` -> turn noclobber OFF

#Pipes

`|` use stdout as stdin for another command, example:

`ls /etc/ | grep cron`

Combining:

`ls /etc/ | grep cron | grep daily > output.txt`

#Grep

Search input files or stdin for a match of a pattern -> `GREP [OPTIONS] PATTERN [FILE]`

##Options

###Matcher Options:

1. `-E` -> use extended regex, defined by POSIXs
2. `-F` -> fixed string; search for exact match of string

###Matching Control Options:

1. `-i` -> Ignore case
2. `-f` -> Read the pattern to use from a file
3. `-v` -> Inverted matching, match anything that does **not** match with the pattern

###Output Control Options:

1. `-c` -> count the lines of occurences
2. `-l` -> list the file names with matches
3. `-L` -> list files **without** matches

###File and dir selection

Grep searches inside the files to see if it can match the pattern. Very useful with the `-l` output options to see where we stored something.

1. `-r` -> recursive, search a dir recursively

##REGEX

(negative lookahead)[http://stackoverflow.com/a/977294] is (not supported by grep)[http://stackoverflow.com/questions/9197814/regex-lookahead-for-not-followed-by-in-grep]

###General

1. `^` -> beginning
2. `$` -> end
3. `[hpok]` -> all the lines with h, p, o or k in it
  1. `[A-Z]` -> Character or number ranges
  2. `[^]` -> Negate what is in the square brackets
4. `.` -> any character

###Quantifiers

It's possible to quantify brackets[]:

1. `?` -> zero or more
2. `+` -> once or more
3. `*` -> any number of times

7.49
