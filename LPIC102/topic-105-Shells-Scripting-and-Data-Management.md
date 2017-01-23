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
2. You can use `${}` if you only want to expand on part of what comes after the dollar sign. So `${foo}bar` extends foo, but not bar. And it [is necessary when expanding for positional parameters above 9](http://stackoverflow.com/a/8748880/1941737)

