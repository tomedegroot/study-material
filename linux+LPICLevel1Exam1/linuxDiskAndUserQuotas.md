#Disk Quotas Preparation

Note: the quota tools described here only work for an ext2 filesystem, not a xfs filesystem

##quota

You may need to install `quota` first if it is not installed by default:

`yum install quota`

##We need to alter */etc/fstab*

Add `usrquota,grpquota` options to setup usrquotas and grpquotas

```
#
# /etc/fstab
# Created by anaconda on Mon Sep 29 21:48:54 2014
#
# Accessible filesystems, by reference, are maintained under '/dev/disk'
# See man pages fstab(5), findfs(8), mount(8) and/or blkid(8) for more info
#
UUID=0f790447-ebef-4ca0-b229-d0aa1985d57f /                       xfs     defaults,usrquota,grpquota        1 1
```

##We need to create /aquota.group and /aquota.user and set right permissions

```
touch /aquota.{user,group}
chmod 600 /aquota.{user,group} 
```

Only read access for the root owner

##remount the filesystem

`mount -o remount /`

##use quotacheck

`quotacheck [OPTIONS] MOUNTPOINT`

1. `-a` -> all filesystems, so you don't have to specify filesystem
2  `-v` -> be verbose
3. `-u` -> check user quotas
4. `-g` -> check group quotas
5. `-m` -> don't try to remount filesystems

#Setup User Quotas

##edquota

Edit the user's quota:

`edquota USERNAME`. Example file:

```
Disk quotas for user quotauser (uid 1003):
  Filesystem                   blocks       soft       hard     inodes     soft     hard
  /dev/xvdf1                        0          0          0          0        0        0
```

Set the max space to 100k:

`edquota quotauser` and enter:

```
Disk quotas for user quotauser (uid 1003):
  Filesystem                   blocks       soft       hard     inodes     soft     hard
  /dev/xvdf1                        0          0        100          0        0        0
```

##repquota

Report a user's quota

`repquota [OPTIONS] [MOUNTPOINT]*`

1. `-v` -> see repquota for all users. By default shows only the current user
2. `-s` -> human readable

If the mount point is not given, `repquota` will list report the status of the quotas for all filesystems in Debian based system. On RedHat based, this will cause an error.

Warnings and errors when disk quotas are exceeded cause the filesystem in question to lock, preventing all write activity for the user exceeding their quota.
