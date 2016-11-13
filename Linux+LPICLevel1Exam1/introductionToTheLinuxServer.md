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
All (default)

Without a letter, it defaults to All so `chmod +x FILE` grants execute permission to user, group AND others!

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

#Cron Jobs

A cron job is a scheduled task. 
Cron is stateless.
If a time occurs where a scheduled task should be executed and the computer is shut down, the task will not be executed.

There is a system cron and a user cron

##System cron

`ls /etc | grep cron` gives the following output:

anacrontab
cron.d
cron.daily
cron.deny
cron.hourly
cron.monthly
crontab
cron.weekly

###Structue of */etc/crontab*

```
SHELL=/bin/bash
PATH=/sbin:/bin:/usr/sbin:/usr/bin
MAILTO=root

# For details see man 4 crontabs

# Example of job definition:
# .---------------- minute (0 - 59)
# |  .------------- hour (0 - 23)
# |  |  .---------- day of month (1 - 31)
# |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
# |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri,sat
# |  |  |  |  |
# *  *  *  *  * user-name  command to be executed
```

**Asterix means  everything**, so the following line:

`* * * * * root echo "hello world" > /tmp/hello.txt`
Means on every minute, hour, day of the month, month on every day of the week it will execute the command.

##/ Step values
`*/5 * * * * root echo "hello world" > /tmp/hello.txt`
Means divide all the possible 60 minutes by 5, so do it 12 times. (which is every 5 minutes)

`*/2 */2 * * * root echo "hello world" > /tmp/hello.txt`
*/2 means off all the 60 minutes, do it 30 times, so in intervals of 2 minutes 
*/2 means off all the 24 hours, do it 12 times, so in intervals of 2 hours

##Multiple values with range - or explicit stating ,

`*/2 0-3 * * * root echo "hello world" > /tmp/hello.txt`
*/2 means off all the 60 minutes, do it 30 times, so in intervals of 2 minutes 
0-3 means between 0 and 3 am

`*/2 1 1,15 * * root echo "hello world" > /tmp/hello.txt`
*/2 means off all the 60 minutes, do it 30 times, so in intervals of 2 minutes 
1 every 1 am
1,15 every 1st and 15th day of the month

## Simpler way of executing a script time based

Copy the script (or a symlink) in the:
1. cron.hourly
2. cron.daily
3. cron.weekly
4. cron.monthly


##*/etc/cron.d/*

*/etc/cron.d/* follows the same format as */etc/crontab*, BUT:
1. Files in */etc/cron.d/* do **not** get overwritten on upgrades, */etc/crontab* can be overwritten. Therefor it is better to use */etc/cron.d/*
2. */etc/cron.d/* does not inherit environment variables from */etc/crontab*, you have to set it manually

##*/var/log/cron*

Holds a log of all the things cron is executing AND edits done via crontab

## Users cron jobs

Regular users can schedule their own cron jobs as longs as their name is **not** in the */etc/cron.deny* file.

You can also remove */etc/cron.deny* and create a file */etc/cron.allow*. This would mean that by default all users have no acces to cron, unless their name is **in** */etc/cron.allow*

The user's cron is in `/var/spool/cron/crontabs`, but they are **not** intended to be edited directly, use:

`crontab` -> bin to edit a user's crontab, for example `crontab FILE` imports the cron task from the file and checks if it is the correct syntax 
  1. `-l` -> list the user's crontab
  2. `-e` -> edit the user's crontab via text editor

#Introduction To Linux Package Managers

2 package managers:

1. Debian
  1. dpkg: source file to install a package without a repository
  2. apt-get: package manager (handles dependencies)
2. RedHat: 
 1. rpm: source file to install a package without a repository 
 2. yum: package manager (handles dependencies), uses rpm to install a package

**yum**

Yum uses rpm to install a package

*/etc/yum.repos.d* -> holds all the repo's

`yum search KEYWORD` -> search all your repo's
`yum update [PACKAGENAME]` -> download updates for PACKAGENAME or all packages if PACKAGENAME is omitted.

**apt-get**

`yum install` contacts the repo to get the most recent package. apt-get doen't do this, therefore, start with:

`apt-get update` -> get the latest package info, e.g. resyncs with the repo's
`apt-cache search PACKAGENAME` -> search the local cache of the repo's for a package

`apt-get upgrade [PACKAGENAME]` -> download updates for PACKAGENAME or all packages if PACKAGENAME is omitted.

Installing the latest versions is recommended for security 

#A Look At System Resources With The Linux **Top** Command

`top` -> display Linux processes

Example output:

```
top - 11:53:19 up  2:33,  1 user,  load average: 0.00, 0.01, 0.05
Tasks: 113 total,   2 running, 111 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem :  1015348 total,   369704 free,   121540 used,   524104 buff/cache
KiB Swap:  2097148 total,  2097148 free,        0 used.   716064 avail Mem 

  PID USER      PR  NI    VIRT    RES    SHR S %CPU %MEM     TIME+ COMMAND                     
  914 root      24   4  451620  36160   5368 S  0.3  3.6   0:24.55 aws                         
    1 root      20   0  125832   6532   3924 S  0.0  0.6   0:04.54 systemd                     
    2 root      20   0       0      0      0 S  0.0  0.0   0:00.00 kthreadd                    
    3 root      20   0       0      0      0 S  0.0  0.0   0:00.00 ksoftirqd/0                 
    5 root       0 -20       0      0      0 S  0.0  0.0   0:00.00 kworker/0:0H                
    7 root      rt   0       0      0      0 S  0.0  0.0   0:00.00 migration/0                 
??? from here until ???END lines may have been inserted/deleted
    8 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcu_bh                      
    9 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/0                     
   10 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/1                     
   11 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/2                     
   12 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/3                     
   13 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/4                     
   14 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/5                     
   15 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/6                     
   16 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/7                     
   17 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/8                 
```

Load average per minute, 5 minute and 15 minute.
Load average is the % of CPU utilization of the time frame. So:

0.00 0.00 .30 would mean 30% utilization over the past 15 minutes. If the number is 1 or goes above 1, it depends on many CPU's your system has. If:

1. 1 CPU, than processes have to wait untill processing resources are available. Your system is bogging down.
2. 2 CPU's, if:
  1. The number is exactly 1, then 1 CPU is fully used
  2. The number is exactly 2, then 2 CPU's are fully used

`SHIFT + m`  -> resort on memory utilization
`SHIFT + p` -> resort on cpu (processor) utilization

NI = **Nice value** from -20 to 19 where 19 is the lowest priority value. This means that all processes with a lower value that 19 have more priority for using the CPU.

Explanation on (StackOverflow)[http://askubuntu.com/a/656787]:

```nice value is a user-space and priority PR is the process's actual priority that use by Linux kernel. In linux system priorities are 0 to 139 in which 0 to 99 for real time and 100 to 139 for users. nice value range is -20 to +19 where -20 is highest, 0 default and +19 is lowest. relation between nice value and priority is :

PR = 20 + NI
so , the value of PR = 20 + (-20 to +19) is 0 to 39 that maps 100 to 139.

According to top manual:

PR -- Priority The scheduling priority of the task. If you see 'rt' in this field, it means the task is running under 'real time' scheduling priority.
NI is nice value of task. A negative nice value means higher priority, whereas a positive nice value means lower priority.Zero in this field simply means priority will not be adjusted in determining a task's dispatch-ability
```
For searching:
`L` -> locate a certain string
`o` -> filter on a column, example: `o COMMAND=http`. Press `o` again for a new filter
`CRTL+o` -> see all filters
`=` -> clear all the filters and brings you back to the start screen of top

Manipulate proceses:
`r` -> renice a value; give a new value for nice
`k` -> kill a process with a (signal)[https://bash.cyberciti.biz/guide/Sending_signal_to_Processes]:
  1. 9 (SIGKILL)-> force quit for when a process is hung
  2. 15 (SIGTERM)-> nicer way of terminating a process


