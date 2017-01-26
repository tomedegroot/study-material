#Topic 105: Shells, Scripting and Data Management

##Customize and use the shell environment

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

So my_command1 has access to the variable that is exported. Just typing `export` gives an overview of all the currently **exported** variables.

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

After some research: some parts of $PATH, such as */usr/bin* is set by bash itself, and not via 

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

So you could adjust these to set certain settings by default

