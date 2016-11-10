#Basic User Management For Fresh Images/Server Installs

(Note to self, `tom` is the user)

1. `su` -> Substitute user. Without any ARGUMENTS substitute to root
2. `useradd USER` -> add a user
3. `passwd [USER]` -> set a password [FOR USER]
4. `userdel` -> remove user
  1. `-r` -> remove the /home/USER dir as well
     * Example: `userdel -r user`

#A Look At VI And Nano Text Editors

VI is also installed on the boot loader. VI knowledge is required for the certification!

Nano is much easier to use for people new to Linux

#Root User, Sudo Users And Setting Up Your User Account

`!!` -> substitutes for previous command. Nifty when you forgot to type `sudo`

1. `su` -> become another user
  1. Called without arguments defaults to root user 
2. `sudo` -> execute command as another user
  1. Set user -u, defaults to root
3. */etc/passwd* -> file which contains user info
4. */etc/sudoers* -> file which contains the sudo policy
  1. See: ```## Allows people in group wheel to run all commands
%wheel	ALL=(ALL)	ALL``` In CentOS, all the users in the wheel group have sudo privilege. This differs per distribution. In Ubuntu, this group is called sudo
5. `visudo` -> command to alter the */etc/sudoers* file. visudo checks the **syntax** of */etc/sudoers* before overwriting it.
6. `usermod [OPTIONS] USER` -> modify users
  1. `-G [groupname]` -> add user to group
7. `groups USER` -> see the groups of which the USER is a member
8. `userdel [OPTIONS] USER` -> remove a user
  1. '-r' -> Delete a user's home dir
9. */etc/default/useradd* -> config defaults for adding a user
10. 'useradd [OPTIONS] USER' -> add user.
  1. On Ubuntu `useradd` is considered low level utility. `adduser` is the *recommended tool.*

#Navigating Linux & The File System

1. `rmdir LOCATION` -> remove an empty directory
2. `rm [OPTIONS] LOCATION` -> remove a file
  1. `-r` -> recursively
3. `cp [OPTIONS]SOURCE DESTINATION` -> copy
  1. `-r` -> recursively. Mandatory for copying dirs. This will also copy their content
4. */etc/* -> is generally used for configuration files
5. */var/* -> is generally used for files that frequently change, such as logging

#Logs and more file management tools

1. `tail [OPTIONS] file` -> show the last 10 lines of a file
  1. `-n NUMBEROFLINES` -> show n last lines instead of 10
  2. `-f` -> follow the files for new stuff being written to it
2. */var/log/* -> contains log files. [Log files and their contents](http://www.thegeekstuff.com/2011/08/linux-var-log-files/)
3. */var/log/secure* -> log for all the info related to authentication and authorization (On Ubuntu it's auth.log)
5. Example combination of piping, 1 & 3: `tail -f /var/log/secure | grep fail | grep authentication`
4. `cat cron secure > custom.log` -> add two files to a new file
5. `less`
  1. `b` -> backword one window
  2. `space` -> forward one window
  3. `/` -> search
  4. Look up the help file with `less --help`


