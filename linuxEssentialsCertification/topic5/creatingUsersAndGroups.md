#Creating Users and Groups#

##User ID's (UID)##

Humans use user names to login. The Linux system (processes, file permissions) use the UID. This can cause problems when a user is removed from a system and the UID gets reassigned to another user.

[Info on the wheel group](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux_OpenStack_Platform/2/html/Getting_Started_Guide/ch02s03.html)

1. `id USER` -> get info on a user
2. `groups USER` -> see of which groups a user is a member

##User Commands##

Some utilities to manage users ([useradd and adduser](http://askubuntu.com/questions/345974/what-is-the-difference-between-adduser-and-useradd)):

`adduser USERNAME` -> add user with default values. See default values for new user in */etc/default/useradd*
  1. `-d` -> get the default values from */etc/default/useradd*
  2. `-c` -> comment, useful to state the user's real name
  3. `-e` -> expire date for the account
  4. `-f` -> number of days after a password expires until the account is disabled
  5. `-g` -> specify user's defaul group
  6. `-G` -> additional groups for the user
  7. `-M` -> no home dir
  8. `-m` -> set home's dir
  9. `-p` -> specify the encrypted password. Better to create without a password and then use `passwd USERNAME` to prevent the password showing up in the processes. By default a password is not created and the account is locked. You can see this with `passwd -S USERNAME`
  10. `-r` -> create a system user, thus user id with low number
  11. `-s` -> specify the default shell for the user
  12. `-u` -> numerical value of the user's ID
2. */etc/login.defs* -> config for shadow password. Has values for the system of adding users.
3. */etc/skeleton* -> default values to be copied to a new user's home dir

Example of adding a user:
`adduser -c "Stephen Smith" -m -s "/bin/bash" ssmith`

`passwd [OPTIONS] USERNAME` -> set or change a password for a user
  1. `-S` -> get status of password
  2. `-l` -> lock an account
  3. `-u` -> unlock an account
  4. `-d` -> delete a password. **not recommended**, possible to login without a password
  5. `--stdin` -> read the password from stdin, example: echo "testPassword" |  passwd --stdin user3
  6. `w` -> warning prior to password expiration

`usermod [OPTIONS] USERNAME` -> manage existing users
  1. `-a` -> add user to a group. Example: `usermod -a -G accounting tony`. Remember, after a user is added to a group, the user must [logout and login again](http://stackoverflow.com/questions/5054888/linux-why-cant-i-write-even-though-i-have-group-permissions) 
  2. `-c` -> modify password's file (*/etc/passwd*) comment on the user (usually the user's real name)
  3. Multiple options the same as in `useradd`

`userdel USERNAME` -> deletes a user, **but** not the user's home dir
  1. `-r` -> deletes the home dir and mail spool of the user with it

##Group Commands##

Makes life as an administrator easier. If multiple users want to access the same files on a system, we can make that easier by using groups. We then only have to manage the group rights.

*/etc/group* -> defines the groups. In this file, you can delete a user from a group.
*/etc/gshadow* -> shadow file for the groups ([info on passwords for groups](http://meinit.nl/a-group-password-in-linux))

1. `groupadd [OPTION] GROUPNAME`
  1. `-g` -> specify group ID
  2. `-p` -> specify password for a group
  3. `-r` -> create system group
2. `groupmod [OPTION] GROUPNAME`
3. `groupdel GROUPNAME` -> delete a group
