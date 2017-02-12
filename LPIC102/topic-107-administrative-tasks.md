#Topic 107 Administrative Tasks

Important for exam:

1. The user commands (not so much the group ones)
2. Map fields in */etc/shadow* to `chage`, `passwd` and `usermod` options
3. Map fields in */etc/passwd* to `useradd` and `usermod`

##Basic User Management For Fresh Images/Server Installs

###Users

Info on UID:

1. **0** is for the root user
2. **1** is for bin user (system binaries and non-login accounts)
3. **48** is for the apache user
4. **99** is the nobody account (meant for services which needs to run under an account, but it should not be possible to login into the account)
5. **0 - 499** are system users

####*/etc/passwd*

The users are stored in the /etc/passwd file. This file maps the UID to the user name. Structure of the file:

```
smithj:x:561:561:Joe Smith:/home/smithj:/bin/bash
```
Each field in a passwd entry is separated with ":" colon characters, and are as follows:

1. Username, up to 8 characters. Case-sensitive, usually all lowercase
2. An "x" in the password field. Passwords are stored in the */etc/shadow* file.
3. UID. This is assigned by the `adduser` script. Unix uses this field, plus the following group field, to identify which files belong to the user.
4. GID of primary group. Red Hat uses group id's in a fairly unique manner for enhanced file security. Usually the group id will match the user id.
5. Comment field, usually the full name of user. This is called the GECOS field 
6. User's home directory. Usually /home/username (eg. /home/smithj). All user's personal files, web pages, mail forwarding, etc. will be stored here.
7. User's "shell account". Often set to `/bin/bash` to provide access to the bash shell (my personal favorite shell).

####Special Login Files

1. */bin/false* -> if the user's shell is set to this, he cannot login
2. */sbin/nologin* -> if the user's shell is set to this, he cannot login and a message will be displayed that the account is unavailable. If */etc/nologin.txt* exists, the contents of that file will be displayed.
3. */etc/motd* -> after a succesful login, the message of */etc/motd* is displayed (motd = message of the day)
4. *~/.hushlogin -> if in the user's home dir, the loging process is changed and:
  1. No mail check will be done
  2. Do not display information of the last login
5. */etc/login.defs* -> This file defines specify defaults for the `useradd` command ([part of the shadow password suite](http://archive.linuxfromscratch.org/lfs-museum/2.3.5/LFS-BOOK-2.3.5-HTML/x4678.html)) (But some settings are in /etc/default/useradd)
6. */etc/securetty* -> Specifies from which ttys the root user can login. If it does not exist, the root user can login from anywhere
7. */etc/usertty* -> If a system doesn't have PAM (Pluggable Authentication Modules) this file is used to determine location, time, days and system users can login from.

**Important** know what happens if these files are here or not and what kind of message the user sees when he logs in (p. 425)

####`useradd`

*/etc/default/useradd* -> config defaults for adding a user, but also look at */etc/securetty*

`useradd [OPTIONS] USER` -> add a user
  1. `-m` -> Create home. useradd will do this automatically, unless CREATE_HOME in */etc/login.defs* is set to no
  2. `-d HOMEDIR` -> set the path for the homedir. The default is to append the LOGIN name to the BASE_DIR. If you use this option, it must come after the `-m` option
  3. `-k [SKEL_DIR]` -> Copy the contents of SKEL_DIR (or */etc/skel/* by default) for the home dir. Because you can sepcify the SKEL_DIR, you can create multiple skel templates
  4. `-g GROUPNAME` -> Specify the primary group. By default a new group for the primary group will be created (same as `usermod`)
  5. `-u UID` -> Specify the new UID. By default the next available UID will be given

Other less important OPTIONS:
  1. `-D [MODIFY]` -> see the Defaults for useradd defined in */etc/default/useradd*. If MODIFY is set, the defaults will be modified.
  2. `-e EXPIRE_DATE` -> set and expiration date on the account
  3. `-G` -> set secondary groups. Same as with `usermod -a -G`
  4. `-f INACTIVITY` -> The number of days after a password expires until the account is permanently disabled.
  5. `-o` -> create a nonunique UID. Not recommended
  6. `-s FULLPATHTOSHELL` -> set the shell

Example:

`useradd -m -d '/home/fritsie' -k '/home/tom' -s '/bin/bash' fritsie`

Extra notes:

1. A new UID will be created with the next available UID.
2. A new group with same name and new GID will be created (unless `-g` flag is given) and this will be the new user's primary group.
3. The homedir for the new user will be copied from */etc/skel/*

####`usermod`

`usermod [OPTIONS] USER` -> modify users
  1. `-U USERNAME` -> unlock a user's account (same as `passwd -u`)
  2. `-L USERNAME` -> lock a user's account, this prefixes the password field in */etc/passwd* with an exclamation mark (!) (same as `passwd -l`)
  3. `-G LISTOFGROUPS` -> set LISTSOFGROUPS as the secondary groups for USER **(same as `useradd`)**
     1. `-a` -> append the LISTOFGROUPS to user
  4. `-c COMMENT` -> set the Comment for the user. This modifies the GECOS field in */etc/passwd* (5th field) **(same as `useradd`)**
  5. `-d HOMEDIR` -> changes the user's home dir **(same as `useradd`)**
  6. `-e EXPIRE_DATE` -> change the user's expire date (date when account is disabled) **(same as `useradd`)**
  7. `-f INACTIVITY` -> The number of days after a password expires until the account is permanently disabled. **(same as `useradd`)**
  8. `-s FULLPATHTOSHELL` -> set the shell **(same as `useradd`)**
  

####`passwd`

`passwd [OPTIONS] [USER]` -> set a password [FOR USER]
  1. `-l` -> lock a user's account
  2. `-u` -> unlock a user's account
  3. `-S` -> get status of a password
  4. `--stdin` -> read the password from stdin, example: echo "testPassword" | passwd --stdin user3

####`userdel`

`userdel USER` -> remove user
  1. `-r` -> remove the /home/USER dir and mail as well. Without the `-r` option, the home dir will **not** be removed.

Example: `userdel -r user`

!Even if you use the `-r` option, user's files not in the HOME dir will not be removed. Those files will just be owned by the UID. If you create a new user with the same UID, those files will be owned by the new user.

!If you cannot delete a user's account because the user is logged in, proceed with the following steps:

1. `usermod -L user`
2. Kill the current shell: `ps -aux | grep tom` and `kill -9 PROCESSID`
3. `userdel -r USER`

####`su` & `sudo`

`su` -> become another user
  1. Called without arguments defaults to root user 

`sudo` -> execute command as another user
  1. Set user -u, defaults to root

*/etc/sudoers* -> file which contains the sudo policy
See: 
`## Allows people in group wheel to run all commands
%wheel	ALL=(ALL)	ALL`

In CentOS, all the users in the wheel group have sudo privilege. This differs per distribution. In Ubuntu, this group is called sudo

`visudo` -> command to alter the */etc/sudoers* file. visudo checks the **syntax** of */etc/sudoers* before overwriting it.

###groups 

Info on GID:

1. **0** the root group.
2. **1** the bin group.
3. **100** the users group. Here you can place regular users that should have access to resources by giving group ownership of those resources to the users group.

Both [Debian/Ubuntu](https://wiki.debian.org/UserPrivateGroups) and [RedHat](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/3/html/Reference_Guide/s1-users-groups-private-groups.html) use User Private Groups (UPG). This is security feature which creates a new primary group for new users with the same group name as the user name. This is to prevent that the default primary group would be the users group (GID: 100) and all these new users have access to each others files by default.

1. Nested groups are not possible in Linux
2. Two types of user - group association:
  1. Primary: the GID of the primary group of a user is in the 4th field of */etc/passwd*. This group is the group owner for all created files, unless the user has logged in to another group via `newgrp`
  2. Secondary: a user's name is on the line of the group in */etc/group* The user gets access to that group's files.

####*/etc/group*

*/etc/group stores group info.

After `[root@t-degroot1 tom]# usermod -a -G user tom`, the file looks like:

```
user:x:1001:tom
...
tom:x:1002:
```

So the group user has become

Contents of */etc/group*

1. group_name
2. password (x)
3. GID
4. group list of users who are a supplementary member of the group (See point 4 of */etc/passwd* to find the primary member of a group)

`groups [USERNAME]` -> get the groups of the USERNAME, USERNAME defaults to current user.

####`groupadd`

`groupadd [OPTION] GROUPNAME`
  1. `-g GROUPID` -> specify GROUPID
  2. `-p` -> specify password for a group
  3. `-r` -> create system group

####`groupmod`

`groupmod [OPTION] GROUPNAME`

Change the GID of users to 101 -> `groupmod -g 101 users` 

####`groupdel`

`groupdel GROUPNAME` -> delete a group

Before doing this:

1. Make sure the group has nog secondary members
2. Make sure the group isn't the primary group of an account
3. Use the `find group GROUPNAME` to find all the files owned by the group and change ownership 

!Most questions in the exam are on `useradd`, `usermod` and `userdel`

####group passwords

Users can change their primary group temporarily via `newgrp [GROUPNAME]`. This opens a new shell.

With `gpasswd` a password can be given for a group. (and stored in */etc/gshadow*)

1. If this is done, everyone needs to enter this password if they want to change their primary group.
2. If this is not done, users who are a member of the group can change their primary group without giving a password. Other users cannot.

###`getent`

User `getent` to query for both local and network accounts:

`getent passwd tom`

###The Shadow Suite

The shadow suite is a set of security tools which does:

1. Transferring the encrypted passwords from the world readable */etc/passwd* to */etc/shadow* (and for group passwords from */etc/group* to */etc/gshadow*) (*/etc/gshadow* is not a part of the exam)
2. Managing expiry accounts and passwords

####*/etc/shadow*

Example line of */etc/shadow* (see p.435)

```
user:$6$5L53yig0$jfErYa7qp0EY0bgZjAWTFDJNqnm4WK7xy6esZJMS6UgYF9/0A9t/Z2sRv3ZhXWIBPmss4.9tvP80mjMJERuHa1:17204:0::7:::
```

Fields:

1. Login name: Username (user)
2. Password: The user's encrypted password ($6$5L53yig0$jfErYa7qp0EY0bgZjAWTFDJNqnm4WK7xy6esZJMS6UgYF9/0A9t/Z2sRv3ZhXWIBPmss4.9tvP80mjMJERuHa1)
3. Last Change: Days since epoch that have elapsed since the password was last changed (17204)
4. Minimum: The minimum amount of days before a password can be changed again (0)
5. Maximum: The maximim the days before the password must be changed (no value, so it doesn't need to change). Based on this value, the password expiration date shown with `chage -l USER` will be calculated
6. Warning: The number of days before the password epires (field 5) when the user will be warned
7. Inactive: The number of days after the password has expires that the user can still log in and then change the password immediately (no value). Based on this value, the password inactive date shown with `chage -l USER` will be calculated
8. Expiration date: The number of days after the epoch after which the account will expire

The permissions difference (**know this for the exam**):

*/etc/passwd*:

1. Red Hat: `-rw-r--r--. 1 root root 1882 Feb  6 20:56 /etc/passwd`
2. Debian:  `-rw-r--r-- 1 root root 1719 Jan 17 08:10 /etc/passwd

So both 644 (World Readable)

*/etc/shadow*:

Red Hat: `----------. 1 root root 1173 Feb  7 07:38 /etc/shadow`, so 000
Debian:  `-rw-r----- 1 root shadow 1116 Jan 17 08:10 /etc/shadow`, so 640

####Aging passwords

`chage [OPTIONS] USER` -> change user password information (**mnemonic**: change age). This command changes the fields in */etc/shadow*

1. `-l` -> list info
2. `-d LAST_DAY` -> change last change value in days (**m**: d for days), LAST_DAYS can be:
  1. In days since EPOCH
  2. 'YYYY-MM-DD' (**m**: is in days)
  3. '0' -> means the user must change his password
3. `-m MIN_DAYS` -> change Min value (**m**: min is small)
4. `-M MAX_DAYS` -> change Max value (**m**: max is big)
5. `-W WARN_DAYS` -> change the warning days
6. `-I INACTIVE_DAYS` -> change the inactive days
7. `-E EXPIRATIONDATEINYYYY-MM-DD` -> change expiration date **of the account**

This can be done interactively, do I need to know the options?

`passwd` has some of the same options:

`passwd [OPTIONS]`

1. `-d LAST_DAY` -> disable a user account by removing the password
2. `-n MIN_DAYS` -> set minimum password lifetime
3. `-x MAX_DAYS` -> maximum password lifetimein days
4. `-w WARN_DAY` -> sets the warning
5. `-i INACTIVE_DAYS` -> change the inactive days
6. `-S` -> get password information

###User Limits

`ulimit OPTIONS USER`

1. `-c` -> limit the size of core (crash dump files)
2. `-d` -> limit the sirze of the user process data
3. `-f` -> limit the maximum size of files created in the shll
4. `-n` -> limit the number of open file descriptopr or open files allowed
5. `-t` -> limit the amount of CPU time allowed
6. `-u` -> limit the number of processes that a given user can run
7. `-v` -> limit the amount of virtual memory available to a shell
8. `-a` -> check All settings

Do I need to know more than just the options?

##Schedule and Automate Tasks

###Cron Jobs

A cron job is a scheduled task. 
Cron is stateless.
If a time occurs where a scheduled task should be executed and the computer is shut down, the task will not be executed.

There is a system cron and a user cron

####System cron

Is **not** made via `crontab` command, that one is only for the user crontab.

#####Structure of */etc/crontab*

*/etc/crontab* [is the system cron](http://superuser.com/questions/290093/difference-between-etc-crontab-and-crontab-e)

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

All the 5 places acts like filters! Every minute, cron checks if a command is not filtered OUT.

The 6th column (user-name) is only in the system crontab, since it's not necessary for the user crontab (duh)

**Asterix means  everything**, so the following line:

`* * * * * root echo "hello world" > /tmp/hello.txt`
Means on every minute, hour, day of the month, month on every day of the week it will execute the command.

#####/ Step values
`*/5 * * * * root echo "hello world" > /tmp/hello.txt`
Step over all the minutes with 5

`*/2 */2 * * * root echo "hello world" > /tmp/hello.txt`
*/2 means off all the 60 minutes, do it 30 times, so in intervals of 2 minutes 
*/2 means off all the 24 hours, do it 12 times, so in intervals of 2 hours

#####Multiple values with range - or explicit stating ,

`*/2 0-3 * * * root echo "hello world" > /tmp/hello.txt`
*/2 means off all the 60 minutes, do it 30 times, so in intervals of 2 minutes 
0-3 means between 0 and 3 am

`*/2 1 1,15 * * root echo "hello world" > /tmp/hello.txt` (NO SPACE AFTER THE COMMA)
*/2 means off all the 60 minutes, do it 30 times, so in intervals of 2 minutes 
1 every 1 am
1,15 every 1st and 15th day of the month

Ranges can be combined with explicit stating:

`3-5,7 * * * * root echo "hello, time is: $(date)" >> /test.txt` 

And to combine (p.461):

`0 1-23/2 * * *` means between 1-23 hours step with 2.

#####Nicknames for cron time entry in a crontab

The first 5 columns of a crontab which indicate the time to execute can also be replaced with nicknames (in most distro's):

1. @reboot
2. @yearly or @annually
3. @monthly 
4. @weekly
5. @daily
6. @hourly

They always run when a period start, so: 

```
0 0 * * * command
```

and

```
@daily command
```

are the same.


#####Notes on the environment:

`cron` doesn't source *~/.bash_profile* and *~/.bashrc* so the enviroment is scarce. Cron also doesn't load a full $PATH like bash does.

Some variables do have special meaning for cron:

1. `$MAILTO` -> everything a job prints to the screen is mailed to the following address. (default is current user)
2. `$SHELL` -> run the job with a different shell.
3. `$CRON_TZ` -> Use alternate timezone for the crontab.

By default everything a job prints is mailed to the current user. To change this:

1. Change `$MAILTO` variable
2. Within the crontab, redirect STDOUT and STDERR to */dev/null*

#####Where is the system cron stored? 

Stored in:

1. */etc/crontab*/
2. */etc/cron.d*/
3. */etc/cron.{hourly,daily,weekly,monthly}*

######*/etc/cron.d/*

*/etc/cron.d/* follows the same format as */etc/crontab*, BUT:
1. Files in */etc/cron.d/* do **not** get overwritten on upgrades, */etc/crontab* can be overwritten. Therefor it is better to use */etc/cron.d/*
2. */etc/cron.d/* does not inherit environment variables from */etc/crontab*, you have to set it manually

######*/etc/cron.{hourly,daily,weekly,monthly}* -> Simpler way of executing a script time based

Copy the script (or a symlink) in the:
1. cron.hourly
2. cron.daily
3. cron.weekly
4. cron.monthly

####Users cron jobs

Works mostly like a system cron, the difference are stated in these notes.

Looks the same as the system cron, but without the user name column, because the user cron is already tied to a user.

Managing access to user cron (best practice: only do this via `crontab`)

1. if */etc/cron.allow* exists and contain user names, only those users can edit their own crontab. 
2. if */etc/cron.allow does not exists and */etc/cron.deny* exists and contain usernames, the users who are in there cannot create their own jobs
3. if both files are removed, only the root user can create cron jobs

**m***: */etc/cron.allow* has precendence over */etc/cron.deny*

The user's cron is in */var/spool/cron/crontabs*, but they are **not** intended to be edited directly, use:

`crontab` -> bin to edit a user's crontab, for example `crontab FILE` imports the cron task from the file and checks if it is the correct syntax 
  1. `-l` -> List a user's crontab
  2. `-e` -> Edit a user's crontab via text editor
  3. `-r` -> Remove a user's crontab
  3. `-u USER` -> select the crontab of user to execute the option on. **Handy way** for the root user to delete or modify another user's crontab.

**Mind you** root's crontab is, like any other user's cron in */var/spool/cron/crontabs*, the system crontab is used for the whole system.

#####Where are user crontabs stored?

The ones edited with `crontab` (user cron) are stored in */var/spool/cron/*. Although you can edit the files in */var/spool/cron/* directly, use the `crontab` command so you get syntax checking.

####*/var/log/cron*

Holds a log of all the things cron is executing AND edits done via crontab

###Anacron

Why anacron?

1. Simplify cron
2. Meant for jobs that run daily or less frequently and the precise time doesn't matter
3. If the computer was off when the job was s

Differences between cron and anacron:

1. No command, everything is specified in */etc/anacrontab*
2. Everything is run as root
3. Max granularity is 1 day instead of 1 minut
4. Jobs are run consecutively

*Anacron can be run as a daemon, but it's typically run from cron itself.

Example of */etc/anacrontab*:

```
# /etc/anacrontab: configuration file for anacron

# See anacron(8) and anacrontab(5) for details.

SHELL=/bin/sh
PATH=/sbin:/bin:/usr/sbin:/usr/bin
MAILTO=root
# the maximal random delay added to the base delay of the jobs
RANDOM_DELAY=45
# the jobs will be started during the following hours only
START_HOURS_RANGE=3-22

#period in days   delay in minutes   job-identifier   command
1	5	cron.daily		nice run-parts /etc/cron.daily
7	25	cron.weekly		nice run-parts /etc/cron.weekly
@monthly 45	cron.monthly		nice run-parts /etc/cron.monthly
```

The columns are as follows:

1. Period in days between runs of this jobs (some of the @nicknames can be used).
2. Delay in minutes before anacron will execute the job.
3. Job identifier: used by anacron to track the last time the job ran.
4. The command to run.

And just as with a crontab, env vars can be specified via key value pairs (`key=value`)

So in the example, the first line execute a job every day with a delay of five minutes and the job-identifier is cron.daily The command is `nice run-parts /etc/cron.daily`. `nice runs` commands at a lower priority and `run-parts` execute every file in a directory.

So since anacron is responsible for executing the jobs in /etc/cron.daily, those jobs will also run if the system is turned off.

###`at` and `batch`

1. Meant to run a job once. 
2. Both commands open an interactive console where you can enter command(s) separated with `ENTER` and end with `CRTL+D`
3. Make sure the `atd` service is running

####`at`

`at TIME` -> run a job at a specific time

Where TIME can be:

1. HH:MM
2. midnight (12:00 AM)
3. noon (12:00 PM)
4. teatime (4:00 PM)
5. Month, day year format: `January 15 2018`
6. MMDDYYYY
7. 2 pm (= time of day)
8. now + time where time = `N [MINUTES,HOURS,DAYS,WEEKS]` example: `now + 5 minutes`

[See for other ways of entering TIME](http://www.computerhope.com/unix/uat.htm)

####Special options for `at` and `batch`

1. `-f` -> read the commands from a file
2. `-m` -> send email when the job has executed
3. `-v` -> display the time a job will be executed

####`batch`

Is an extension of the `at` command

`batch` -> run a job [when the load average is below 0.8](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/3/html/System_Administration_Guide/s1-autotasks-at-batch.html)

#####Change when at runs batch jobs: `atrun -l`

The load average can be seen via `w` (is the who command)(see more on page 458):

```
[root@t-degroot1 tom]# w
 10:29:33 up 17 min,  1 user,  load average: 0.00, 0.01, 0.03
USER     TTY      FROM             LOGIN@   IDLE   JCPU   PCPU WHAT
tom      pts/0    82.169.16.89     10:28    5.00s  0.02s  0.18s sshd: tom [priv] 
```

The three numbers show the average number of processes over the past minute, 5 minutes and 15 minutes. 

The load average is a fraction of the number of processors, thus:

1. With one processor a load average of 0.5 means over the past X minutes there was a process waiting to run 50% of the time.
2. With two processors a load average of 1 means over the past X minutes there was a process waiting to run 50% of the time. 

You can get the number of processors via `nproc` or `cat /proc/cpuinfo`

By default `batch` runs a job when the load average for 1 minute is lower than or equal to 1 minute. To change this:

`atrun -l N` -> change the load average to N and when the load average for 1 minute is equal to or drops below N, `at` will execute the batch job

####`atq` and `atrm`

Use `atq` (=atqueue) to view the pending jobs. The pending jobs are stored in */var/spool/at/*

Extra: 'spool' means a [temporary place to store data](https://techterms.com/definition/spool)

Use `atrm N` where N is the job number found via atq

###Restricting access:

1. if */etc/at.allow* exists and contain user names, only those users can create `at` or `batch` jobs
2. if */etc/at.allow* does not exists and */etc/at.deny* exists and contain usernames, the users who are in there cannot create `at` jobs
3. if both files are removed, only the root user can create `at` jobs

##Mail Transfer Agent

Even though some enitities in a mail chain are combined nowadays, the officel entities in the mail chain are:

1.Mail User Agent (MUA), is the client for receiving and sending mail. Sending mail to:
