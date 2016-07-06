#Special Directories And Files#

##Symbolic Link##

Create a pointer(shortcut) to an actual filename. Since it is a pointer, changes to the link will also change the original value. It is a reference.
`ln -s TARGET LINK_NAME`

Why would we want a symbolic link?
1. Do not have to type the full (sometimes) long location
2. As with both [composer](https://github.com/composer/composer) & [npm](https://www.npmjs.com/) you can place symbolic link to the bins of different packages in one location.

Difference between symbolic and hard link:
A symbolic link links to another file name, hard link points to the inode (contents) of the file. See [this](http://askubuntu.com/questions/108771/what-is-the-difference-between-a-hard-link-and-a-symbolic-link) & [this](http://stackoverflow.com/questions/185899/what-is-the-difference-between-a-symbolic-link-and-a-hard-link) for more information.

##System files, Special Files and Sticky Bits##
