#Finding Your Way on a Linux System: Command Line Basics#

A shell is a command line interpreter that sends command to the OS kernel.

`echo $SHELL` -> see which shell you are using.
`cat /etc/passwd` -> see which shells users are using.

CRTL + ALT + F2: log into a shell if you are in an x window environment  
ALT+[F2-F6] : open multiple shells  
ALT+F1: Go back to the GUI Environment  

##`ls`##

Options:

* -l -> long; more info
* -p -> appends an indicator (/) to show it is a dir
* -R -> Recursive; show content of a dir

##$PATH##

The interpreter first looks at the working dir and then the $PATH for executables and filenames.

`echo $PATH` -> see your current path.

To add stuff to the $PATH:
`PATH=$PATH:pathToAdd` -> This adds the path as a [local variable](http://unix.stackexchange.com/questions/56444/how-do-i-set-an-environment-variable-on-the-command-line-and-have-it-appear-in-c).

`export $PATH` -> export a variable so that it is an environment variable. Environment variables get passed to every subsequent command.

To make an environment variable persistent (so use it again after the current session) alter either the 
* ~/bash_profile file -> persistent for one use.
* /etc/profile or /etc/profile.d -> persistent for all users.

##Basic Commands

1. `halt` -> shutdown
2. `reboot` -> restart
3. `init [0/6]`
  1. `0` -> will shutdown the OS
  2. `6` -> reboot
4. `shutdown`
  1. `-H` -> halt
  2. `-P` -> poweroff
  3. `-r` -> reboot
  4. `-c` -> cancel a shutdown
5. `exit` -> close terminal session
6. `su [name or - (to become root)]` -> substitute user (super user)
7. `env` -> see the environment variables
8. `top` -> show a list of applications and processes
  1. `q` to quit
9. `clear` -> clear the screen
10. `which [command]` -> show full path of an application
11. `whoami` -> username of current logged in user
12. `netstat` -> shows the status of the network
13. `route` -> view and manipulate the routing table
14. `ifconfig` -> see and modify  configuration set to a network card. Newer versions of Linux use `ip addr`

##`uname` (Unix Name)##

`uname` -> Give information about the system. Flags:

1. `-s` -> kernel name
2. `-n` -> host name (node name)
3. `-r` -> kernel release number
4. `-v` -> kernel version number
5. `-m` -> machine hardware name
6. `-p` -> processor type (e.g. x86_64)
7. `-i` -> hardware platform (e.g. x86_64)
8. `-o` -> operating system
9. `-a` -> Give all information add once (`uname -a | sed 's/ /\n/g'` for nice formatting)

##Command line history##

The *~/.bash_history* file shows the your command history. With arrow up you can cycle through the history.

`export HISTFILESIZE=9999` -> Up the history file size of the ~/.bash_history* file to 9999. The default size is 1000.

##`cd dirpath`##

Change working dir to dirpath. `cd` without arguments take you to home dir.

##Shell config files##

A login shell is created at boot or when you log in from a remote machine. The terminal of the GUI is not a login shell. The type of shell dictates what config files are used to setup the environment of the shell. [More info](http://stackoverflow.com/questions/415403/whats-the-difference-between-bashrc-bash-profile-and-environment)

These config files are shell scripts with commands that configure the shell with aliases, functions and variables. Examples:

System wide:
* */etc/profile* -> (login shell)
* */etc/bashrc* -> (non-login)

User specific:
* *~/.bash_profile* -> (login shell)
* *~/.bashrc* -> (non-login)

You can find this in `man bash`

you'll find most people end up telling their *.bash_profile* to also read *.bashrc* with something like:

`[[ -r ~/.bashrc ]] && . ~/.bashrc`

Example: one can edit the $PATH variable in these config files.

##Variables##

1. Variable = a placeholder for another value
2. Environment = a set of variables that are used in configuring computing environmemts. Environment holds current directory and $PATH
3. User defined and system defined variables:
  1. User defined -> defined by the user
  2. System defined

Example: *~* stands for home directory. With `cd ~` bash looks up the $HOME variable and changes dir to that location.

Common environment variables:

1. BASH and SHELL -> */bin/bash*
2. CPU -> spec to your system
3. DISPLAY -> the local video card monitor
4. ENV -> */etc/bash.bashrc*
5. EUID -> UID number of current user
6. HISTFILE -> *~/.bash_history*
7. HISTSIZE -> 1000
8. HOME -> current users home directory
9. HOST and HOSTNAME -> systems assigned hostname
10. LOGNAME -> username of current user
11. MAIL -> Path to mailbox: */var/spool/mail/username* OR */var/mail/username*
12. OLDPWD -> prior current dir
13. OSTYPE -> Linux
14. PATH -> distribution dependant. Where to look for files and commands
15. PSI -> distribution dependent
16. PWD -> depends on current dir within
17. USER and USERNAME -> username of the current user

`env` -> get all environment variables.  
`set` -> get environment variables.  
`echo $KEY` get value of variable.  

`KEY=VALUE` -> set $KEY to VALUE for the current session
`PATH=$PATH:/var/opt/` -> append to VALUE.

To make a change to a variable available outside the current session, use `export KEY` **without the dollar sign!**

To make a system persistent after reboots, change the value in a bash config files, such as ~/.bash_profile

##Globbing##

The process of *expanding* a non-specific filename containing a wildcard characterto a set of specific filenames that exists.

Globbing means global command

List of characters for expanding:

* `*` Zero or more characters. Example: `ls *.txt`
* `?` One character. Example: `ls test?` for test1 or `ls test??` for test12
* `[ab]` a **or** b. Example: `ls [ab]*.txt`. [] is a more specific type of `?` expansion and only works for a single character. So touch [fF]ile.txt does not work. Therefor use:
* `{a,A}` a or A. Example `touch {f,F}ile.txt`
* `{1..20}` range of 1,2,3,4..20. Example `touch fotos-{2000-2010}`
* [more info](http://tldp.org/LDP/GNU-Linux-Tools-Summary/html/x11655.htm)

##Quoting and backticks##

###Double quotes###
Substitutes value of variables and commands.  
Example: `echo "Username is $USER"` will print current username

Exception: escaping (or negating the special character '$') with the backslash `\` character.
Example: echo "The cheeseburger costs \$5.00"

###Single quotes###
Preserves the literal meaning of each character of a given string, thus turning of the special meaning.  
Example: `echo 'Username is $USER'` will print the literal Username is $USER

###Command Substition with the backtick `####

What is in the backticks and the backticks itself will be substituted with output from the command in the backticks:

`echo "Did you know that there are `wc -w < testfile1` number of words in testfile1?"` one can also use `$()` for command substitution

##Formatting Commands##

Three steps of operation of a Linux command:

1. Computer waits for user input.
2. User selects a command via keyboard or mouse.
3. Computer executes

* First word is a command, the rest are parameters.
* In general commands are in lowercase (remember, unlike MS command prompt, bash is case sensitive).
* Command and parameters are separated by either one or more spaces.
* With the backslash `\` token the prompt goes to the next line. Then press enter to end input of the command
* 

##Working with options##

Parameters can be divided in two types:
1. Parameters **with** a dash `-` are called options. Example `ls -al`
2. Parameters **without** a dash are called arguments

In general formatting commands look like:

`command options arguments`

##`!!` and `background`

1. `!!` -> subsitute for the last command entered. Handy for `sudo !!`
2. `COMMAND&` -> run a command in the background. `disown` to remove a job from the current shell.
