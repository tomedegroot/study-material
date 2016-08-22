#Managing File Permissions and Ownership#

##File/Directory Permissions and Owners##

`ls -l` output:

FILETYPE,USERPERMISSIONS,GROUPPERMISSIONS,OTHERPERMISSIONS,NUMBEROFHARDLINKS,USER,GROUP
drwxr-xr-x. 2 tom tom

d = dir
- = file
l = symobolic link
p = named pipe
s = socket
c = character file (serial stream of output)
b = block device (randomly accessible)

r = read (4)
w = write (2)
x = execute (1)

Octal permissions with rwx(421)
1. On dirs, x means we can cd into it.
2. On files, x means we can execute it.

Get octal permissions:
`stat -c "%a %n" FILE` 

Set permissions on a file:
1. `chmod 555 filename` -> give the user, group and anyone r+x permission on filename
2. `chmod ugo+w filename` -> adds write permission to the user, group and other (off course the minus (-) sign also works)
Before changing the permissions of a file, you need to be **user owner** or **root**. 

Changing ownership. This can [only be done by **root**.](http://superuser.com/questions/697608/chown-operation-not-permitted)
`chown username:groupname filename` or `chown username.groupname filename`
`chown username: filename` works as well. In that case user is username and the group is also username
