#Topic 107 Administrative Tasks

Important for exam:

1. The user commands (not so much the group ones)
2. */etc/shadow*

##Basic User Management For Fresh Images/Server Installs

###Users

Info on UID:

1. **0** is for the root user
2. **1** is for bin user (system binaries and non-login accounts)
3. **48** is for the apache user
4. **99** is the nobody account
5. **0 - 499** are system users

####*/etc/passwd*

The users are stored in the /etc/passwd file. This file maps the UID to the user name. Structure of the file:

```
smithj:x:561:561:Joe Smith:/home/smithj:/bin/bash
```
Each field in a passwd entry is separated with ":" colon characters, and are as follows:

1. Username, up to 8 characters. Case-sensitive, usually all lowercase
2. An "x" in the password field. Passwords are stored in the */etc/shadow* file.
3. Numeric UID. This is assigned by the `adduser` script. Unix uses this field, plus the following group field, to identify which files belong to the user.
4. Numeric GID. Red Hat uses group id's in a fairly unique manner for enhanced file security. Usually the group id will match the user id.
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
  1. `-d HOMEDIR` -> set the path for the homedir. The default is to append the LOGIN name to the BASE_DIR
  2. `-m` -> Create home. useradd will do this automatically, unless CREATE_HOME in */etc/login.defs* is set to no
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
5. Maximum: The maximim the days before the password must be changed (no value, so it doesn't need to change)
6. Warning: The number of days before the password epires (field 5) when the user will be warned (The check is if WARNING_DAYS > (MAX-DAYS-(CURRENT_DAY-LAST_CHANGE)), so greater than)
7. Inactive: The number of days after the password has expires that the user can still log in and then change the password immediately (no value)
8. Expiration date: The number of days after the epoch after which the passwold will expire

The permissions difference (**know this for the exam**):

*/etc/passwd*:

Red Hat: `-rw-r--r--. 1 root root 1882 Feb  6 20:56 /etc/passwd`
Debian:  `-rw-r--r-- 1 root root 1719 Jan 17 08:10 /etc/passwd

*/etc/shadow*:

Red Hat: `----------. 1 root root 1173 Feb  7 07:38 /etc/shadow`
Debian:  `-rw-r----- 1 root shadow 1116 Jan 17 08:10 /etc/shadow`

####Aging passwords

`chage [OPTIONS]` -> change user password information (**mnemonic**: change age). This command changes the fields in */etc/shadow*

1. `-m MIN_DAYS` -> change Min value
2. `-M MAX_DAYS` -> change Max value 
3. `-d LAST_DAY` -> change last change value
4. `-E EXPIRATIONDATEINYYYY-MM-DD` -> change expiration date
5. `-I INACTIVE_DAYS` -> change the inactive days
6. `-W WARN_DAYS` -> change the warning days
7. `-l` -> list info

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
