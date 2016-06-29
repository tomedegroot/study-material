#Turning commands into a Scripts/VI#

##Nano###
1. `CTRL+K` -> Cut line
2. `CTRL+O` -> Save file
3. `CTRL+U` -> Uncut text

##Vi##

Diifferent modes (is in the bottom line):

1. Normal mode -> after opening a file
2. Insert mode -> edit the text file.`i`,`INSERT`,`s`,`o`, or `a`
3. Command **line** mode via `:` -> Enter commands
  1. `w [nameOfFile]` -> write out to file that was opened or to [nameOfFile]
  2. `q` -> quit
  3. `!` -> several meanings:
     1. It forces a command, such as `:q!` to force quiting even though changes have not been saved
     2. It work as a toggle for certain commands, so `:set cursorline` `:set nocursorline` to `:set cursorline!`
  4. `:noh` -> remove highlight (e.g. after search)
  5. `:set number` -> line numbers
  6. `:scriptnames` -> get all the .vim files that Vim loaded, including .vimrc (Add user settings to *$HOME/vimrc*)
4. Command mode, default mode to quickly navigate via shortkeys:
 
Deleting:
   
  1. `dw` -> delete word after cursor **and the space after the word**
  2. `de` -> delete word after cursor
  3. `dd` -> delete entire line
 
Yanking(copying):
 
  1. `yw` -> yank (copy) entire word *and the space after the word**
  2. `ye` -> yank (copy) entire word
  3. `yy` -> yank (copy) entire line
   
Paste:

  1. `p`  -> paste what was just deleted or yanked

Moving:
   
 1. `/` -> search for a term, this will highlight the term
 2. `w` -> move to next word
 3. `b` -> move to previous word
 4. `nG` -> move to the nth line of file
 5. `G` -> move to last line of file

##Basic Shell Scripting##

Scripts need an interperteter (*/bin/bash*). The script has access to:
1. Variables, e.g. $USER
2. Arguments:
  1. `$1` -> First Argument
  2. `$2` -> Second Argument
  3. `$?` -> Exit code/Status of previous statement (0 for success, non-zero for an error)  
  4. `$@` -> Iterate over arguments

Important to know:

1. `#!` -> shebang, what program to run
2. `*/bin/bash* -> Bourne Again Shell`, [advised](http://stackoverflow.com/a/10383546) to use `#! /usr/bin/env bash`. env searches the $PATH to find the application to run the script, so your script becomes more portable.
3. `Variables` -> pass variables or create arguments to pass to scripts
4. `echo` -> print/echo's what tell echo to print to screen
5. `Exit [exitCode]` -> exit and return the exit code

##If conditional:##

```
if *condition*
*then*
	*command*
*fi*
```	

Example of a shell script with *if*:

```
#! /usr/bin/env bash

FLAGLOCATION='flag'

if [ -r $FLAGLOCATION ]; then
  echo 'flag is readable'
else
  echo 'flag is not readable'
fi
```

Options for `test FILE`:

1. `-d` -> dir exists
2. `-e` -> file exists
3. `-f` -> file exists and regular file
4. `-G` -> file exists and owned by group
5. `-h or -L` file exists and is symbolic link
6. `-O` -> file exists and owned by specific UID
7. `-r` -> file exists and is readable
8. `-w` -> file exists and writable
9. `-x` -> file exists and executable

##while##

Example of `while`:
```
while *condition*
*do*
	*command*
*done*
```
##until##
Opposite of while: loop as long as condition is **false**

Example of `until`:
```
until *condition*
*do*
	*command*
*done*
```

##for##
Loop specifc number of times

Structure of `for`:
```
for i in sequence
*do*
        *command*
*done*
```
Three ways of creating a sequence with `seq`:
1. Specify a single value. Sequence starts at 1, increments by 1 and end at specified value.
2. Specify two values. Seq starts at first value, incerements by 1 and end at second value
3. Specify three value. Seq starts at first, increments by second, end at third

*NOTE*: 
1. You have to put `for i in $(seq 5 15)` so the output of the seq command is used in the for construct. Without the command subsitution via $(), you actually create a sequence with 3 values: seq, 5 and 15.
2. You can use backticks instead of $() for command substition. ``for i in `seq 5 15` `` is the same as `for i in $(seq 5 15)`
3. Quickly give owner, group and everyone execute permission via `chmod +x file`. `chmod -x` or `chmod +w` works as well. Remember:  
  1. `1` is bit for execute
  2. `2` is bit for writing
  3. `4` is bit for read
