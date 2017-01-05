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

The exec command replaces the shell process, thus when the program terminates it terminates the shell.

##history

Stored in ~/.bash_history

Cycle through commands: `UP ARROW`

Search the history: `CRTL+R`
Next entry: `CRTL+R`

Cancel search and return original entry: `CRTL+G`

##shortcuts

End of line: `CRTL+E`
Beginning of line: `CRTL+A`

Remove till beginning of line: `CRTL+U` or `CRLT+X` and then `BACKSPACE`
Remove till end of line: `CRTL+K`
Remove word: `CRTL+W`
Remove char: `CRTL+D`

Paste removed material: `CRTL+Y`; **different from VIM**

Transpose a char: `CRTL+T`

##Bash configuration

To make an environment variable persistent (so use it again after the current session) alter either the

1. *~/bash_profile* file -> persistent for one use.
2. */etc/profile* or */etc/profile.d* -> persistent for all users.

```
Bash as login shell will load /etc/profile, ~/.bash_profile, ~/.bash_login, ~/.profile in the order

Bash as non-login interactive shell will load ~/.bashrc
```

#Environment Variables, Redirection Operators & Data Pipes

##export

How to make a variable available to all sub-processes? -> `export key=value`. ***key without the $ sign**

This way all child processes can access the variable, that is every program started from this session will have the variable.

##environment variables

`env` -> get all the environment variables

##Redirection operators

##sort

`sort [OPTIONS]`

1. `-r` -> reverse
2. `-n` -> numerical
3. `-k` -> sort by key (or column).
  1. `-k2` -> sort by field 2 **nothing -> field number**
  2. `-k2,4` -> sort by field 2 and end with field 4. **comma -> range of fields**
  3. `-k FIELDNUMBER[.CHARNUMBER]` -> set key to sort on to a certain field and char within that field. All defaults to 1. **dot -> field.column**
  4. Example: `last | sort -k5M -k6n` -> sort monthly by the 5th field first and then numerical by the 6th field

##I/O Redirection

COMMAND > FILENAMEORANOTHERCOMMAND -> shorthand for COMMAND 1> FILEORANOTHERCOMMAND 

1. `tail /var/log/messages > logtemp.txt` -> stdout is redirected to the file (so it is not on the screen). 
2. `cat nonexistentfile.txt 2> myerrors.txt` -> stderr is redirected to myerrors.txt 
3. `>>` -> append file descriptor 
4. `cat nonexistentfile.txt 2>> myerrors.txt` -> stderr is appended to myerrors.txt 
5. `COMMAND 1> file1 2> file2` -> stdout to file1 and stderr to file2 example: mount 1> mountfile 2> mounterror
6. `COMMAND `2&1` -> redirect stderr to the same direction as STDIN
7. `COMMAND &> file` -> write to file for STDIN and STDERR
8. `COMMAND < stdin` -> redirect stdin as input to a command
9. `COMMAND1 | COMMAND2` -> STDOUT of COMMAND1 is STDIN of COMMAND2


##xargs

Build command lines from STDIN. From the man:

```
xargs reads items from the standard input, delimited by blanks (which can be protected with double or single quotes or  a  backslash)  or  newlines, and executes the command (default is /bin/echo) one or more times with any initial-arguments followed by items read from standard input.
```

Examples:
1. `ls variable.txt | xargs cat`
2. From man:

```
find /tmp -name core -type f -print0 | xargs -0 /bin/rm -f

       Find files named core in or below the directory /tmp and delete them, processing filenames in such a way that file or directory names containing spaces or  newlines  are
       correctly handled.
```

Explanation: `find -print0` prints the filename, terminated with a 0. xargs -0 lets xargs interprets items as terminated by a 0 character
