#Lecture: Basic User Management For Fresh Images/Server Installs

(Note to self, `tom` is the user)

1. `su` -> Substitute user. Without any ARGUMENTS substitute to root
2. `useradd USER` -> add a user
3. `passwd [USER]` -> set a password [FOR USER]
4. `userdel` -> remove user
  1. `-r` -> remove the /home/USER dir as well
     * Example: `userdel -r user`

