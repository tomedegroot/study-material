#Special Directories And Files#

##Symbolic Link##

Create a pointer(shortcut) to an actual filename. Since it is a pointer, changes to the link will also change the original value. It is a reference.
`ln -s TARGET LINK_NAME`

Why would we want a symbolic link?
1. Do not have to type the full (sometimes) long location
2. As with both [composer](https://github.com/composer/composer) & [npm](https://www.npmjs.com/) you can place symbolic link to the bins of different packages in one location.

Difference between symbolic and hard link:
A symbolic link links to another file name, hard link points to the inode (contents) of the file. See [this](http://askubuntu.com/questions/108771/what-is-the-difference-between-a-hard-link-and-a-symbolic-link) & [this](http://stackoverflow.com/questions/185899/what-is-the-difference-between-a-symbolic-link-and-a-hard-link) for more information.

##System files, Special Files/Dirs and Sticky Bits##

Special dirs and files:

1. */var* -> contains files that change often such as mail, logs etc.
2. */tmp* -> contains temporary files that **do** get deleted on  reboot.
3. */var/tmp* -> contains files that **do not** get deleted on reboot.

The */tmp* and */var/tmp* folder have special rules concerning permissions. 

1. Every Linux user can write to */tmp*. That means other users can delete files within the */tmp* folder. 
2. All programs write their temporary files to the */tmp* folder, because these temporary files are being written as the programs are being executed.

Caveat: all the files in */tmp* have 777 permissions. This means users can delete other user's files. How to solve this?

Sticky bit->A folder with a sticky bit ensures that files and folders within the folder with the sticky bit can only be deleted by the owner, even if the permissions on the file are 777.

`chmod o+t FILE` -> example: `chmod o+t /sticky`

After this, when you do `ls -l` The last symbol of the permission string is a 't'. This means any files within the folder with sticky bit can only be deleted by the user who created the file.

You can set the sticky bit via a fourth octet before the regular octets in `chmod`:
`chmod 0777 sticky` -> sticky bit is off
`chmod 1777 sticky` -> sticky bit is on

REMEMBER:
Without the sticky bit set, any user with write and execute permissions for the directory can rename or delete contained files, regardless of the file's owner.

In other words, if you have write access to a dir, but not the file in the dir (*/dir/file*), then you can still the delete the file since you have write access to the dir
