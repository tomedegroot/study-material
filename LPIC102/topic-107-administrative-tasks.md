#Topic 107 Administrative Tasks

##Basic User Management For Fresh Images/Server Installs

###User Account Fundamentals

Core info on UID:

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
3. Numeric user id. This is assigned by the `adduser` script. Unix uses this field, plus the following group field, to identify which files belong to the user.
4. Numeric group id. Red Hat uses group id's in a fairly unique manner for enhanced file security. Usually the group id will match the user id.
5. Full name of user. I'm not sure what the maximum length for this field is, but try to keep it reasonable (under 30 characters).
6. User's home directory. Usually /home/username (eg. /home/smithj). All user's personal files, web pages, mail forwarding, etc. will be stored here.
7. User's "shell account". Often set to `/bin/bash` to provide access to the bash shell (my personal favorite shell).

####*/etc/group*

*/etc/group stores group info.

After `[root@t-degroot1 tom]# usermod -a -G user tom`, the file looks like:

```
user:x:1001:tom
...
tom:x:1002:
```

Contents of */etc/group*

1. group_name
2. password
3. GID
4. group list of users who are a supplementary member of the group (See point 4 of */etc/passwd* to find the primary member of a group)

`groups [USERNAME]` -> get the groups of the USERNAME, USERNAME defaults to current user.

####`getent`

User `getent` to query for both local and network accounts:

`getent passwd tom`

####Special Login Files

1. */bin/false* -> if the user's shell is set to this, he cannot login
2. */sbin/nologin* -> if the user's shell is set to this, he cannot login and a message will be displayed that the account is unavailable. If */etc/nologin.txt* exists, the contents of that file will be displayed.
3. */etc/motd* -> after a succesful login, the message of */etc/motd* is displayed (motd = message of the day)
4. *~/.hushlogin -> if in the user's home dir, the loging process is changed and:
  1. No mail check will be done
  2. Do not display information of the last login
5. */etc/login.defs* -> This file defines specify defaults for the `useradd` command. (What about /etc/default/useradd)

###Adding, modifying and deleting users

####`useradd`

*/etc/default/useradd* -> config defaults for adding a user

`useradd USER` -> add a user
  1. `-d HOMEDIR` -> set the path for the homedir. The default is to append the LOGIN name to the BASE_DIR
  2. `-m` -> create home. useradd will do this automatically, unless CREATE_HOME in */etc/login.defs* is set to no

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

####`su` & `sudo
`
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


