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
  1. `touch {a,b,c}` -> expands to a,b and c
  2. `touch {a..d}` -> expands to a,b,c and d
  3. `touch {ed,ld}*` -> expand to everything that starts with either 'ed' or 'ld'

**Since there (must be a reference to a file names){http://tomecat.com/jeffy/tttt/glob.html} for square brackets ([]) to work, touching files which are non existent will not work with square brackets, you need to use the curly brackets for that.**

**Globbing is sometimes work the same as REGEX, but they are not the same.**

##ls

ls lists, options:

1. `-a` -> all, including . files
2. `-d` -> only show directories
3. `-f` -> append indicator (one of */=>@|) to entries. So you can easily see it is a dir or socket for example
  1. `/` -> dir
  2. `@` -> symbolic link
4. `-R` -> recursive

##cp

`cp [OPTIONS] SOURCE DESTINATION`
  1. `-i` -> interactive, prompt before overwrite
  2. `-p` -> preserve permissions. By default, if you copy a file it gets the same permissions and owner as the folder you are copying to. With `-p` you keep the same permissions and owner as the original file

#File Archiving & The RM, MV Commands

##cp

Extra notes on flags for `cp`:
  1. `-a` -> It preserves ownership on all the folders and it's contents recursively.
  2. `-u` -> Update copy. It's a backup command: it tells cp to only copy if the target location is newer or the target location doesn't exist

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

##tar

How to create an archive of files? -> use `tar [OPTIONS] FILE...`

How is this also called? -> a tarball

What usually happens with a tarball? -> it will be compressed with a zipping tool (gzip or bzip)

Options:
  1. How to get verbose output? -> `-v`
  2. How to select which archive file you want? -> `-f archive`

  3. How to create a tarball? -> `-c`, so `tar -cvf archive file1 file2`
  4. How to extract a tarball? -> `-x`
  5. How to list the files in a tarball? -> `-t` for lisT

  6. How to filter the tar operation through gzip? `-z` so it will either zip or unzip using gzip:
    1. `tar cvfz archive.tar.gz archivezipped text1 text2` -> archive and zip files
    2. `tar tvfz archive.tar.gz archivezipped` -> list zipped archive
    3. `tar xvfz archive.tar.gz archivezipped` -> extract zipped archive

  7. How to append a tarball to another tarball? -> `-A`
  8. How to make tar change dir before extracting? -> `-C dirname`, so `tar xvf archive.tar -c /var` will extract the contents to */var/*

##The gzip and gunzip command

Use it if you want to zip 1 file, not a dir use gzip.

How to use gzip? -> `gzip [OPTIONS] FILENAME`
  1. How to write to a new file and keep the existing one? -> `gzip -c file1 > file1.gz` -> the `-c` option writes to STDOUT and keeps the original file. Use this options for `gunzip` as well

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
  2. How to change the location of a link? -> `ln -is NEW_SOURCE LINK` -> the `i` is interactive and prompts you to overwrite with the new link. Of course, add the `s` flag to overwrite
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

If you remove a file, hard links to the same inode of that file still work. If you remove a file which is soft linked, the symbolic link breaks. See also:

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

2. On RedHat (and thus CentOS) the setuid bit is (ignored for shell scripts)[https://access.redhat.com/solutions/124693] thus the permissions are of the user who executes the script. This is a (security measure)[http://unix.stackexchange.com/a/130910]

##set setgid

Run this file with same user permissions of the group:

`chmod g+s FILE` -> set setgid bit. ls output: `-rwxrwsrw-`
`chmod g-s FILE` -> unset setgid bit

Same concept as the setuid bit

##Octal permissions for the special bits

Special Mode Bits

The setuid, setgid, and sticky bit can be set using chmod where

1 = sticky bit
2 = setgid
4 = setuid
For example to set the setuid bit along with permissions 766:

chmod 4766 filename

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

By default the following modes are set:

files=666
folders=777

With the umask you can the default modes for files and folders. So a umask of 002 will result in:

files=664
folders=775

So you have to **substract the umask from the permissions** this because the umask (uses the bitwise AND NOT){https://www.cyberciti.biz/tips/understanding-linux-unix-umask-value-usage.html}. So if you want to substract only the read rights for all users: `umask 444`

4.10




