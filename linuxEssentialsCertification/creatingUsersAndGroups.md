#Creating Users and Groups#

##User ID's (UID)##

Humans use user names to login. The Linux system (processes, file permissions) use the UID. This can cause problems when a user is removed from a system and the UID gets reassigned to another user.

[Info on the wheel group](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux_OpenStack_Platform/2/html/Getting_Started_Guide/ch02s03.html)

1. `id USER` -> get info on a user
2. `groups USER` -> see of which groups a user is a member
