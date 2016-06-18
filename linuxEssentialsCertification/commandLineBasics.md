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

##$Path##

The interpreter first looks at the working dir and then the $PATH for executables and filenames.

`echo $PATH` -> see your current path.

To add stuff to the $PATH:
`PATH=$PATH:pathToAdd` -> This adds the path as a [local variable](http://unix.stackexchange.com/questions/56444/how-do-i-set-an-environment-variable-on-the-command-line-and-have-it-appear-in-c).

`export $PATH` -> export a variable so that it is an environment variable. Environment variables get passed to every subsequent command **in the current session.**  

To make an environment variable persistent alter either the 
* ~/bash_profile file -> persistent for one use.
* /etc/profile or /etc/profile.d -> persistent for all users.

