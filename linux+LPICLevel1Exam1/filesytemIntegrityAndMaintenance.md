#du, df and mount

These tools will allow us to explore the sizes of files, directories and partitions on our Linux system. We will use them to view statistics in various formats and to obtain other file information such as the number of inodes.

##du

Get the disk usage of a file.

`du [OPTIONS] [FILE]`

1. How to get all the info of the current dir? -> `-a` by default du only shows dirs
2. How to get info in human readable format? -> `-h`
3. How to get a summary of all the info? -> `-s`; summary means to not traverse into dirs. THerefor `-a` and `-h` are incompatible
4. How to exclude patterns our display? -> `--exclude=PATTERN`

[FILE] is by default the current dir (.), just as with ls

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

#dumpe2fs and tune2fs

##dumpe2fs

How to dump ext2/ext3/ext4 filesystem information? -> `dumpe2fs [OPTIONS] FILESYSTEM`

*Uses the same system binaries as the debugfs application

##tune2fs

How to tune a filesystem? -> `tune2fs [OPTIONS] FILESYSTEM`
1. How to set a label? -> `-L NEWLABEL`
2. How to adjust the number of mounts after which the filesystem will be checked (via `e2fsck`)? -> `-c NUMBER`
3. How to set the current number of mounts? -> `-C NUMBER`; If set to a greater value than the max-mount-counts parameter set by the -c option, e2fsck(8) will check the filesystem at the next reboot.
4. How to set the interval between checks in days|weeks|months? -> `-i NUMBERd|w|m`

**mnemonic**: Capital -C is for the longest parameter: current number of mounts, and smaller -c is for the smaller word check 

#xfs

XFS is an older file system. Ext2/4 is now more in common.

##xfsdump

`xfsdump -J MOUNTPOINT` -> create a dump of the filesystem

@todo take a look at xfs_dump and xfs_restore. Just create a new xfs, do the dumping and copying. (Max 5 minutes)

**Mind you** Create a new xfs file system to do all the tests. Don't use the one mounted on */*

#Disk Partition Schemes

It's easier to set your disk layout at installation than afterwards. So built in flexibility.

#How to get a label and uuid of your device files?

3 ways:

1. `lsblk -o label,uuid,name`
2. `ls -al /dev/disk/by-uuid >> file.out && ls -al /dev/disk/by-partlabel >> file.out`
3. `blkid`

#How to resize a partition table?

To make a partition smaller:
1. Resize the filesytem -> [via resize2fs](https://access.redhat.com/articles/1196333)
2. Resize the partition -> [via fdisk](https://access.redhat.com/articles/1190213)
  1. Delete existing partition
  2. Create smaller partition of the same size as the resized filesystem; tip: use human readable sizes.
3. After resizing the partition use `fsck`

To increase a partition size, just do step 1 as the last step

