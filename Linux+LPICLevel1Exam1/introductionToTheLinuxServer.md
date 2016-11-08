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

6.14
