#Topic 107 Administrative Tasks

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
5. Comment field, usually the full name of user. I'm not sure what the maximum length for this field is, but try to keep it reasonable (under 30 characters).
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

*/etc/default/useradd* -> config defaults for adding a user

`useradd USER` -> add a user
  1. `-d HOMEDIR` -> set the path for the homedir. The default is to append the LOGIN name to the BASE_DIR
  2. `-m` -> Create home. useradd will do this automatically, unless CREATE_HOME in */etc/login.defs* is set to no
  3. `-k` -> Copy the contents of */etc/skel/* for the home dir. **IS DEFAULT**
  4. `-g GROUPNAME` -> Specify the primary group. By default a new group for the primary group will be created
  5. `-u UID` -> Specify the new UID. By default the next available UID will be given

Extra notes:

1. A new UID will be created with the next available UID.
2. A new group with same name and new GID will be created (unless `-g` flag is given) and this will be the new user's primary group.
3. The homedir for the new user will be copied from */etc/skel/*

####`usermod`

`usermod [OPTIONS] USER` -> modify users
  1. `-G GROUPNAME` -> add user to group
  2. `-U USERNAME` -> unlock a user's account
  3. `-L USERNAME` -> lock a user's account

####`passwd`

`passwd [OPTIONS] [USER]` -> set a password [FOR USER]
  1. `-l` -> lock a user's account
  2. `-u` -> unlock a user's account
  3. `-S` -> get status of a password
  4. `--stdin` -> read the password from stdin, example: echo "testPassword" | passwd --stdin user3

####`userdel`

`userdel USER` -> remove user
  1. `-r` -> remove the /home/USER dir as well
  Example: `userdel -r user`

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

####group passwords

Users can change their primary group temporarily via `newgrp [GROUPNAME]`. This opens a new shell.

With `gpasswd` a password can be given for a group. 

1. If this is done, everyone needs to enter this password if they want to change their primary group.
2. If this is not done, users who are a member of the group can change their primary group without giving a password. Other users cannot.

###`getent`

User `getent` to query for both local and network accounts:

`getent passwd tom`

