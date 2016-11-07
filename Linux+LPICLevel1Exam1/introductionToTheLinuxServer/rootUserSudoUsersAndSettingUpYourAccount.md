#Root User, Sudo Users And Setting Up Your User Account

1. `su` -> become another user
  1. Called without arguments defaults to root user 
2. `sudo` -> execute command as another user
  1. Set user -u, defaults to root
3. */etc/passwd* -> file which contains user info
4. */etc/sudoers* -> file which contains the sudo policy
  1. See: ```## Allows people in group wheel to run all commands
%wheel	ALL=(ALL)	ALL``` In CentOS, all the users in the wheel group have sudo privilege. This differs per distribution.
5. `visudo` -> command to alter the */etc/sudoers* file. visudo checks the **syntax** of */etc/sudoers* before overwriting it.
6. `usermod [OPTIONS] USER` -> modify users
  1. `-G [groupname]` -> add user to group
7. `groups USER` -> see the groups of which the USER is a member

8.06
