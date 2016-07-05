#Managing File Permissions and Ownership#

##File/Directory Permissions and Owners##

`ls -l` output:

FILETYPE,USERPERMISSIONS,GROUPPERMISSIONS,ANYONEPERMISSIONS,NUMBEROFHARDLINKS,USER,GROUP
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

Set permissions on a file:
1. `chmod 555 filename` -> give the user, group and anyone r+x permission on filename
2. `chmod ugo+w filename` -> adds write permission to the user, group and other


