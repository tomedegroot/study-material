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

##*/etc/fstab*

Check the device notes for how the file works.

Example of /etc/fstab:

```
#
# /etc/fstab
# Created by anaconda on Mon Sep 29 21:48:54 2014
#
# Accessible filesystems, by reference, are maintained under '/dev/disk'
# See man pages fstab(5), findfs(8), mount(8) and/or blkid(8) for more info
#
UUID=0f790447-ebef-4ca0-b229-d0aa1985d57f /                       xfs     defaults        1 1
/root/swap swap swap sw 0 0 
```

Syntax: device mountpoint filesystem options dump fsck
1. Device: Can mount by  le name, disk UUID or network drive
2. Mount point: Should usually be an empty directory
3. File system: What type of  le system is being mounted; auto tells kernel to auto-detect
4. Options: Tell kernel how to treat mounted system. Comma seperated with following options or set all the defaults by just specifying `defaults`:
  1. uid: Set owner of disk
  2. umask: Set umask
  3. noauto: Do not automatically mount drive  
  4. exec: Execute binaries on  le partition
  5. ro: Read only
  6. rw: Read and write
  7. user: All normal users to mount disk
  8. nofail: (add to let fsck skip non-existent device (source)[http://techmonks.net/nofail-and-nobootwait-mount-options-in-fstab-prevent-boot-problems/]) 
5. Dump: Set to 1 to backup partition
6. fsck: Determine order for  le system check

Extra info on nofail option:

```
fsck normally does not check whether the device actually exists before calling a file system specific checker. Therefore non-existing devices may cause the system to enter file system repair mode during boot if the filesystem specific checker returns a fatal error. The /etc/fstab mount option nofail may be used to have fsck skip non-existing devices. fsck also skips non-existing devices that have the special file system type auto
```


##how is */etc/fstab* used?

1. The kernel will try to mount the device in /etc/fstab at bootup which do **not** have the noauto options
2. With `mount -a` you mount all the devices listed in */etc/fstab*
3. You can no mount via `mount FILESYSTEM`. `mount` will look up the where to mount in */etc/fstab*

#Working With Swap And Linux Page File

The physical memory is broken up into pages. When the physical memory runs out, Linux stores (the less important) pages into swap.

Swap is storage space which usually lives on the hard drive, but it can also be on an external drive. Off course, the hard drive is slower than memory and an externel drive would be slower than the hard drive.

(The Linux Academy CentOS and Debian server have swap space by default.)

##Setting up swap

1. Create a file: `dd if=/dev/zero of=~/swap.swp bs=1024 count=800k` -> 800 megabyte file. (bs of 1024 is 1K. For the `dd` command, you could also have specified the option as `bs=1K`)
2. Set up the device or file as a swap file: `mkswap DEVICE/FILE`
3. Use the `swapon` command to turn the swap file on:

`swapon` and `swapoff`

1. How to get info? -> `swapon -s`; **mnemonic** Summary
2. How to turn swap **on** for a device/file? -> `swapon SWAPFILE`
3. How to enable all swap? -> `swapon -a`
4 .How to turn swap **off** for a device/file? -> `swapoff SWAPFILE`
5. How to disable all swap? -> `swapoff -a`

4. Check the total swap space using the `free` command