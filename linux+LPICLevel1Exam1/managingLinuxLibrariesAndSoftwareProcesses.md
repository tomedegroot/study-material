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

```
top - 11:53:19 up  2:33,  1 user,  load average: 0.00, 0.01, 0.05
Tasks: 113 total,   2 running, 111 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem :  1015348 total,   369704 free,   121540 used,   524104 buff/cache
KiB Swap:  2097148 total,  2097148 free,        0 used.   716064 avail Mem 

  PID USER      PR  NI    VIRT    RES    SHR S %CPU %MEM     TIME+ COMMAND                     
  914 root      24   4  451620  36160   5368 S  0.3  3.6   0:24.55 aws                         
    1 root      20   0  125832   6532   3924 S  0.0  0.6   0:04.54 systemd                     
    2 root      20   0       0      0      0 S  0.0  0.0   0:00.00 kthreadd                    
    3 root      20   0       0      0      0 S  0.0  0.0   0:00.00 ksoftirqd/0                 
    5 root       0 -20       0      0      0 S  0.0  0.0   0:00.00 kworker/0:0H                
    7 root      rt   0       0      0      0 S  0.0  0.0   0:00.00 migration/0                 
??? from here until ???END lines may have been inserted/deleted
    8 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcu_bh                      
    9 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/0                     
   10 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/1                     
   11 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/2                     
   12 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/3                     
   13 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/4                     
   14 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/5                     
   15 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/6                     
   16 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/7                     
   17 root      20   0       0      0      0 S  0.0  0.0   0:00.00 rcuob/8                 
```

Load average per minute, 5 minute and 15 minute.
Load average is the % of CPU utilization of the time frame. So:

0.00 0.00 .30 would mean 30% utilization over the past 15 minutes. If the number is 1 or goes above 1, it depends on many CPU's your system has. If:

1. 1 CPU, than processes have to wait untill processing resources are available. Your system is bogging down.
2. 2 CPU's, if:
  1. The number is exactly 1, then 1 CPU is fully used
  2. The number is exactly 2, then 2 CPU's are fully used

NI = **Nice value** from -20 to 19 where 19 is the lowest priority value. This means that all processes with a lower value that 19 have more priority for using the CPU.

PR = 20 + NI
so , the value of PR = 20 + (-20 to +19) is 0 to 39 that maps to static priority 100 to 139.

According to top manual:
```
PR -- Priority The scheduling priority of the task. If you see 'rt' in this field, it means the task is running under 'real time' scheduling priority.
NI is nice value of task. A negative nice value means higher priority, whereas a positive nice value means lower priority.Zero in this field simply means priority will not be adjusted in determining a task's dispatch-ability
```

How to renice a process? -> `-r`

1. Commands to enter during `top` execution:
  1. Displaying and searching:
    1. `L` -> locate a certain string
    2. `o` -> filter on a column, example: `o COMMAND=http`. Press `o` again for a new filter
    3. `CRTL+o` -> see all filters
    4. `=` -> clear all the filters and brings you back to the start screen of top
    5. `SHIFT + m`  -> resort on memory utilization
    6. `SHIFT + p` -> resort on cpu (processor) utilization
  2. Manipulate proceses:
    1. `r` -> renice a value; give a new value for nice
    2. `k` -> kill a process with a [signal](https://bash.cyberciti.biz/guide/Sending_signal_to_Processes):
      1. 9 (SIGKILL)-> force quit for when a process is hung
      2. 15 (SIGTERM)-> nicer way of terminating a process (this is the default!)
    3. `s` -> change delay (same as `-d` when starting top). **mnemonic** Sjeens delay
2. Options entered when starting top: `top OPTIONS`
  1. How to set the delay time? -> `-d SECONDS`, so `-d 1` sets update time of 1 second
  2. How to specify the process id's you want to view -> `-pPROCESSID1,PROCESSID2...` Great tool to watch just one or two processes of a beta program
  3. How to specify the amount of updates and then quit? -> `-n NUMBEROFUPDATES` so `-n 5` will make sure top updates 5 times and then quits

#Using Nice to Change Linux Process Priorities

1. What is the highest nice value? -> -20
2. What is the lowest nice values? -> 19
3. What is the default nice value? -> 10
4. How to set a nice value for a program you are starting? -> `nice -n NICEVALUE COMMAND`, example: `nice -n -20 top`. **You need to be root** Logical otherwise every user would increase the priority of it's own priority

##How to renice from the command line? -> 

`renice OPTIONS`
  1. `renice -n -20 -p 1650` where `-p 1650` signifies processid 1650
  2. `renice -n -20 -u root`, set for all processes from root.


