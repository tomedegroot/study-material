#Topic 105: Shells, Scripting and Data Management

##105.1: Customize and use the shell environment

1. Brunson & Walberg ch. 12
2. linuxacademy.com: [Customizing the Bash Shell](https://linuxacademy.com/cp/modules/view/id/2)

###Introduction to the shell:

How is chosen if and what shell is there for the user?

The shell to use is specified per user in */etc/passwd*.:
 1. Executable:
   1. Executable to the shell: `tom:x:1002:1002::/home/tom:/bin/bash`
   2. If you don't want to the user to have shell, point to executable:
     1. */usr/bin/false* (returns a non-zero exit code, thus blocking acces)
     2. */sbin/nologin* for a polite message. Example: `apache:x:48:48:Apache:/usr/share/httpd:/sbin/nologin`
 2. If no shell is specified, bash is the default shell.

Concepts learned here can be applied to other shells as well, such as the C-shell (csh)

###Variables

####Assigning Variables

Assign a variable: `WEBSERVER_PID=1560`. Important:
  1. **No dollar sign**
  2. **No spaces** around the '=' sign
  3. A variable name can be:
    1. upper- or lowercase
    2. numbers (except the reserverd positional params: $1, $2)
    3. underscore (so no other symbols)
  4. If you have spaces in your value, escape it or surround it in quotes. So the following statements have the same result:
    1. `GREETING=Hello\ World!`
    2. `GREETING='Hello World!'`
    3. `GREETING="Hello World!"`

Using a variable: `echo $WEBSERVER_PID`
  1. The '$' tells the shell to interpret what comes after it, in this case a variable 

A variable can also be set using `declare [OPTIONS] KEY=VALUE`. Via the OPTIONS, certain attributes could be set to the variable such as `-x` which exports the variable.

####Variable scope

By default, a variable only lives in the current shell and not parents or children:

`$ NAME=Tom`
`$ ./my_command`

So the script `my_command` doesn't have acces to the variable $NAME. 

####Passing the variable to a child.

There are two ways of passing a variable to a child:

1. Pass the variable to **only one child process**: `$ NAME=Tom ./my_command`
2. Pass the variable to all child processes: 

`$ export NAME=Tom 
`$ ./my_command1`

So my_command1 has access to the variable that is exported **to the environment of my_command1**. Just typing `export` gives an overview of all variables automatically exported to the environment of child processes.

####Setting a variable from a child

A common pattern is to set variable assignments in a different file and use that file in a script in a command line. To read the variables in such a file do:

1. `source config_file.sh` 
2. or the shorthand . for source: `. config_file.sh`

Sourcing a files executes it in the current environment and doesn't create a seperate child environment. If there is no `export` of the variables in the script, child processes of the current process will not have access to the variables.

####`unset` and `set`

`unset NAME` -> will unset the variable $NAME. Note that you **cannot put the dollar sign there*

`set [ARGUMENTS]` does three things:

1. Without any arguments it shows **all the variables in the current environment (so both the exported and not exported onces)**
2. With arguments you can set the behaviour of bash:
  1. `set -x` or `set +o xtrace` output commands as they are execute (useful for script debugging). To revert: `set +x`
  2. `set -C or `set -o noclobber` don't overwrite existing files with redirects To revert: `set +o noclobber`
3. Assign positional parameters: 

```
$ set a b c d e f g h i j k l m
$ echo $1
a
$ echo ${10}
j
```

Why `${10}`? -> so the shell doesn't expand $1 to 'a' so you would get 'a0'. 2 takeaways:

1. Variable expansion (`${}`), is not the same as brace expansion (`{}`)
2. You can use `${}` if you only want to expand on part of what comes after the dollar sign. So `${foo}bar` extends foo, but not bar. And it [is necessary when expanding for positional parameters above 9](http://stackoverflow.com/a/8748880/1941737). So it is a more precise way to tell to bash what to expand

###compound commands executed in  a subshell (so it has no access to variables if they are not exported)

1. `(command)` -> create a compound command, but do **not** substitute the output, so `wc -l (ls)` will **not** work and redirection has to be done on the complete compound command. See our `dircopy` function in this document where this can be useful: first change dir and then read from STDIN in 1 command.
2. `$(command)` -> create a compound command and substitute the output. This means the STDOUT is placed where `$(command)` is 

To demonstrate, xecute the following:

```
echo "In parent $BASH_SUBSHELL pid $$"
FOO=bar
echo $FOO
(FOO=baz; echo -n "In subshell $BASH_SUBSHELL "; echo $$)
echo $FOO
```

Result:

```
In parent 0 pid 1758
bar
In subshell 1 1758
bar
```

($$ will be substituted for the PID)

###Using `env`

1. `env` without any arguments prints the environment
2. Place `#! /bin/env ruby` in the start of the script gets the shell to search for the executable ruby in $PATH
3. Manipulate the env just before running a command: `env [COMMAND [ARGS]]`, so for example: `env -i sh -c 'echo $PATH'`
  1. `env -i` -> Ignore the current environment (test this via `env -i env`)
  2. `sh -c 'STRING'` -> read the Command(s) from string and execute immediately

####EDITOR

$EDITOR -> variable which holds your default editor

###Global and user shell settings

####setting up the shell

Order of sourcing scripts for a **login session**:
1. */etc/profile*
2. files in */etc/profile.d*
3. *~/.bash_profile*
4. *~/.bashrc* is sourced from *~/.bash_profile* (optional: On RedHat, the */.bashrc* sources */etc/bashrc* if it exists, which sources everythin in */etc/profile.d*)
5. When logging out: *~/.bash_logout* is sourced

**Mind you** the sourcing of */.bash_logout* when logging out is part of the loggin session

A non-login session is mostly when:
1. The root user uses `su` to become another user
2. A sysadmin uses `su` to become the root user

Order of sourcing scripts for a **non-login session**:

1. *~/.bashrc*
2. On RedHat, the */.bashrc* sources */etc/bashrc* if it exists.

(*~/.bash_profile* is **not** sourced from */.bashrc*, because then you would end up in an invinite sourcing loop)

**Mnemonic:** In short *~/.bashrc* is sourced from *~/.bash_profile*, not the other way around

####$PATH

$PATH contains your dirs where to search for commands. It's separated by colons:

```
[root@t-degroot1 ~]# echo $PATH
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/tom/.local/bin:/home/tom/bin
```

The shell will search the path in order from left to right (so if a command is */usr/local/bin* and in */home/tom/bin*, it will execute the one in */usr/local/bin*)

To add a dir to your $PATH:

`export PATH=$PATH:$HOME/bin`

Trick to add the working dir to your path: `export PATH=$PATH:.` This gets interpreted, so it's not statically set when you set the $PATH variable and 'moves' with you as you travel through the system. This comes with security risks: if a user puts a malicious program called `ls` in it's home dir and the root user is there, problems arise.

After some research: some parts of $PATH, such as */usr/bin* is set by bash itself, and not via */etc/profile* or */etc/bashrc*

####Aliases

`alias nameOfAlias="contentsOfTheAlias"` Example: `alias ll="ls -l"`. So an alias is a form of substitution and it replaces the whole or a part of your command.

To know:

1. Aliases have precendence over $PATH, so if you add options to a command in $PATH, the alias will be used: `alias rm="rm -f"`, every time you issue the command `rm`, `rm -f` will be executed.
2. How to bypass an alias?
  1. Enter the full path to the command, example: */bin/ls*
  2. Escape: `\ls` (alias `ls` is aliased to add colors, do '\ls' to see the difference)

####Functions

A function runs code and is **not substitution**. Form:

`function name() {commands}`

Example of this function added to *~/.bashrc*:

1. Define the function in a file

```
#copy the contents of a dir
function dircopy(){
        tar -cf - * | (mkdir $1 && cd $1 && tar xf -)
}
```

2. Then source the file where the function is in: `. file-with-function.sh`

3. Call the function: `dircopy ~/backup`

####Prompt string

#####Setting prompt string one ($PS1)

The variable PS1 holds the content of the command prompt. To make the following command prompt:

`[tom@t-degroot1 backup]$ `

Set $PS1 like so: `export PS1="[\u@\h \W]$ "` -> the prompt will be updated immediately, no need to relogin

For the exam: you don't have to know all the abbreviations, just know special values are escaped with `\`. Look it up in `man bash` under '**PROMPTING**'

######Dynamic content in $PS1

It is possible to call a function or execte a command from within $PS1: `export PS1='$(date +%r) - [\u@\h \W]$ '`

**important** -> every time bash generates the prompt string, it reads the value of $PS1 and does command substitution at runtime. Therefor, if you have dynamic content in your prompt string, you must place the variable PS1 in single quotes. If you would assign the value to PS1 via double quotes, bash would already do command substitution and before assigning the value to PS1 and the prompt would have the same value every time.

######Prompt string 2 ($PS2)

$PS2 is used when the command prompt goes over multiple lines. If $PS2 is not set, bash uses the default `>` to indicate multi line input.

###Skeleton home dir for new users

The location of the skeleton dir for new users is set in */etc/default/useradd*

By default */etc/default/useradd* points to */etc/skel*.

*/etc/skel* hold a default value for bash customization files:

```
-rw-r--r--.   1 root root   18 Jan 16 19:42 .bash_logout
-rw-r--r--.   1 root root  193 Jan 16 19:42 .bash_profile
-rw-r--r--.   1 root root  231 Jan 16 19:42 .bashrc
drwxr-xr-x.   4 root root   37 Dec 19  2015 .mozilla
```

So you could adjust these to adjust the default home dir.

##Localization and Internationalization 

Internationalization = The feature that *allows* a system to display information in different ways for different locations

Localization = A process that bundles all regional changes for a single location into a locale

So localization is the process of adapting internationalized software for a specific region or language by adding locale-specific components and translating text.

###Time Zones

UTC = Universal Coordinated Time

GMT = Greenwich Mean Time = UTC + 0

DST = Daylight Saving Time: Clock move ahead an hour to take advantage of longer nights. A DST Zone sets the data when an hour is added or removed.

Unix stores all timestamps in since midnight Jan 1 1970 UTC (epoch), and each user sets the timezone for displaying.

###Getting the date

`date [OPTION] [+FORMAT]` -> gets the date and timezone

`date +'%z'` -> `-0500` -> gives you the **timeZone offset.** So Central daylight time=UTC-5

`date -u` -> gives you the date in UTC

###Setting timezones

Timezone info is stored in binary in */usr/share/zoneinfo*, so for example: */usr/share/zoneinfo/Europes/Amsterdam*. 

####System timezone

System timezone is stored in */etc/localtime*. To set it, make a copy of or symlink to the right timezone from */etc/localtime*:

`ln -sf /usr/share/zoneinfo/Europe/Amsterdam /etc/localtime`

####User timezone

Users get the system timezone by default. They can override it by setting the $TZ environment variable. For example:

`TZ=Europe/Amsterdam date +'%z'` or `TZ=America/New_York` date +'%z'. Example:

```
[root@t-degroot1 Europe]# date +'%z'
+0100
[root@t-degroot1 Europe]# TZ=America/New_York date +'%z'
-0500
[root@t-degroot1 Europe]# TZ=Asia/Hong_Kong date +'%z'
+0800
```

**Mind the forward slash after the continten and the underscore if a city name consists of two words.**

####Other tools for setting the timezone

1. `tzselect`
2. `tzconfig` -> **GUI** to set */etc/localtime* for you
3. `dpkf-reconfigure tzdata` -> set */etc/localtime* for you

To get the timezone in a word, some distros have additional files:

1. */etc/timezone* (Debian, gives wrong output for me)
2. */etc/sysconfig/clock* (RedHat, it's not in CentOS 7, it's [replaced with the timedatectl command](http://unix.stackexchange.com/a/213114))

###Character Encoding

ISO-8859 Standards:

1. ISO-8859-1: Latin with English chars
2. ISO-8859-9: Latin with Turkish chards
3. ISO-8859-3: Turkish with some others 

Unicode: each char is defined as a code point (a number). The first 127 code points are compatible with ASCII ([ASCII uses 7 bit originally](http://stackoverflow.com/a/14690651/1941737)). There are several Unicode encodings

1. UCS-2: 2 byte Universal Character Set. Stores everything in 2 bytes, but what if there are more bytes?
2. UTF-16: 16-bit Unicode Transformation Format. Anything over 16K is represented with a second pair or bytes.
3. UTF-8: A two bytes minimum of UCS-2 or UTF-16 is not compatible of with existing ASCII files. UTF-8 allows 1 to 6 bytes to be used for the char encoding with the length of the char encoded in the high order bits of the number. So this makes it backwards compatible with ASCII while also being able to store any Unicode code point.

###locales

A locales is represented by:

1. Language code (ISO 639), countries such as Belgium and Canada have multiple languages
2. Country code (ISO 3166)
3. Encoding (optional)

Example: nl_NL.UTF-8

To see all the available locales: `locale -a`

```
[tom@t-degroot1 ~]$ locale -a | grep nl_NL.utf8
nl_NL.utf8
```

Internationalisation in Unix is handled by gettext, which uses the environment variables outputted with the command `locale`:

```
A locale is composed of several locale categories. When a program looks up locale dependent values, it does this according to the following environment variables, in priority order:

1. LANGUAGE
2. LC_ALL
3. LC_xxx, according to selected locale category: LC_CTYPE, LC_NUMERIC, LC_TIME, LC_COLLATE, LC_MONETARY, LC_MESSAGES, ...
4. LANG
```
[source](https://www.gnu.org/software/gettext/manual/html_node/Locale-Environment-Variables.html)

A locale contains settings for the following categories(between brackets in which env variables locale for this setting can be specifically stored(point 3 of the order of reading variables)):

1. Addresses ($LC_ADDRESS)
2. Collation (how to sort) ($LC_COLLATE)
3. Measurement ($LC_MEASUREMENT)
4. Messages ($LC_MESSAGES)
5. Monetary ($LC_MONETARY)
6. Names ($LC_NAME)
7. Numeric ($LC_NUMERIC)
8. Paper (Paper sizes user in the country) ($LC_PAPER)
9. Telephone ($LC_TELEPHONE)
10. Time (date and time formats, 24 hour clock vs AM and PM) ($LC_TIME)

So you can set environment variable and it will be used:

```
[tom@t-degroot1 ~]$ LC_TIME=nl_NL.utf8 date
ma jan 30 20:54:46 CET 2017
```

###converting files between encodings

`iconv -c -f ASCII -t UTF-8 file.txt > file-utf8.txt`

1. `-c` -> clear any unkown chars
2. `-f ENCODING` -> from encoding
3. `-t ENCODING` -> to encoding

`iconv -l` -> get a list of all available encodings

##105.2: Shell Scripting

Most if this is covered in the book [The Linux Command Line](http://linuxcommand.org/tlcl.php), [see my scripts to relearn that](https://github.com/tomedegroot/study-material/tree/master/bashscripts). In here I will just place the learning points that need to be freshen up:

###Running the script:

1. The shebang: `#! /bin/bash` -> specify bash, because the user might use another shell. **if there is no shebang, linux will try to execute using the default shell which in most cases is bash**
2. A file must be executable and have a shebang to run directly,
3. Or not run directly via: `bash script.sh` (No shebang on +x permission needed on script.sh)
4. A good place to store the script for more users to use is in */usr/local/bin/*

###Substition:
1. `$(COMMAND)` or `\`COMMAND\`` -> command substitution. Substitute with the command output (p.345)
2. `$((MATHEXPRESSION))` -> arithmetic substitution -> `echo $((2+2))` or:

```
PROCESSLIST=$(ps -ef | wc -l)
echo $(($PROCESSLIST - 1))
```

*You can use `bc` to decimal arithmetic. bc reads the expression from STDIN:

`echo "3.14 * 3 ^ 2" | bc` -> You need to use double quotes to prevent expansion

3. You can substitute within arithmetic substitution: `echo $(( $(ps -ef | wc -l) - 1  ))`

###Conditionals

####Basic structure and `$?`

```
if ps -ef | grep -q [m]ysqld; then
	echo "Mysql is running"
fi
```

`grep -q` means quit to not generate output. grep exit status is 0 when grep matches at least 1 time.

`$?` -> holds the exit status of the previous command. This can be used for testing. If the exit status of `$?` is 0(=NO ERROR), it evaluates to true, otherwise to false (This is the opposite of other programming languages. Why? Because 0 is the logical output for NO ERRORS so higher numbers mean different errors and evaluating NO ERROR as true is logical, because only with NO ERROR you want to continue execution):

####`else` and `elif`

```
#! /bin/env bash

if ps -ef | grep -q [m]ysqld; then
        echo "Mysql is running"
else
	echo "Mysql is not running"
fi
```

`elif` structure:


```
#! /bin/env bash

TESTFILE=./testfile.txt

if  [[ "$(wc -l < $TESTFILE)" -gt  "10" ]]; then
        echo "$TESTFILE has more than 10 lines"
elif [[ "$(wc -l < $TESTFILE)" -gt "5"  ]]; then
        echo "$TESTFILE has more than 5 lines"
else
        echo "$TESTFILE has less than 5 lines"
fi
```

###Testing syntax

####Notation for test command

1. `test CONDITION`
2. [ CONDITION  ] -> shorthand for test. Mind the spaces. Is still in bash for POSIX copliancy and backwards compatibility. The newer and one is:
3. [[ CONDITION  ]] -> is newer and better in handling unset variables and can also do artithmetic testing

####Notation for FILE and STRING CONDITION

Get possible test conditions via `help test`

`!` negates the result of a conditional:

```
[root@t-degroot1 tom]# [[ ! 2 < 4 ]]
[root@t-degroot1 tom]# echo $?
1
```

#####FILE CONDITION

1. `FILE1 -ef FILE2` -> Equal device and File indode number
2. `FILE1 -nt FILE2` -> FILE1 newer than FILE2
3. `FILE1 -ot FILE2` -> FILE1 older than FILE2

4. `-d FILE` -> exists and dir
5. `-e FILE` -> exists
6. `-f FILE` -> exists and regular file
7. `-h FILE` -> exists and symbolic link
8. `-r FILE` -> exists and readable
9. `-s FILE` -> exists and greater than zero. **mnemonic**: Sero
10. `-w FILE` -> exists and writable
11. `-x FILE` -> exists and executable


#####STRING CONDITION

1. `-z STRING` -> true if string is zero (so empty string)
2. `-n STRING` -> true for non zero string
3. `'STRING1' = 'STRING2'` -> true if equal
3. `'STRING1' != 'STRING2'` -> true if not equal (since ! negates everything in the test, this is equal to: [[ ! 'STRING1  ]])

####Artihmetic testing

#####Arithmetic condition works within `test`, `[ ]` and `[[ ]]`

1. `X -eq Y` -> equal
2. `X -ne Y` -> not equal
3. `X -gt Y` -> greater than
4. `X -ge Y` -> greater than or requal to
5. `X -lt Y` -> lower than
6. `X -le Y` -> lower than or equal to

Examples:

`[ 2 -eq 2 ]` -> $? is 0
`[ '2' -eq '2' ]` -> $? is 0

#####Arithemtic testing with `[[ ]]` and `(( ))`

1. ((ARITHMETIC CONDITION)) -> exit status 0 if an arithmetic test evaluates to true:
2. [[ ARITHMETIC CONDITION ]] -> The newer `[[ ]]` keyword [does artihmetic testing](http://serverfault.com/questions/52034/what-is-the-difference-between-double-and-single-square-brackets-in-bash)

Example:

```
[root@t-degroot1 tom]# (( 2 < 4))
[root@t-degroot1 tom]# echo $?
0
[root@t-degroot1 tom]# (( 2 < 1))
[root@t-degroot1 tom]# echo $?
1
[root@t-degroot1 tom]# [[ 2 = 2 ]]
[root@t-degroot1 tom]# echo $?
0
```
**important** 
`[[ ]]` is purely used for testing, `(( ))` is a broader arithmetic context. This results in:

To compare equals: 
1. use 1 or 2 `=` signs in `[[ ]]`, example: `[[ 1 = 1 ]]`, `[[ 1 == 1 ]]`, `[[ 1 -eq 1 ]]` and [[ '1' -eq '1' ]] are the same.
2. always use 2 equal signs in `(( ))`. Using 1 `=` sign in `(( ))` will try to assign a value.

###`read`

Read data from a string and assign it to VARIABLE: `read VARIABLE`. Example:

```
#! /bin/bash
echo -n "Say something: "

read STRING

if [[ -z $STRING ]]; then
        echo "You didn't say something"
elif [[ -n $STRING ]]; then
        echo "You said $STRING"
fi
```

####Combining multiple conditions in 1 test

Precedence of operators:

1. Bracketes `()`
2. AND
3. OR

Writing of operators

In `[ ]` the only supported ways are:

1. AND -> `-a`
2. OR -> `-o`

In `[[ ]]` and in ``(( ))`` the only supported ways are:

1. AND -> `&&`
2. OR -> `||`

Example: `(( 1 == 1 && (2 == 3 || 2 == 2) ))`

####`case` statement

```
#! /bin/bash
#
# Test menu with case
clear
echo "
Please Select: 
A. Display System Information
B. Display Disk Space
C. Display Home Space Utilization
Q. Quit
"
read -p "Enter selection[A, B, C or Q] > "

case $REPLY in
	q|Q)	echo "Program terminated"
		exit
		;;
	a|A)	echo "Hostname: $HOSTNAME"
		echo $(uptime | sed "s/\w+//")
		;;
	b|B)	df -h
		;;
	c|C)	if [[ $(id -u) -eq 0 ]]; then
			echo "Home Space Utilization (All Users)"
			du -sh /home/*
		else
			echo "Home Space Utilization ($USER)"
			du -sh $HOME
		fi
		;;
	*)	echo "Invalid entry" >&2
		exit 1
		;;
esac
```

Structure:

1. Open with `case VARIABLE in`
2. Write conditional -> Write string(s) to be matched as `STRING)` or `STRING1|STRING2)`
3. Write zero  or more statements to execute if STRING is matched
4. Optionally: write default statements after default conditional: `*)`
5. Close case statement via `esac`

If a condition is matched then those statements will be executed and the case statement terminates.

Extra:

1. With the builtin read, if no names are supplied as in the above statement, the value entered will be assigend to the variable $REPLY by default.
2. `read -p "PROMPT"` -> will display PROMPT to the user, so our program looks like:

```
Please Select: 
A. Display System Information
B. Display Disk Space
C. Display Home Space Utilization
Q. Quit

Enter selection[A, B, C or Q] >
```

##### `case` globbing on a string

File globbing is specifying filename patterns with wildcards such as `cat list.ou*put` would match *list.output* (**mnemonic** glob is derived from global because you describe a global pattern)

See p. 352: `df -P / | tail -1 | awk '{print $5}' | tr -d '%'` -> this leaves an exact number and then match the string as in file globbing:

```
DISKSPACE = df -P / | tail -1 | awk '{print $5}' | tr -d '%'

case $DISKSPACE in
	100)
		echo "disk full"
		;;
	[1-7]*[1-9])
		echo "lots of space left"
		;;
	[8,9]*)
		echo "At least 80% full"
		;;
	*)
		echo "Not a percentage"
		;;
esac
```

Extra:
1. `awk` is a great tool to [cut in a line that does not have equally spaced delimeters](http://www.unix.com/linux/51690-how-cut-column-not-equally-spaced-delimeters.html)

####loops

#####`for`

```
for i in COLLECTION; do
	echo $i
done;
```

COLLECTION can is a bunch of strings generated via. This can be seperated by spaces or newlines. Some examples:
1. 'Tom Jaimie Esmee Bart Timon'
2. Generating values which are seperated by spaces:
  1. brace expansion: {1..10[..incr]}, which generates values seperated by spaces
  2. file globbing:`*.txt`
2. `$(seq)` command substition where the values are seperated by newlines:
  1. `seq LAST` -> starts with 1 and increments with 1
  2. `seq FIRST LAST`, increments with 1
  3. `seq FIRST INCREMENT LAST`
  4. `seq -w` -> pad the output with leading zero's (see p.354)
  5. `cat /etc/passwd`

#####`while` and `until`

`while`: if test is true, execute the loop.

```
while TEST; do
	STATEMENTS
done;
```

`until` is the opposite of while: if result of the TEST is false, execute the loop. Structure:

```
until TEST; do
	STATEMENTS
done;
```

Example:

```
until [[ -f /var/myprocess.output ]]; do
	echo "Still no output, so my process has not completed a run yet."
done
```

You can use `read` in a while loop to read from STDIN. Example:

```
while read -p 'What is your name? ' NAME; do
	echo $NAME
done;
```

Output:

```
[root@t-degroot1 tom]# while read -p 'What is your name? ' NAME; do echo $NAME; done;
What is your name? Tom
Tom
What is your name? 
```

####Special bash variables:

Three types of variables relevant for scripts:

1. `$0` -> holds the command that was used to call the script
2. `$1`, `$2`, $N -> holds in order the arguments passed on to the script.
3. `$#` -> holds the number of arguments passed on to the script

`shift` -> helps you dealing with unknown arguments: moves $2 to $1, $3 to $2 etc

```
#! /bin/env bash

while [[ $# -gt 0 ]]; do
	echo "Now processing argument: $1"
	shift
	echo "There are $# arguments left to process."
done;
```

[See an example of how to combine while, case and shift to deal with an unknown number of positional parameters](https://github.com/tomedegroot/study-material/blob/master/bashscripts/positional_parameters/script_incorporation)

####Returning an exit code

`exit CODE` -> returns CODE and the caller sees this code in `$?`

####Using `grep` in scripts

#####Using brace expansion to avoid grepping it's own process

* Extra info on why using '[]' in `ps -ef | grep [m]ysqld` doesn't match it's own process:
```
When you run ps -ef | grep string, grep is displayed in the output because string matches [...] grep string.

But, when you run ps -ef | grep [s]tring the line isn't displayed, because grep translates [s]tring to string, while ps outputs [...] grep [s]tring, and that doesn't match string
```
[source](http://unix.stackexchange.com/questions/2062/grep-why-do-brackets-in-grep-pattern-remove-the-grep-process-from-ps-results)

#####Use grep to search through binary

In scripts you use commands such as grep. You can:

1. redirect the output of a command
2. redirect STDERR 

And still use the `$?` variable to check the exit status. Example

`grep -r foo /etc > /dev/null 2>&1` 

####`exec`

Normally when you issue a command from the shell, the shell forks itself: this means a child process is created which is an exact copy of the parent process and the child process replaces itself with the `ls` command. You can use `exec` to [replace your own process with another process](http://man7.org/linux/man-pages/man3/exec.3.html)


Example (*./exec.sh*):
```
echo "Hi 1"
exec sleep 1
echo "Hi 2"
```

Output:

```
[root@t-degroot1 tom]# ./exec.sh 
Hi 1
[root@t-degroot1 tom]# 
```

So by using `exec` you specify to **not** create a child process, but to replace the current process directly.

##Basic SQL Management

###Database fundamentals

Random: An index helps to retrieve data fast, but comes with a penalty when data written because the index needs to be updated.

Types of databases:
1. A key-value database is simple and fast. (Example: Redis)
2. Relational database stores data and the relationship between data. 
  1. Almost always uses SQL. (Example: MySQL, Oracle, SQLLite). 
  2. If there is a many-to-many relationship [junk tables can be used](https://megocode3.wordpress.com/2008/01/04/understanding-a-sql-junction-table/). 
  3. The structure the data is stored in a schema. If you make a change to the schema, every row needs to be modified (even adding a null value for a new column is a modification) 
3. Schemaless database:
  1. Called NoSQL because they don't use SQL
  2. Does not enforce relationships
  3. Stores data in documents which are free form
  4. Good for huge databases
  5. Not good for storing transactions
  6. Examples: MongoDB, ElasticSearch and Couchbase

###SQLLite

[Resource](https://www.sqlite.org/cli.html)

`sqlite [databasefile]`

####Info on `sqlite`:

1. If the databasefile doesn't exist it will be created.
2. Dot-commands ([if a command is preceded with a dot, it will be intercepted by the interpreter. You don't need close it with a semicolon](https://www.sqlite.org/cli.html#special_commands_to_sqlite3_dot_commands_)):
  1. `.help` -> show this help message
  2. `.table(s) [TABLENAME]` -> gives you the tables and if TABLENAME is given only of the ones matching the pattern
  3. `.schema [TABLENAME]` -> gives you the schemas
  4. `.header(s) ON|OFF` -> toggle column headers in output
  5. `.mode column` -> set the output mode to left aligned column (typical SQL output)
  6. `.exit` and `.quit`-> exit sqlite
4. In sqlite you can run expressions without a FROM clause: `sqlite> SELECT 1 + 1;`. Other examples:

```
sqlite> SELECT 1 + 1;
2
```


####General info on SQL syntax:

1. Comments start with `--` and can appear anywhere on a line
2. SQL Keywords (SELECT, from) are case-insensitive, but 
3. User generated data (data structure such as table names and data in the database) is case-sensitive

####Notes on conditional testing:

There are multiple ways where conditional testing can be used:

1. After a `SELECT`: 

```
sqlite> SELECT 1 = 1;
1
```

2. After a `WHERE` to constitute a 'where clause'. After the keyword `WHERE`, the SQL interpreter just looks for a test conditional: `WHERE value1 = x`
3. After a `JOIN ON`

Notes on  conditional testing:

1. `WHERE last_name = 'de Groot'` means the last name is 'de Groot', but
2. `WHERE last_name = maiden_name` means where in a row the value of field last_name is the same value as the value of the field maiden_name. **so mind you if there are quotes for literal checking or not to check with the value of another column in** (this way of checking of the value of the column without quotes is also happening in a join claus: `JOIN book ON book.author_id = author.id`)
3. Not equal to can be expressed as `VALUE1 <> VALUE2`:

```
sqlite> SELECT 1 <> 2;
1
```

4. `value1 BETWEEN value2 AND value3` -> example: `WHERE columnname BETWEEN 2010 AND 2012` -> this is `1` (true) for 2010, 2011 and 2012
5. `value1 IN (value2,value3)`
6. `LIKE` -> use like to use wildcards in string comparison:
  1. `%` -> matches zero or more chards
  2. `_` -> matches a single char

```
sqlite> SELECT 'tom' LIKE 't_m';
1
sqlite> SELECT 'tom' LIKE '%o%';
1
```

7. User multiple conditions in the clause with `AND` and `OR`. `ADD` has precendence over `OR` and you can use parantheses to: 
  1. group clauses 
  2. to make it more clear what the grouping is (so to group and `AND` within parantheses): `sqlite> SELECT (30 > 15 AND 30 < 50);`

####`ORDER BY`, `LIMIT`, `ALIAS`

8. `ORDER BY COLUMNUMBER` is possible, so you just state the ordernumber of the column (confusing to me)
9. `LIMIT`:
  1. `LIMIT N` -> Limit to N columns
  2.`LIMIT N1, N2` or `LIMIT N1 OFFSET N2` -> Skip N1 and then show N2 results. 
11. Alias table names via `AS` -> `SELECT * FROM author AS a` -> and further simplify notation via: `SELECT * FROM author a` (You don't need to write as)

####`JOIN`

#####Types of joins (p. 382):
![Image of Joins](https://github.com/tomedegroot/study-material/tree/master/LPIC102/joins.png)  

1. `JOIN [ON...]`:
  1. Carthesian join (= [cross join](http://www.w3resource.com/sqlite/sqlite-cross-join.php)):
    1. `SELECT * FROM author JOIN book;` -> will do a carthesian join and join everything because you didn't specfy conditions in the `ON...` clause (see p.380). 
    2. This is the same as `SELECT * FROM author CROSS JOIN book;` and
    3. `SELECT * FROM author, book;`
  2. `JOIN book ON book.author_id = author.id`
2. `INNER JOIN` -> only product output if there is a match
2. `LEFT JOIN` -> join a table on the right to the table on the left if there is a match on the right. If not, insert a null value
3. `RIGHT JOIN` -> first select from left and only show that if it can be joined with the data on the right, if not: insert a null value. (Note to self: most of the time you do not want to use this, because you are first getting all sorts of data on the left to later decide you don't want it because it doesn't match with a table on the right.)

####NULL

NULL means no value and in SQL you cannot compare with no value. Therefor there are two constructs to compare:

1. `IS NULL`
2. `IS NOT NULL`

(Extra: [How to deal with NULL in joins](http://stackoverflow.com/a/14366034/1941737))

####subselects `()`

subselects work like command substitution, but then you substitute the table of the result of another query:

```
sqlite> SELECT * FROM book WHERE author_id IN (SELECT id FROM author WHERE first_name = 'Sean');
3|Wireless All In One For Dummies|2009|1|2009
4|Check Point CCSA Exam Cram 2|2005|1|2004
```

*p. 386: if you use an `IN` claue, the subselect may only return 1 column.

And you can also join the results of a subselect:

```
sqlite> SELECT * FROM book b INNER JOIN (SELECT * FROM author a) a ON b.author_id = a.id; 
1|LPIC 1 Exam Cram 2|2004|2|2004|2|Ross|Brunson
2|Linux and Windows 2000 Integration Toolkit|2001|2|2000|2|Ross|Brunson
3|Wireless All In One For Dummies|2009|1|2009|1|Sean|Walberg
4|Check Point CCSA Exam Cram 2|2005|1|2004|1|Sean|Walberg
```

####Group data

A `GROUP BY` consists of two things:

1. `GROUP BY` clause to specify where to group on (can be multiple columns)
2. If you are selecting more than what you are grouping: AGGREGATE functions to wrap us the fields you are not GROUPING:
  1. AVG(column)
  2. COUNT(column)
  3. MIN(column)
  4. MAX(column)
  5. SUM(column)

Example:

```
sqlite> SELECT first_name, last_name, COUNT(b.id) FROM author a INNER JOIN book b on b.author_id = a.id GROUP BY first_name, last_name;
Ross|Brunson|2
Sean|Walberg|2
```

####Inserting data

`INSERT INTO table_name(columns) VALUES(values) [, VALUES(values)];` -> Add multiple VALUES statements to insert multiple records:

`INSERT INTO employee(name, age) VALUES('Tom', 28), VALUES('Hans', 30);`

Or another option if you will providing the data for all columns or accept that the data you do not provide will be filled with NULL:

`INSERT INTO table_name VALUES(values)`

####Updating data:

`UPDATE table_name SET column1=value1, column2=value2 [WHERE conditions];` -> **omit the where clause and all rows will be updated**

####Deleting data:

`DELETE FROM table_name [WHERE conditions];` -> **omit the where clause and all rows will be deleted**

####Creating a table:

```
CREATE TABLE table_name (
column_name1 datatype [primary key],
column_name2 datatype
);
```
