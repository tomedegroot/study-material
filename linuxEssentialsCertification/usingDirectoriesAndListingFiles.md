#Using dirs and listing files#

##The Linux File System##

File system is used to control how data is stored and retrieved on a storage device.

Requirements:

1. Data is organized and easily located
2. Data can be saved in a persistent manner
3. Data integrity is preserved
4. Data can quickly be retrieved for a user in a later point in time

It shouldn't matter if it is a hard disk, usb-stick or cloud storage.  

In reality there are more disk file systems. These disk file systems are implementations of specific file systems.

Linux has the file system hierarchy standard (FHS). This means:
1. Hierarchy to structure data. At the top is root(/).
2. Linux systems have standard where the root dir has certain sub dirs in a certain order.

In FHS one can expect amongst others the following under */*:

1. /bin -> contains binaries such as cp and rm
2. /boot -> contains boot loader files necessary for booting
3. /dev -> files that represent hardware
  1. Character orientated device files: devices that receive or send characters sequentially (such as printers and mice)
  2. Block orientated device files: device that manage data in blocks, such as your hard drive or your usb-drive.

Remember: when you interact with hardware you do that via the interface /dev/particularDevice represents.
4. /etc -> text based Config files and services running on our system.
  1. /etc/aliases -> Contains a table to redirect all local users
  2. /etc/exports -> Configured file systems to be exported to remove NFS clients
  3. /etc/fstab -> List partitions and file systems that will be automatically mounted
  4. /etc/ftpusers -> Controls users access to ftp service running on a linux file system
  5. /etc/group -> Contains local group definitions.
  6. /etc/grub.conf -> Contains config parameters for the init process
  7. /etc/hosts -> This contains a list of hostname to IP Address mappings for resolving hostnames.
  8. /etc/inittab -> Contains config params for init process
  9. /etc/init.d -> Subdir containing startup scripts and services
  10. /etc/rc.d/init.d/ -> Red Hat or CentOS based startup scripts
  11. /etc/passwd -> Users accounts file
  12. /etc/shadow -> Contains encrupted passwords for user accounts
  13. /etc/resolv.conf -> Contains DNS server and domain suffix
  14. /etc/X11 -> Contains X Window config files
5. /home -> Contains subdirs that are the home dirs for the users, for example: /home/tom
6. /lib -> Contains code libs used by programs
7. /media -> Used by some distro's to mount external devices
8. /mnt -> Used by some distro's to mount external devices
9. /opt -> Optional, files for programs you can install manually
10. /proc -> Interface for accessing processes
11. /root -> Root user's home dir
12. /sbin -> Similiar to bin, this contains **system** management files. Example ifconfig, init, shutdown etc.
13. /srv -> Services(Apache) save their files here
14. /sys -> Contains information on the hardware in our system
15. /tmp -> Contains temporary files
16. /usr -> Contains application files. Anything in here is [non-required](http://unix.stackexchange.com/questions/5915/difference-between-bin-and-usr-bin) for linux

  1. /usr/bin -> Binaries
  2. /usr/lib -> Libraries
  3. /usr/lib64 -> 64 bit libraries
  4. /usr/local -> Locally installed software
  5. /usr/sbin -> System admin binaries
  6. /usr/share -> Documentation
17. /var -> Variable data such as log files

Linux Disk File System is responsible for the reliability of storing data on a hard drive and making it retrievable. Different formats:
1. ext2 = Second Extended File System (1993), stores data in standard hierarchical way of dirs and files. Most widely used. Fast. Aspects:
  1. Max files size = 2 Terabyte
  2. Max volume = 4 Terabyte
  3. Max filename = 255 bytes
  4. Supports Linux Files System Groups and Users
  5. Supports compression
  6. Must check entire file system if the system goes down uncleanly (power outage) not properly unounting the file system
2. ext3 = Updated version of ext2. Ext2 is upgradeable to ext3 and ext3 is downgradeable to ext2. Key advantage of ext3 is journaling. Ext3 uses the journal to check the integrity of the files thus not having to check the entire file system. Ext3 only checks those transactions which are not marked as completed in the journal. Thus ext3 takes a few seconds where ext2 takes hours.
3. Reiser = Also uses journaling, but completely different internal structure that ext2. This allow larger file sizes, such as 8 TB and max volume of 16 TB. And it is faster.
4. ext4 = Updated version ext3. Supports files up to 16 TB and volumes of up to 1 Exabyte. Maximum of  billion files on a system. Also uses checksums to check the journal file.

##Files, Dirs##

For navigation:
1. `pwd` -> print working dir
2. `cd [dir]` -> change working dir to dir. 
  1. Without `[dir]` argument ->  go to ~
  2. `.` -> current dir
  3. `..` -> up one dir
  4. `../..` -> up two dir
3. `ls` -> list content of dir
  1. `-a` -> show all files, including hidden files
  2. `-l` -> long, give type and rights on files
  3. `-R` -> Recursive, pipe to `more` to be able to read better
 
##Hidden files and dirs##

Files or dir that is prefixed with a '.' is hidden. The hidden files are only shown by the ls with `ls -a`

##Home##

Configs in the home folder take precedence over system wide configs. The user has complete control of his home dir. 

The FHS says that home is a site specific file system, but suggests */home/username*

##Absolute and relative paths##

Relative from the working dir.
Absolute from the root path, prefix with the root dir (/)


