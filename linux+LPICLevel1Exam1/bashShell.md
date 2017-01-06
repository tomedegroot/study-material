#Simple Commands & Shortcuts For The Linux Shell

##pwd

Print the local working directory

##time

How to measure execution of a command? -> `time COMMAND`

##shortcuts tom $HOME

1. `cd`
2. `cd ~`
3. `cd $HOME`

##exit shell after executing a program

How to exit shell after executing a program? -> `exec PROGRAM`

the exec command replaces the shell process, thus when the program terminates it terminates the shell.

##history

stored in ~/.bash_history

cycle through commands: `up arrow`

search the history: `crtl+r`
next entry: `crtl+r`

cancel search and return original entry: `crtl+g`

##shortcuts

end of line: `crtl+e`
beginning of line: `crtl+a`

remove till beginning of line: `crtl+u` or `crlt+x` and then `backspace`
remove till end of line: `crtl+k`
remove word: `crtl+w`
remove char: `crtl+d`

paste removed material: `crtl+y`; **different from vim**

transpose a char: `crtl+t`

##bash configuration

to make an environment variable persistent (so use it again after the current session) alter either the

1. *~/bash_profile* file -> persistent for one use.
2. */etc/profile* or */etc/profile.d* -> persistent for all users.

```
bash as login shell will load /etc/profile, ~/.bash_profile, ~/.bash_login, ~/.profile in the order

bash as non-login interactive shell will load ~/.bashrc
```

#environment variables, redirection operators & data pipes

##export

how to make a variable available to all sub-processes? -> `export key=value`. ***key without the $ sign**

this way all child processes can access the variable, that is every program started from this session will have the variable.

##environment variables

`env` -> get all the environment variables

##redirection operators

##i/o redirection

command > filenameoranothercommand -> shorthand for command 1> fileoranothercommand 

1. `tail /var/log/messages > logtemp.txt` -> stdout is redirected to the file (so it is not on the screen). 
2. `cat nonexistentfile.txt 2> myerrors.txt` -> stderr is redirected to myerrors.txt 
3. `>>` -> append file descriptor 
4. `cat nonexistentfile.txt 2>> myerrors.txt` -> stderr is appended to myerrors.txt 
5. `command 1> file1 2> file2` -> stdout to file1 and stderr to file2 example: mount 1> mountfile 2> mounterror
6. `command `2&1` -> redirect stderr to the same direction as stdin
7. `command &> file` -> write to file for stdin and stderr
8. `command < stdin` -> redirect stdin as input to a command
9. `command1 | command2` -> stdout of command1 is stdin of command2

#Manipulating files

##xargs

Build command lines from STDIN. From the man:

```
xargs reads items from the standard input, delimited by blanks (which can be protected with double or single quotes or  a  backslash)  or  newlines, and executes the command (default is /bin/echo) one or more times with any initial-arguments followed by items read from standard input.
```

So great for commands such as rm, ls and others who DO NOT read from STDIN

Examples:
1. `ls variable.txt | xargs cat`
2. From man:

```
find /tmp -name core -type f -print0 | xargs -0 /bin/rm -f

       Find files named core in or below the directory /tmp and delete them, processing filenames in such a way that file or directory names containing spaces or  newlines  are
       correctly handled.
```

Explanation: `find -print0` prints the filename, terminated with a 0. xargs -0 lets xargs interprets items as terminated by a 0 character

##sort

`sort [options]`

1. `-r` -> reverse
2. `-n` -> numerical
3. `-k` -> sort by key (or column).
  1. `-k2` -> sort by field 2 **nothing -> field number**
  2. `-k2,4` -> sort by field 2 and end with field 4. **comma -> range of fields**
  3. `-k fieldnumber[.charnumber]` -> set key to sort on to a certain field and char within that field. all defaults to 1. **dot -> field.column**
  4. example: `last | sort -k5m -k6n` -> sort monthly by the 5th field first and then numerical by the 6th field

##cat

Purpose: concatenate files and print to STDOUT

`cat [FILE...]`

##uniq

`uniq`

Omit repeated lines. Example:

```
[tom@t-degroot1 ~]$ echo -e "5\n1\n5\n4" | sort -n | uniq
1
4
5
```

##echo

Echo out files. `-e` allows interpretation of backslash escapes.

Example:

```
[tom@t-degroot1 ~]$ echo -e '5\n1'
5
1
```

##nl

`nl [FILE]`

Get the line numbers per line

##fmt

Simple formatter to make stuff look nice. Nice for printing on paper

##split

Split file into multiple files. Example:

```
[tom@t-degroot1 ~]$ split -l 2 test1 splitted
[tom@t-degroot1 ~]$ ls splitted*
splittedaa  splittedab  splittedac  splittedad  splittedae  splittedaf
```

Command structure:

`split [OPTIONS] FILETOSPLIT PREFIXFORNEWFILENAMES`

OPTIONS:
1. `-l n` -> split per 2 lines, so every new file has 2 lines (and the last one has 1 line if the origin file has an odd number of lines)

##paste

`paste [FILE...]`

Paste line by line for multiple files:

```
[tom@t-degroot1 ~]$ echo "bla hello world" > test1
[tom@t-degroot1 ~]$ echo "bla how are you today" > test2
[tom@t-degroot1 ~]$ past test1 test2
bla hello world bla how are you today
```

##join

`join [OPTIONS] FILE1 FILE2`

Join two files. Example:

```
[tom@t-degroot1 ~]$ echo "bla" > test1
[tom@t-degroot1 ~]$ echo "bla how are you today" > test2
[tom@t-degroot1 ~]$ join test1 test2
bla how are you today
```

It works like cat, but prit the join field only one.

OPTIONS:
1. `-1 FIELD -2 FIELD` -> specify on which fields to join for file 1 and file2


##expand and unexpand

`expand [FILE...]` -> convert tabs to spaces

`unexpand [FILE...]` -> convert spaces to tabs

So expand expands the file filesize, but not the visual size of text

##tr

`tr [OPTIONS] SET1 SET2` -> translate any char in set1 for the **first char** in set2

Example:

```
[tom@t-degroot1 ~]$ cat test1 
bla hello world
[tom@t-degroot1 ~]$ tr hello test < test1 
bta tettt wtrtd
```

@todo no important for test, but why would a person want to use this?


