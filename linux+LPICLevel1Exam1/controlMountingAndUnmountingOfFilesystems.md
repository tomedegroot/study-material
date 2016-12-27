#How To Create a Linux Academy Disk Volume

Create a volume for your server in the server tab. This simulates attaching a device to a linux system.

#Creating and Mounting A Disk Partition

A device file can only be mounted on /dev as a device file, a file system can be mounted on a mount point in the file system. Thus the order is:

1. Device file
2. File system

@todo: how can a file system be on both /xvdf and /xvdf1 ?

How to access device files:

1. Create a file system on a device. Device files can be accessed in via */dev/**
2. Mount the partition with file system on a mount point

##file systems

1. What is the original native Linux file system? -> ext2fs (second extended file systems, native for Linux)
2. What is the followup on ext2fs and how is it different? -> ext3fs (ext3 is like ext2, but it has journaling)
3. What is journaling? -> Whenever a change is made to the file system an entry to the journal is made. This acts as a log/backup to help restore your system
4. What is the followup on ext3fs and how is it different? -> ext4fs (Necessary to handle drives of 32TB and files of 2 TB)

How to get file system info? -> `df OPTIONS`

OPTIONS:

1. `-t` -> get the type of file system
2. `-h` -> get info in human readable format

##mkfs

How to make a file system? -> `mkfs [OPTIONS] [FILESYSTEMOPTIONS] DEVICE`

OPTIONS:

1. `-t FSTYPE` -> defaults to ext2

FILESYSTEMOPTIONS:

These are depended on the file system

1. `-m PERCENTAGE` -> ext leaves reserved space of 5% by default. This is reserved for if the file system is full and the system crashes. Than you can easily use this 5% to get the system running while finding a permanent fix.
2. `-c` -> Perform a bad block check. Is handy for old drives to prevent the drive going bad.

##mounting and unmounting

`mount DEVICE MOUNTPOINT`

`umount MOUNTPOINT`, if the device is busy you cannot unmount

#Using `fdisk`, crating a file system and */etc/fstab*

##fdisk

How to manipulate a disk partition table? -> `fdisk [OPTIONS] DEVICEFILE`

Interactive options:

1. How to save your changes to the disk? -> `w` (for Write table to disk) 
2. How to add a new partition? -> `n`

After saving your changes with `-w`, you need to create a new file system on the partition
