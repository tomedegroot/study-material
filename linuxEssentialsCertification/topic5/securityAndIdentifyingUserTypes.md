#Basic Security and Identifying User Types#

##Root and Standard Users##

###Basic info###

Linux is designed for multiple users. Multiple users shouldn't be able to access each other's files and each user should have it's own environment. Linux achieves this by using:

1. Users
2. Groups
3. Ownership
4. Authentication
5. Permissions

Handy tools relating to users:

1. `finger [USER=current-user]` -> Get info on user
2. `id [USER=current-user]` -> Get user id

Where are the Linux account stored within the Linux File System?

1. */etc/passwd* -> here accounts are stored. Is used for local authentication. Gives you USERNAME:PASSWORD(LEGACY FIELD,NOW IN */etc/shadow*):USERID:GROUPID:$HOME:$SHELL
2. */etc/shadow* -> stores the encrypted passwords, linked to */etc/passwd* 
3. */etc/group* -> stores group info (see next lesson)

Recommended to not edit these files directly, but to use the user management tools (next lessons). Basic operations can be done with:

1. pwck -> verify integrity of password files
2. pwconv -> convert to and from shadow passwords and groups

###Root###

The super user is the root user. Enables you to perform administrative tasks. These tasks usually require you  to work with files regular users cannot read. The root user can read and write any file on the Linux file system. The mechanism with the root user is also a defensive mechanism for accidental mistakes.

How to become root?

1. Log in as root
2. `su [USER=root]` -> substitute user, but keep own $PATH
  1. `- ` -> substitute user and get $PATH of user
3. `sudo` -> execute one command as root (add user to the sudo group to add to the sudoers file)

1. `w` -> info on current logged on users.
2. `who` ->
  1. `-b` -> last boot time of machine
  2. `-m` -> host name and user associated with it
  3. `-r` -> run level for user
  4. `-q` -> number of logged on users
  5. `-a` -> all info at once
3. `last [USER=current-user]` -> shows recent activity of a user

###System Users###

System user accounts are not used for users to login, but are used by the services that are running on our system. The system user's id is always lower than 1000. 
