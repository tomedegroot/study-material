#File Naming Basics And Look A Look At File Commands

##Case sensitivity

File names and file extensions are case sensitive

##Spaces

Space are interpreted by the shell. So if you want to create a file name with space, there are two ways:

1. `vi 'this file has spaces'` (quotes)
2. `vi this\ file\ has\ spaces` (escaping)

##File names limit:

1. EXT: 255 chars

##Files starting with a .

These hidden files, used for configuration. They are excluded from the view with a basic ls command (use the `-a` flag)

##File Globbing in Bash

1. What is the wild card for 1 symbol? -> `?` -> `ls bo?k` will get book
2. What is the wild card for 0,1 or multiple symbols? -> `*` -> `ls b*k` will get book
3. How can a range be expressed **with reference** to the file names? -> `ls b[oa]k` -> means 'bok' or 'bak', bash can only expand if it finds the filenames
4. How can a range be expressed without reference to the file names? Use `{}`, so:
  1. `touch {a,b,c}` -> expands to a,b or c
  2. `touch {a..d}` -> expands to a,b,c or d
  3. `touch {ed,ld}*` -> expand to everything that starts with either 'ed' or 'ld'

**Since there (must be a reference to a file names)[http://tomecat.com/jeffy/tttt/glob.html] for square brackets ([]) to work, touching files which are non existent will not work with square brackets, you need to use the curly brackets for that.**

**Globbing is sometimes work the same as REGEX, but they are not the same.**

##ls

ls lists, options:

1. `-a` -> all, including . files
2. `-d` -> only show directories
3. `-F` -> append indicator (one of */=>@|) to entries. So you can easily see it is a dir or socket for example
  1. `/` -> dir
  2. `@` -> symbolic link
4. `-R` -> recursive

##cp

`cp [OPTIONS] SOURCE DESTINATION`
  1. `-i` -> interactive, prompt before overwrite
  2. `-p` -> preserve permissions. By default, if you copy a file it gets the default file permissions (see umask). With `-p` you keep the same permissions and owner as the original file
  3. `-a` -> It preserves ownership on all the folders and it's contents recursively.
  4. `-u` -> Update copy. It's a backup command: it tells cp to only copy if the target location is newer or the target location doesn't exist
  5. `-r` -> recursive

#File Archiving & The RM, MV Commands

##mv

Moving files

`mv [OPTIONS] SOURCE TARGET`
  1. How to prevent an overwrite?: `-n` for no clobber
  2. How to get a prompt before overwriting?: `-i` for interactive

What is remarkable on the relationship between `mv` and `cp` -> they share a lot of there options.

How does Linux mv work under the hood when writing to a different file system? -> Linux writes the file to the new file system and then removes the file from the old file system.

##rm

How to remove a file? -> `rm [OPTIONS] file`
  1. How to do this recursively? -> either `r` or `R`

##mkdir

How to create a dir? -> `mkdir DIRNAME`

How to create necessary parents if they do not exist? -> `mkdir -p DIRNAME`, example: `mkdir -p DIRPARENT DIRNAME`

##tar

How to create an archive of files? -> use `tar [OPTIONS] FILE...`

How is this also called? -> a tarball

What usually happens with a tarball? -> it will be compressed with a zipping tool (gzip or bzip)

Options:
  1. How to get verbose output? -> `-v`
  2. How to select which archive file you want? -> `-f archive` **mind you** the `-f` option must be at the end of options for specifying the zip file

  3. How to create a tarball? -> `-c`, so `tar -cvf archive file1 file2`
  4. How to extract a tarball? -> `-x`
    1. How to extract **only one file** from a tarball? -> `tar -xvf tarball.tar file`
  5. How to list the files in a tarball? -> `-t` for lisT

  6. How to filter the tar operation through gzip? `-z` so it will either zip or unzip using gzip:
    1. `tar cvzf archive.tar.gz archivezipped text1 text2` -> archive and zip files
    2. `tar tvzf archive.tar.gz` -> list zipped archive 
    3. `tar xvzf archive.tar.gz archivezipped` -> extract zipped archive
    4. **mind you** the `-f` option must be at the end of options for specifying the zip file

  7. How to append **a tarball to another tarball?** -> `-A` for Appending another tar
  8. How to add a file to a tarball? -> `-r`, so `tar -rvf etc.tar dirlist.txt` will add dirlist.xt to etc.tar, **mnemonic** r for add file entRy
  9. How to make tar change dir before an action? -> `-C dirname`, so `tar -c /var -xvf archive.tar` will extract the contents to */var/*. **mind you** tar executes in the order of operations it finds, so the `-c` has to before the `-x` operator. (More info on the order of -c)[https://www.gnu.org/software/tar/manual/html_node/directory.html]

##The gzip and gunzip command

Use it if you want to zip 1 file, not a dir use gzip.

How to use gzip? -> `gzip [OPTIONS] FILENAME`
  1. How to write to a new file and keep the existing one? -> `gzip -c file1 > file1.gz` -> the `-c` option writes to STDOUT and keeps the original file. Use this options for `gunzip` as well. **mnemonic** Cat the result

**Learned from the exercise** A .gz file is just one big file. If you execute `gzip -c * > mygzip.gz` it will create one .gz file which concatenates all the files. And if you then append a new file to it with gzip -c newfile.txt >> mygzip.gz it will append the zipped content.

@todo study which of the gzip and tar commands alters the source file(s) and where the output is going by default

##Links

How to give a file multiple identities, like Windows shortcuts or Mac OS X aliases? -> use links

Why do you want to use links?
  1. Access the same file, but from multiple locations

Which 2 link types are there?
  1. hard -> cannot be used across file systems, it is a directory entry that is associated with an  (inode on a file system)[http://blog.scoutapp.com/articles/2014/10/08/understanding-disk-inodes]. So if you want to remove the file, you have to remove both hard links
  2. soft -> (symbolic) points to another location and can be used across file systems, therefor it is used more. It is a file with it's own inode and it works like a redirect. Technically it is slower than a hard link.
  3. (see the difference)[http://askubuntu.com/a/43599]

`ln [OPTIONS] SOURCE LINK` -> source is the file you are referencing, hard link by default
  1. How to create a symbolic link? -> `s`
  2. How to change the location of a link? -> `ln -is NEW_SOURCE LINK` -> the `i` is interactive and prompts you to overwrite with the new link. Of course, add the `s` flag to make it a symbolic link or leave it to make it a hard link
  3. How to overwrite without a prompt? -> `-f` for force, so: `ln -fs /etc/hosts hosts_symbolic_link`

Extra:

The output of `ls -al` is:

```
-rwxrw-r--    1    root   root 2048    Jan 13 07:11 afile.exe
1. file permissions,
2. number of links,
3. owner name,
4. owner group,
5. file size,
6. time of last modification, and
7. file/directory name

File permissions is displayed as following;

1. first character is - or l or d, d indicates a directory, a line represents a file, l is a symlink (or soft link) - special type of file
three sets of characters, three times, indicating permissions for owner, group and other:
2. r = readable
3. w = writable
4. x = executable

In your example -rwxrw-r--, this means the line displayed is:

1. a regular file (displayed as -)
2. readable, writable and executable by owner (rwx)
3. readable, writable, but not executable by group (rw-)
4. readable but not writable or executable by other (r--)
```

So dirs can have a lot of links. Why?

```
Historically, the first Unix filesystem created two entries in every directory: . pointing to the directory itself, and .. pointing to its parent. This provided an easy way to traverse the filesystem, both for applications and for the OS itself.

Thus each directory has a link count of 2+n where n is the number of subdirectories. The links are the entry for that directory in its parent, the directory's own . entry, and the .. entry in each subdirectory.

Later filesystems have tended to keep track of parent directories in memory and usually don't need . and .. to exist as actual entries; typical modern unix systems treat . and .. as special values as part of the filesystem-type-independent filesystem code. Some filesystems still include . and .. entries, or pretend to even though nothing appears on the disk.

Most filesystems still report a link count of 2+n for directories regardless of whether . and .. entries exist, but there are exceptions, for example btrfs doesn't do this.
````

##Copying versus Linking

What to use depends on your needs.

If you remove a file, hard links to the same inode of that file still work. If you remove a file which is soft linked, the symbolic link breaks. (so if you get the error: `not such file or directory`), but the file exists, than check via `ls -al` if the file is a symlink and the link to the original file broken. This is not the case for hard links:

```
A file is an inode with meta data among which a list of pointers to where to find the data.

In order to be able to access a file, you have to link it to a directory (think of directories as phone directories, not folders), that is add one or more entries to one of more directories to associate a name with that file.

All those links, those file names point to the same file. There's not one that is the original and the other ones that are links. They are all access points to the same file (same inode) in the directory tree. When you get the size of the file (lstat system call), you're retrieving information (that metadata referred to above) stored in the inode, it doesn't matter which file name, which link you're using to refer to that file.
```

Soft links on the other hand save space.

##Basic Directory & Group Commands

How to remove a directory? -> `rmdir` will fail if a directory is not empty, so use: `rm -R DIRNAME`

##Change group

What is you are logged in as user and you want to change ownership of the group? You can only to that if you belong to the giving and the receiving group. You cannot 'give away' files.

`chgrp GROUPNAME FILENAME`
  1. `-R` -> dp recursively, so group ownership of subdir(s) as well

#Special Perimission Bits

See the (Oracle Docs on permissions)[https://docs.oracle.com/cd/E19683-01/816-4883/secfile-69/index.html] and (this)[http://www.tutonics.com/2012/12/linux-file-permissions-chmod-umask.html#special_mode_bits] for more info on the special bits

##sticky bit

Info from previous notes on the sticky bit:

Caveat: all the files in /tmp have 777 permissions. This way everyone has write access to /tmp, but this also  means users can delete other user's files. How to prevent this?

Sticky bit->A folder with a sticky bit ensures that files and folders within the folder with the sticky bit can only be deleted by the owner, even if the permissions on the file are 777.

`chmod o+t FILE` -> example: `chmod o+t /sticky`, ls output: `drwxr-xr-t`
`chmod o-t FILE` -> example: `chmod o-t /sticky`

Mnemonic aid: it's the user who applies the special bit to (in this case others) and it's the t from sTicky

After this, when you do ls -l The last symbol of the permission string is a 't'. This means any files within the folder with sticky bit can only be deleted by the user who created the file.

You can set the sticky bit via a fourth octet before the regular octets in chmod: chmod 0777 sticky -> sticky bit is off chmod 1777 sticky -> sticky bit is on.

REMEMBER: Without the sticky bit set, any user with write and execute permissions for the directory can rename or delete contained files, regardless of the file's owner.

In other words, if you have write access to a dir, but not the file in the dir (/dir/file), then you can still the delete the file since you have write access to the dir

##setuid permission bit

When you run a program in Linux, by default the program has the same permissions as the user who executes the program. See test output of a program which prints a line to a file in /etc owned by root:

```
-rwxr-xr-x. 1 root root 48 Dec 11 21:01 program.sh
[root@t-degroot1 root]# exit
exit
[tom@t-degroot1 root]$ ./program.sh
./program.sh: line 1: /etc/myfile.txt: Permission denied
```

Why? -> tom doesn't have write permissions to /etc/myfile.txt and if tom runs the program, the program gets the same permissions as tom and thus it cannot write.

How can you run a program with the same permissions as the user who owns the program? -> with the setuid permission bit.

`chmod u+s FILE` -> set setuid bit. ls output: `-rwsrwxrw-`
`chmod u-s FILE` -> unset setuid bit

### 2 caveats

1. The effective program you are running when you execute a shell script is bash, so you have to set the setiud bit on the bash executable to run the program with the same permissions as the owner

2. On RedHat (and thus CentOS) the setuid bit is [ignored for shell scripts)](https://access.redhat.com/solutions/124693) thus the permissions are of the user who executes the script. This is a [security measure](http://unix.stackexchange.com/a/130910)

##set setgid

Run this file with same user permissions of the group:

`chmod g+s FILE` -> set setgid bit. ls output: `-rwxrwsrw-`
`chmod g-s FILE` -> unset setgid bit

Same concept as the setuid bit

##setgid on a dir

When the setgid is set on a dir, it has a whole different meaning. The setgid on a dir causes new files and subdirectories created within it to inherit its group ID,

##Octal permissions for the special bits

Special Mode Bits

The setuid, setgid, and sticky bit can be set using chmod where

1 = sticky bit
2 = setgid
4 = setuid
For example to set the setuid bit along with permissions 766:

chmod 4766 filename

[More info on stickybit, SETGID, SETUID](http://unix.stackexchange.com/a/43747)

#Default Permission umask, newgrp and chattr

##newgrp

`newgrp GROUPNAME` -> change the current groupid of the login session. Any newly created file is group owned by the groupid of the login session:

```
[root@t-degroot1 tom]# newgrp linuxacademy
[root@t-degroot1 tom]# echo "newfile" >> newfile.txt
[root@t-degroot1 tom]# ls -l

-rw-r--r--. 1 root linuxacademy   16 Dec 12 08:53 newfile.txt
```

Why do you want to use newgrp? -> When you create a lot of groups in a session you don't have to use a lot of `chown`

##umask

Linux set the following modes on files and folders if no umask is set:

files=666
folders=777

With the umask you can set different default modes for files and folders. So a umask of 002 will result in:

files=664
folders=775

So you have to **substract the umask from the permissions** this because the umask [uses the bitwise AND NOT](https://www.cyberciti.biz/tips/understanding-linux-unix-umask-value-usage.html). So if you want to substract only the read rights for all users: `umask 444`. **Basically you see which rights you want to take away.**

##Additional file attributes

You can set extra attributes on files via chattr:

`chattr [OPTIONS] [MODE] [FILES]...`

Where [MODE] = `+-=[aAcCdDeijsStTu]`

1. `+` -> sets
2. `-` -> removes
3. `=` -> make it the only attribute(s)

Some common attributes:

1. `A` -> not atime updates, this means the update time of the file does no longer gets updated when the file is **accessed**. Remember, this is **not** when the file last modified time which shows in ls. This saves time for the kernel.
2. `c` -> compress files or any files placed in a dir
3. `a` -> can only be open for appending. (need to be root to set this)
4. `i` -> immutable, Means no renaming, no symbolic link creation, no execution, no writable, even though the user is the owner, has the right permissions or is the root user. (need to be root to set this)
5. `s` -> secure deletion, it works like a shredder: If the file gets deleted, not only are the pointers deleted, but the kernel write blocks of zero's to the location.

Example: `sudo chattr +a test.txt `

Common [OPTIONS]
  1. `R` -> Recursive for dirs

How to list the extra attributes? ->  `lsattr`

I get a permission issue, even though I have the right permissions or I am root. What to do? -> check the extra attributes via `lsattr`

#Linux Core Directories & What They Are Used For

Where is info for the initial booting of the computer, such as grub? -> */boot/*

Most of this info is in the notes of linuxSystemManagementAndArchitectureTopics.md

Where are the services that can started or stopped? -> */etc/init.d/* [info](http://www.ghacks.net/2009/04/04/get-to-know-linux-the-etcinitd-directory/)

#Finding Files in Linux Using Find, Locate, Whereis, Which and Type

##find

How to search within a dir tree? -> `find`

`find [OPTIONS] [PATH]... [EXPRESSION]`

Where [EXPRESSION] is made up of: [OPTIONS] [TESTS] [ACTIONS]. In:

`find / -name test`, the [PATH] = */*, the [EXPRESSION] = `-name test` where `-name test` = [TEST]

Every test in [TESTS] works like a filter

###[TESTS] -maxdepth

How many dirs deep do you want to go? `find . -maxdepth 0`

Where:

1. `maxdepth 0` is only 1 file which is the current dir itself and 
2. `maxdepth 1` is the content of the current dir

###[TESTS] -name

Example: `find / -name *.c`

###[TESTS] -perm

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

####[TEST] -perm PERMISSION (exact)

PERMISSION matches the **exact permission**

```
find . -perm 664

Search for files which have read and write permission for their owner, and group, but which other users can read but not write to.  Files which meet these criteria but have other permissions bits set (for example if someone can execute the file) will  not  be matched.
```

####[TEST] -perm -PERMISSION (at least for all named users)

-PERMISSION: Check for the presence of the bits in the permission **without regard for the presence of other bits**

```
find . -perm -664

Search  for  files which have read and write permission for their owner and group, and which other users can read, without regard to the presence  of  any  extra  permission bits  (for  example  the executable bit).  This will match a file which has mode 0777, for example.

find . -perm -220
find . -perm -g+w,u+w

Both  these  commands  do  the same thing; search for files which are writable by both their owner and their group.
```

####[TEST] -perm /PERMISSION: (at least for any of the named users)

/PERMISSION: Check if any of the named permission is at least available:

```       
find . -perm /222

Search for files which are writable by somebody (their owner, or their group, or  anybody else).

find . -perm /220
find . -perm /u+w,g+w
find . -perm /u=w,g=w

All three of these commands do the same thing, but the first one uses the octal representation of the file mode, and the other two use the symbolic form. These  commands all  search for  file which are writable by either their owner or their group. The files don't have to be writable by both the owner and group to be matched; either will do.
```

####[TEST] -perm COMBINING

```
find . -perm -444 -perm /222 ! -perm /111
find . -perm -a+r -perm /a+w ! -perm /a+x

These two commands both search for files that are readable for everybody ( -perm  -444 or  -perm -a+r),  have at least one write bit set ( -perm /222 or -perm /a+w) but are not executable for anybody ( ! -perm /111 and ! -perm /a+x respectively).
```

###[TEST] -size

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

###[TEST] -user or -group

How to search by the owner or group of a file? -> `find . -user tom` or `find . -group root`

###locate

Why use `locate`? - search for files and dirs from a database (so it's quicker.) 

What is the downside -> the database only updates once an hour, **but** you can update the database directly via `updatedb`

###whereis

Only searches for binary files and man page dirs.

###which

Only searches within path an shows the first result in the path

###type command

Why use `type` -> it tells you how bash would interpret a command:

```
[root@t-degroot1 home]# type ls
ls is aliased to `ls --color=auto'
```

What does the -t option do? -> tells you what type the command is. From the man:

```
If the -t option is used, type prints a string which is one of alias, keyword, function, builtin, or file
```

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

#dd

##How does dd work?

dd is a utility to copy from stdin to stdout

When to use this? -> Creating iso files, creating disk images,  securely deleting files/disks (filling it with 0's), converting lower case to upper case and vice versa, writing to a partition. So:

```
In essence, dd copies and optionally converts data. It uses an input buffer, conversion buffer if conversion is specified, and an output buffer. Reads are issued to the input file or device for the size of the input buffer, optional conversions are applied, and writes are issued for the size of the output buffer
```

Structure of dd command: `dd [OPERANDS]...`

Example: `dd if=/dev/zero of=file.iso bs=1024 count=1`

Some operands:
1. How to specify the input file? -> `if=INPUTFLE` -> by default dd reads from STDIN
2. How to specify the output file? -> `of=OUTPUTFILE` -> by default dd writes to STDOUT
3. How to set the block size? -> `bs=BLOCKSIZE`, entered in bytes by default or in  human-readable format such as: `bs=1K` By default dd will collected and processed as full-sized output block until the end of the input is read. @todo look this up in the book. 
4. How to set the count? -> `count=`, copy only n input blocks with the size specified by the block size. If the block size is NOT specified, dd will read until the end of the input file.

##How to backup using dd?

How to grab the first 5 bytes of a filesytem?

1. Pick the filesystem from an overview -> `df -h`
2. We start with entering the input file and output file: `dd if=/dev/xda1 of=mbr.bak`
3. Enter the block size (what you want to transfer per time) -> `dd if=/dev/xda1 of=mbr.bak bs=512`
4. Set the count of how many times you want to copy the block size -> `dd if=/dev/xda1 of=mbr.bak bs=512 count=1`


##Convert using dd

1. How to convert using dd? ->`dd if=INPUTFILE conv=CONVERSIONTYPE`. Example:
  1. `dd if=myfile conv=ucase` (Only one needed for certification)

##Securely deleting a file

Deleting a file only removes the pointers, if you want to savely delete a file (so deleting a contents):

Example: `dd if=/dev/urandom of=myfile bs=16 count=1`

So specify the exact file size for the bytes at a time and the count

```
[root@t-degroot1 tom]# ls myfile
myfile
[root@t-degroot1 tom]# dd if=/dev/urandom of=myfile bs=16 count=1
1+0 records in
1+0 records out
16 bytes (16 B) copied, 0.000162625 s, 98.4 kB/s
[root@t-degroot1 tom]# ls myfile
myfile
```

Instead of */dev/urandom* you can choose */dev/zero*. This generates zero's.

###Difference between /dev/random and /dev/urandom

*/dev/random* depends on entropy (= lack of order) gathered by the system. If there is not enough collected, /dev/random will block. */dev/urandom* generates it's own entropy pool, thus generating it's own randomness, thus not blocking if the system does not have enough entropy gathered. [source](http://stackoverflow.com/questions/4819359/dev-random-extremely-slow) So for large files, use */dev/urandom*

##Backing up, copying one hard drive to another hard drive

1. Mount a device
2. Check what the device is called: `ls /dev`
3. Create a filesytem on the device: `mkfs -t ext4 /dev/xvdf` (This will be explained in-depth later), to check to make sure it is not a mounted filesystem already: `df` -> see where all currently mounted filesystems are mounted
4. To backup the first 1000 MB: `dd if=/dev/xvda1 of=/dev/xvdf bs=1M count=1000`

#touch

## stat

How to check the last modify time? -> stat FILENAME
  1. Access = last time file was read
  2. Modify = last time file was modified (content changed)
  3. Change = last time meta data was changed (e.g. permissions)

##touch

Create an empty file or update the last access, modify and/or change time

1. `touch [OPTIONS] FILENAME` -> change access, modify AND change time
  1. How to change only the access time? -> `-a`
  2. How to change only the modified time? -> `-m`
  3. How to use another files access and modify time to set the access and modify time for your file? -> `stat -r FILESOURCE FILETARGET` FILETARGET will have the same access and modify time as FILESOUCE. The `-r` is for reference

#inode

Find more [extra info on inode numbers](https://www.cyberciti.biz/tips/understanding-unixlinux-filesystem-inodes.html) and [deleting a file with special characters in it by inode number](https://www.cyberciti.biz/tips/delete-remove-files-with-inode-number.html)
