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

```$ set a b c d e f g h i j k l m
$ echo $1
a
$ echo ${10}
j```

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
2. `tzconfig` -> set */etc/localtime* for you
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

1. The shebang: `#! /bin/bash` -> specify bash, because the used might use another shell
2. A file must be executable and have a shebang to run directly,
3. Or not run directly via: `bash script.sh` (No shebang on +x permission needed on script.sh)
4. A good place to store the script for more users to use is in */usr/local/bin/*

###Parameters:

1. `$0` -> Holds the invoked command (can be the relative or absolute path)
2. `$1` - `$N` -> Holds positional parameters

###Substition:
1. `$(COMMAND)` or `\`COMMAND\`` -> command substitution. Substitute with the command output (p.345)

* Extra info on why using '[]' in `ps -ef | grep [m]ysqld` doesn't match it's own process:

2. `$((MATHEXPRESSION))` -> arithmetic substitution -> `echo $((2+2))` or:

```
PROCESSLIST=$(ps -ef | wc -l)
echo $(($PROCESSLIST - 1))
```

*You can use `bc` to decimal arithmetic. bc reads the expression from STDIN:

`echo "3.14 * 3 ^ 2" | bc` -> You need to use double quotes to prevent expansion

3. You can substitute within arithmetic substitution: `echo $(( $(ps -ef | wc -l) - 1  ))`

```
When you run ps -ef | grep string, grep is displayed in the output because string matches [...] grep string.

But, when you run ps -ef | grep [s]tring the line isn't displayed, because grep translates [s]tring to string, while ps outputs [...] grep [s]tring, and that doesn't match string
```
[source](http://unix.stackexchange.com/questions/2062/grep-why-do-brackets-in-grep-pattern-remove-the-grep-process-from-ps-results)

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

####Artihmetic testing, notation for command and condition

4. ((ARITHMETIC CONDITION)) -> exit status 0 if an arithmetic test evaluates to true:
5. [[ ARITHMETIC CONDITION ]] -> The newer `[[ ]]` keyword [does artihmetic testing](http://serverfault.com/questions/52034/what-is-the-difference-between-double-and-single-square-brackets-in-bash)

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
**important** To compare equals, use 1 `=` sign!

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
