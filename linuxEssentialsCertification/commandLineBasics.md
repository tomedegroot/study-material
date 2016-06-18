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
