#Changes between MBR and GPT based partitions

MBR=Master Boot Record
GPT=GUID(Globally Unique Identifier) Partition Table

Legacy of the Master Boot Record:
1. MBR allows us to identify how and where to boot an OS
2. It's the first thing a BIOS loads
3. MBR is typically the first 512 bytes of the first sector. Overwriting this set of blocks can cause our system not to boot
4. Limited to 2TB disk size
5. Limited to four primary partitions

So Linux is moving from MBR to GPT because it can handle larger disk spaces.

1. fdisk allows use to manage a MBR
2. gdisk allows us to manage a GPT

#gdisk

(In gdisk the parition table is on the first 2048 bytes)

How to create a gdisk partition:

1. `gdisk DEVICEFILE` -> gdisk /dev/xvdf. Very similar to fdisk.

Everything else, making the filesystem and mounting it is al the same.

#ReiserFS and Btrfs File Systems

For the LPIC 101-1 we must have a general overview of the ReiserFS and Btrfs

##ReiserFS

1. General purpose FS
2. Supported by all major filesystems

+ Journaled; but only metadata
+ Better performance with small files than ext2/3 (smaller than 4kb)

- Does not support quotas

##BtrFS

Stands for B-tree File System

+ Highly scalable
+ Self healing filesystem (copy on write; it keeps one file for multiple usages and if one usage is changed, only then it creates a copy. But under the hood the multiple usages are only saved once (much like dropbox))
+ Create snapshots

#Using parted

Use parted to create a gpt based partition

Broken video

#Logical Volume Manager (LVM)

You only need a conceptual understanding, not a technical understanding

A logical volume is an abstraction over physical disks and can span multiple physical disks. A physical disk can only belong to one volume group:

```
	Logical Volume
		^
		|
	Volume group
	^		^
	|		|
	Physical	Physical
	Volume		Volume
```

Physical volumes can be added to the volume group while the volume group is used. This make it possible to have **online data relocation**. Remove a physical volume, give it a different parition scheme(MBR to GPT) and add it back to the volume group)

If large amounts of data is send, the data can be split between physical data to **increase throughput*

It can create **snapshots of the data for backups**
