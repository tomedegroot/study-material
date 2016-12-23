#Software Libraries

Libraries provide code that can be used in between software packages. But since they are shared, issues with:

1. Locating the correct library
2. Getting the right version of the library

Might occur. We will learn how to fix those.

##Configuration

Main configuration file for libraries is */etc/ld.so.conf*. This way is just an include for the dir with config files in it:

```
include ld.so.conf.d/*.conf
```

If you update this file, you have to run a command to update the cache: `ldconfig`

Extra: it is called ld.so* because it Links Dynamically Shared Objects

**Mind you, the core libraries are always available:** 
1. The */lib/* dir is always included, it doesn't need to be configured
2. The */usr/lib/* dir is always included, it doesn't need to be configured

What is you do not want to update the config file, because you are still developing?

set the $LD_LIBRARY_PATH variable: `export LD_LIBRARY_PATH=/usr/lib/mylibrary`, off course the `ldconfig` command does **not** have to be executed and give more paths seperated via the colon (':')

So with:
1. The files in the config files/dirs (loaded a boot and reloaded with `ldconfig`)
2. And the $LD_LIBRARY_PATH variable

you can set paths where will be searched for variables.

Info only in the course notes:

1. Create symlinks for fixing minor .x.x.x version differences
2. How to get library dependencies on a program? `ldd PATHTOPROGRAM`. You have to give the path, not the program name. ldd will not look in $PATH for you to find the path of program. Example:

```
[tom@t-degroot1 ~]$ ldd $(which httpd)
	linux-vdso.so.1 =>  (0x00007fff825cd000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f6901795000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f690156e000)
	libaprutil-1.so.0 => /lib64/libaprutil-1.so.0 (0x00007f6901344000)
	libcrypt.so.1 => /lib64/libcrypt.so.1 (0x00007f690110d000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f6900ee3000)
	libdb-5.3.so => /lib64/libdb-5.3.so (0x00007f6900b24000)
	libapr-1.so.0 => /lib64/libapr-1.so.0 (0x00007f69008f5000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f69006d9000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f69004d4000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f6900113000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f6901c80000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f68fff0e000)
	libfreebl3.so => /lib64/libfreebl3.so (0x00007f68ffd0a000)
```

#Using `ps` to manage processes

@todo, not vital for exam: read up the difference between `-x` and `-e`

1. What is a reason for the complexity of `ps`? -> `ps` is build to run on different systems, so there are 3 styles of entering options (UNIX, BSD, GNU)

2. `What is `ps` showing by default? -> only the processes from the terminal executing the command, truncated to fit your terminal window

`ps OPTIONS` 
1. Selection options:
 1. `-e` -> displays all the processes on the system
 2. `-x` -> displays all the processes, even if they don't have a tty. Splits the processes by user owner
 3. `-U USERNAME` or `U USERNAME` -> display all the processes of a USERNAME
 4. `aux` -> everything on the system, on the system
 5. `--forest` -> see relationships between the processes, example: `ps -U root --forest`
2. Output format options:
  1. `u` -> user orientated ouutput. Example: `ps u U tom`:

```
[root@t-degroot1 tom]# ps u U tom
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
tom       1129  0.0  0.2 142960  2196 ?        S    16:51   0:00 sshd: tom@pts/0
tom       1130  0.0  0.2 115520  2188 pts/0    Ss   16:51   0:00 -bash
```

**Mind you** -> the `U` is different from `-u`
**Mind you** -> Some selection options are mutually exclusive. If you select only for USERNAME via `-U` you cannot select all in the same command via -x

##How to change the ps default settings

$PS_PERSONALITY env variable controls the default ps settings
