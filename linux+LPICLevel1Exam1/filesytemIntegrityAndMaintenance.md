#du, df and mount

These tools will allow us to explore the sizes of files, directories and partitions on our Linux system. We will use them to view statistics in various formats and to obtain other file information such as the number of inodes.

##du

Get the disk usage of a file.

`du [OPTIONS] [FILE]`

1. How to get all the info of the current dir? -> `-a`
2. How to get info in human readable format? -> `-h`
3. How to get a summary of all the info? -> `-s`; summary means to not traverse into dirs. THerefor `-a` and `-h` are incompatible
4. How to exclude patterns our display? -> `--exclude=PATTERN`

##df

Get the disk usage of a filesystem?

`df [OPTIONS] [FILE]`
1. How to get all info, including dummy filesystems? -> `-a`
2. How to get info in human readable format? -> `-h` (By default it will always be in K)
3. How to get the filesystem type? -> `-T`

#fsck and e2fsck

##fsck

Check file system **on an unmounted** filesytems. If you try it on a mounted filesystem it will result in an error.

`fsck [OPTIONS] DEVICEFILEORMOUNTPOINT`
1. How to Automatically fix errors? -> `-a`
2. How to check All filesystems in */etc/fstab* -> `-A`
3. How to prevent execution, but just show filesytem status? -> `-N`

*If you specify the MOUNTPOINT instead of the DEVICEFILE, then the MOUNTPOINT must be configured in /etc/fstab

##e2fsck

Does exactly the same as fsck, but:

1. Only for ext2/3/4 filesystems
2. You cannot specify the mount point, you need to specify the device file

#mkfs, mkefs and debugfs

##mkfs

(Is a frontend tool for other make file system tools)[http://litux.nl/Reference/books/7213/ddu0222.html]

How to make a file system? -> `mkfs [OPTIONS] [FILESYSTEMOPTIONS] DEVICE`

OPTIONS:

1. `-t FSTYPE` -> defaults to ext2

##mke2fs

Make ext2 filestem: `mkefs OPTIONS`

1. How to specify the type of extended filesytem? `-t EXTENDEDFSTYPE`
2. How to set the volume label? -> `-L VOLUMELABEL`

This volume label is stored in the superblock. [More info on the superblock](https://www.cyberciti.biz/tips/understanding-unixlinux-filesystem-superblock.html)

##debugfs

Interactive program to debug a filesystem

`debugfs [OPTIONS] DEVICEFILE`

1. How to allow writing to the filesystem? -> `-w`

Interactive options:

1. `help` -> Get help
2. `q` -> Quit
3. `lsdel` -> list deleted inodes. **only works with ext2**
4. `undel INODENUMBER`
