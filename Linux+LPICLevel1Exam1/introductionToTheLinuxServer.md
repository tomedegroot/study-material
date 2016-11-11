#Basic User Management For Fresh Images/Server Installs

(Note to self, `tom` is the user)

`su` -> Substitute user. Without any ARGUMENTS substitute to root

`useradd USER` -> add a user

`passwd [USER]` -> set a password [FOR USER]

`userdel` -> remove user
  1. `-r` -> remove the /home/USER dir as well
  Example: `userdel -r user`

#A Look At VI And Nano Text Editors

VI is also installed on the boot loader. VI knowledge is required for the certification!

Nano is much easier to use for people new to Linux

#Root User, Sudo Users And Setting Up Your User Account

Extra:

`!!` -> substitutes for previous command. Nifty when you forgot to type `sudo`

Core:

`su` -> become another user
  1. Called without arguments defaults to root user 

`sudo` -> execute command as another user
  1. Set user -u, defaults to root

*/etc/passwd* -> file which contains user info

*/etc/sudoers* -> file which contains the sudo policy
See: 
```## Allows people in group wheel to run all commands
%wheel	ALL=(ALL)	ALL``` 
In CentOS, all the users in the wheel group have sudo privilege. This differs per distribution. In Ubuntu, this group is called sudo

`visudo` -> command to alter the */etc/sudoers* file. visudo checks the **syntax** of */etc/sudoers* before overwriting it.

`usermod [OPTIONS] USER` -> modify users
  1. `-G [groupname]` -> add user to group

`groups USER` -> see the groups of which the USER is a member

`userdel [OPTIONS] USER` -> remove a user
  1.'-r' -> Delete a user's home dir

*/etc/default/useradd* -> config defaults for adding a user

'useradd [OPTIONS] USER' -> add user.
  1. On Ubuntu `useradd` is considered low level utility. `adduser` is the *recommended tool.*

#Navigating Linux & The File System

Core:

`rmdir LOCATION` -> remove an empty directory
`rm [OPTIONS] LOCATION` -> remove a file
  1. `-r` -> recursively
`cp [OPTIONS]SOURCE DESTINATION` -> copy
  1. `-r` -> recursively. Mandatory for copying dirs. This will also copy their content
*/etc/* -> is generally used for configuration files
*/var/* -> is generally used for files that frequently change, such as logging

#Logs and more file management tools

Core:

`tail [OPTIONS] file` -> show the last 10 lines of a file
  1. `-n NUMBEROFLINES` -> show n last lines instead of 10
  2. `-f` -> follow the files for new stuff being written to it

*/var/log/* -> contains log files. [Log files and their contents](http://www.thegeekstuff.com/2011/08/linux-var-log-files/)
*/var/log/secure* -> log for all the info related to authentication and authorization (On Ubuntu it's auth.log)
Example combination of piping, 1 & 3: `tail -f /var/log/secure | grep fail | grep authentication`
`cat cron secure > custom.log` -> add two files to a new file
`less`
  1. `b` -> backword one window
  2. `space` -> forward one window
  3. `/` -> search
  4. Look up the help file with `less --help`

#File permissions

Extra:

`cat /proc/version` -> get the distribution. Sometimes this is retrievable with `uname -a`. uname stands for Unix Name

`realpath FILE` -> returns an absolute path. Resolves symlinks and thus creates a canonical path.

`dirname` -> strips the last component of a file name, thus giving you the directory

Example: `DIR=$(dirname $(realpath ./file)) && echo $DIR` -> this echoes out the absolute path to the file after it's been stored in a variable
 
Core:

`touch FILE` -> create or update timestamp of a file
`ls -l` -> list file permissions. This would output something like:

-rw-rw-r--. 1 anthony anthony    0 Nov 11 09:46 myfile

The first place (a dash in the example) shows the file types. Following possiblities:

  1. Regular (-)
  2. Direcotry files (d)
  3. Block file (b)
  4. Named pipe file or just a pipe file(p)
  5. Symbolic link file(l)
  6. Socket file(s)

(See an explaination of all the types)[https://www.linux.com/blog/file-types-linuxunix-explained-detail]

`chmod [OPTIONS] MODE FILE` -> Can only be done by the owner of root

MODES, modeletter is capitalized: 
1 = Execute, 
2 = Write, 
4 = Read

Multiple ways of setting the permission. By:

1. One number, such as 6 which means write and read
2. `ugoa+MODELETTER` to grant a right to 
3. `ugoa-MODELETTER` to revoke a right

ugoa stands for:
User
Group
Others
All

The permission bits have different meaning for a folder:
1. The read bit allows the affected user to list the files within the directory
2. The write bit allows the affected user to create, rename, or delete files within the directory, and modify the directory's attributes
3. The execute bit allows the affected user to enter the directory, and access files and directories inside
4. The sticky bit states that files and directories within that directory may only be deleted or renamed by their owner (or root)

`groupadd GROUPNAME` -> Add a group
`usermod -g USER GROUPNAME` -> add a user to a group
  1. `-g -a` -> append the new group to user's group. Without the -a, all the groups which are non-primary and non-listed will no longer have the user in the group.
`groups USER` -> check the groups to which a user belongs

`chown [OPTIONS] USER:GROUP FILE` -> change the owner and/or group of the file. The colon can also be a dot.
  1.`-R` Recursively
  2. USER: -> sets the user and group to USER
  3. :GROUP -> only sets the group

You can only `chown` if they have the target user and group privileges. This means that only root can change the file's ownership.


