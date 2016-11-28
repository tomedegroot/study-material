#wc, split, cat, and diff commands

##cat
`cat FILE [FILES..]`

###heredoc

Read from STDIN until a certain word is found:

`cat << KEYWORD` -> read from STDIN until KEYWORD is found 

##wc

count -> `wc`

1. lines -> `-l`
2. chars -> `-m`
3. words -> `-w`

##split

Split a file (or stdin with piping).
The output will be files with names: xaa, xab, xac... if those filenames already exist, they will be overwritten.

`split [OPTIONS] [FILE] [FILESPREFIX]`

1. `-l` -> number of lines per output file. So if you have a file of 6 and you want to split it in 2 files, do `-l 3`

If [FILEPREFIX] is specified, all the newly created files will start with the prefix, example:

`split -l 20 /var/log/dmesg lines` will create files linesaa, linesab, linesac, etc

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

##Extra:

`wget` -> download from the web
 1. `O` -> specify the output file. Use `-` for STDOUT

##Options

###Matcher Options:

1. `-E` -> use extended regex, defined by POSIX (=egrep)
2. `-F` -> fixed string; search for exact match of string(=fgrep)

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

1. `^` -> beginning
2. `$` -> end
3. `[hpok]` -> all the lines with h, p, o or k in it
  1. `[A-Z]` -> Character or number ranges
  2. `[^]` -> Negate what is in the square brackets
4. `.` -> any character
5. `\` -> escape character, so `\$`, `\[` or `\\` for example

##egrep

Use egrep via `grep -e`. More options are possible with egrep.

(negative lookahead)[http://stackoverflow.com/a/977294] is (not supported by grep)[http://stackoverflow.com/questions/9197814/regex-lookahead-for-not-followed-by-in-grep]. But there is a workaround for some cases: pipe the output to grep -v, as in:

`egrep 'hello|world' testf | grep -v 'jeff'`

##REGEX Pipe (= or, or both)

1. `hello|world` -> OR, look for a line that contains hello OR  world
2. `(W|w)orld` -> OR within group, so World or world.

##Quantifiers

It's possible to quantify brackets[]:

1. `?` -> zero or more
2. `+` -> once or more
3. `*` -> any number of times
4. `{2}` -> exactly 2 times

##fgrep

Use as egrep -F, which is interpret the string literally. So the ^, $ and [ for example will be intrepreted literally

##Examples:

1. `wget -O- http://www.nu.nl | grep -E 'href=".*economie.*\.html"'`

#cut

Print selected lines of files:

`cut FIELD TYPE [OPTIONS] [FILE]` or STDIN

Field types:
  1. `-fN` -> set fields as field type, so: `cut -d: -f1,4-6 /etc/passwd`
    2. `-d` -> set delimiter for the field, so `-d:` sets ':' as delimiter. The default is TAB
  2. `-cN` -> set characters as field types, so: `cut -c1-5 /etc/passwd` gives you the first 5 characters of every line of /etc/passwd

##example

`cut -f2 -d ' ' test.txt` -> set space as the delimeter

#sed

Stream editor for filtering and transforming text

`sed [OPTIONS] [SCRIPT] [INPUTFILE]`

A script can consist of multiple commands. If no special option is set, the first non-option character is seen as the start of the script.

##commands

Commands form the sed script.

`sed 's/regexp/replacement/'` -> search and replace

`sed 's/regexp/replacement/w changes.txt'` -> save only the changed lines to changes.txt

We don't have to search and replace, we can just search and write:

`sed 's/regexp/replacement/w fulltime.txt'` -> example: `sed '/fulltime/w fulltime.txt'`, no we have a file with all fulltime employees

`sed '0,/parttime/s/parttime/promotion/'` -> search for the first line with occurence of parttime, search within that line for parttime and replace it with promotion

##example

Replace all html tags with nothing(so strip the html tags):

`sed 's/<[^>]*>//' team`, search for any occurence of a <, continue to match for any character except > until you find the > and match that one and replace it with nothing.

@todo Do a sed tutorial

#tee

Allows to read from STDIN and **output to STDOUT and FILE**

`... | tee [OPTIONS] FILES` -> send output to both STDOUT and FILES
  1. `-a` -> append to the file instead of overwriting

##example
1. `ls | tee file1 file2` -> send ls output to both STDOUT and file1 and file2
2. `ls f* | wc -l | tee count.txt` -> count the number of files starting with f and output to both STDOUT and count.txt
3. `ls /var/log/ | tee copy{1..3}` -> output content of /var/log to STDOUT and save to copy1, copy2 AND copy 3
