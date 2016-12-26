#`which` and `whereis`

Commands to find info on other Linux commands

##`whereis COMMAND`

Only searches for binary files and man page dirs.

##`which COMMAND`

Only searches within $PATH  and shows the first result in the path

#locate 

`locate PATTERN`

Not installed by default on every linux distro

Why use locate? - search for files and dirs from a database (so it's quicker.)

What is the downside -> the database only updates once an hour, but you can update the database directly via updatedb

##updatedb.conf file

Why is `updatedb used` -> to create a database used by locate.

Where is the `updatedb` config file? -> */etc/updatedb.conf*, the output looks like:

```
PRUNE_BIND_MOUNTS = "yes"
PRUNEFS = "9p afs anon_inodefs auto autofs bdev binfmt_misc cgroup cifs coda configfs cpuset debugfs devpts ecryptfs exofs fuse fuse.sshfs fusectl gfs gfs2 gpfs hugetlbfs inotifyfs iso9660 jffs2 lustre mqueue ncpfs nfs nfs4 nfsd pipefs proc ramfs rootfs rpc_pipefs securityfs selinuxfs sfs sockfs sysfs tmpfs ubifs udf usbfs"
PRUNENAMES = ".git .hg .svn"
PRUNEPATHS = "/afs /media /mnt /net /sfs /tmp /udev /var/cache/ccache /var/lib/yum/yumdb /var/spool/cups /var/spool/squid /var/tmp"
```

Prune means (removing sections of decision trees), so PRUNE in the config means removing entities from the updatedb.

What is PRUNE_BIND_MOUNTS? -> A bind mount is not a device, but a path that is mounted into another path. [More info](http://backdrift.org/how-to-use-bind-mounts-in-linux) and [see practical use cases](http://backdrift.org/how-to-use-bind-mounts-in-linux). This means skip bind mounts.

What is PRUNEFS? -> Skip certain file system types

What is PRUNENAMES? -> Skip certain file extension

What is PRUNEPATHS? -> Skip certain paths in the file system 

See here a summary of all the [PRUNE* variables](http://manpages.ubuntu.com/manpages/xenial/man5/updatedb.conf.5.html)

#find

How to search within a dir tree? -> `find`

`find [OPTIONS] [PATH]... [EXPRESSION]`

Where [EXPRESSION] is made up of: [OPTIONS] [TESTS] [ACTIONS]. In:

`find / -name test`, the [PATH] = */*, the [EXPRESSION] = `-name test` where `-name test` = [TEST]

Every test in [TESTS] works like a filter

##[TESTS] -name

Example: `find / -name *.c`

Example:

```
[root@t-degroot1 etc]# cd /etc
[root@t-degroot1 etc]# find . -name 'cron*'
./systemd/system/multi-user.target.wants/crond.service
./cron.monthly
./cron.hourly
./cron.weekly
./crontab
./sysconfig/crond
./cron.d
./cron.deny
./selinux/targeted/modules/active/modules/cron.pp
./selinux/targeted/active/modules/100/cron
./pam.d/crond
./cron.daily
```

##[TEST] -user or -group

How to search by the owner or group of a file? -> `find . -user tom` or `find . -group root`

##[TESTS] -maxdepth

How many dirs deep do you want to go? `find . -maxdepth 0`

Where:

1. `maxdepth 0` is only 1 file which is the current dir itself and 
2. `maxdepth 1` is the content of the current dir

##[TEST] -type

Filter by file type (File, Dir, Link)

Example: `find . -type f`

##[TEST] -size

Example: `find . -size 2M` -> search for files which take **exactly** n units of space

1. Variation: `-size +1M` -> search files which are bigger than 1 Megabyte
2. Variation: `-size -1M` -> search files which are smaller than 1 Megabyte
3. Combine: `-size +1M -size -2M` -> search files which are bigger than 1 Megabyte and smaller than 2 Megabyte

See the man entry for how to enter human-readable formats:

```
 -size n[cwbkMG]
              File uses n units of space.  The following suffixes can be used:

              `b'    for 512-byte blocks (this is the default if no suffix is used)

              `c'    for bytes

              `w'    for two-byte words

              `k'    for Kilobytes (units of 1024 bytes)

              `M'    for Megabytes (units of 1048576 bytes)

              `G'    for Gigabytes (units of 1073741824 bytes)
```

1. **Mind you**, a kilobyte is actually 1024 bytes, NOT 1000 bytes.

##[TESTS] -perm

From the manual:

```
-perm mode    File's  permission  bits  are exactly mode (octal or symbolic).  Since an exact
              match is required, if you want to use this form for  symbolic  modes,  you  may
              have  to  specify  a  rather complex mode string.  For example `-perm g=w' will
              only match files which have mode 0020 (that is, ones for which group write per‐
              mission  is  the only permission set).  It is more likely that you will want to
              use the `/' or `-' forms, for example `-perm -g=w', which matches any file with
              group  write  permission.  See the EXAMPLES section for some illustrative exam‐
              ples.

-perm -mode   All of the permission bits mode are set  for  the  file.   Symbolic  modes  are
              accepted  in  this form, and this is usually the way in which would want to use
              them.  You must specify `u', `g' or `o' if you use a symbolic mode.    See  the
              EXAMPLES section for some illustrative examples.
```

###[TEST] -perm PERMISSION (exact)

PERMISSION matches the **exact permission**

```
find . -perm 664

Search for files which have read and write permission for their owner, and group, but which other users can read but not write to.  Files which meet these criteria but have other permissions bits set (for example if someone can execute the file) will  not  be matched.
```

###[TEST] -perm -PERMISSION (at least for all named users)

-PERMISSION: Check for the presence of the bits in the permission **without regard for the presence of other bits**

```
find . -perm -664

Search  for  files which have read and write permission for their owner and group, and which other users can read, without regard to the presence  of  any  extra  permission bits  (for  example  the executable bit).  This will match a file which has mode 0777, for example.

find . -perm -220
find . -perm -g+w,u+w

Both  these  commands  do  the same thing; search for files which are writable by both their owner and their group.
```

###[TEST] -perm /PERMISSION: (at least for any of the named users)

/PERMISSION: Check if any of the named permission is at least available:

```       
find . -perm /222

Search for files which are writable by somebody (their owner, or their group, or  anybody else).

find . -perm /220
find . -perm /u+w,g+w
find . -perm /u=w,g=w

All three of these commands do the same thing, but the first one uses the octal representation of the file mode, and the other two use the symbolic form. These  commands all  search for  file which are writable by either their owner or their group. The files don't have to be writable by both the owner and group to be matched; either will do.
```

###[TEST] -perm COMBINING

```
find . -perm -444 -perm /222 ! -perm /111
find . -perm -a+r -perm /a+w ! -perm /a+x

These two commands both search for files that are readable for everybody ( -perm  -444 or  -perm -a+r),  have at least one write bit set ( -perm /222 or -perm /a+w) but are not executable for anybody ( ! -perm /111 and ! -perm /a+x respectively).
```

###[ACTION] -exec

Execute against all returned results. Example:

`find . -perm 777 -exec chmod 555 {} \;`

1. The `{}` means is a placeholder for all returned results.
2. The `\;` means to end the expression

7.00
