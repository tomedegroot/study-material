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

##`ps aux` is most used

Sample output:

```
[root@t-degroot1 tom]# ps aux | grep httpd
root      2211  0.6  0.4 226012  4980 ?        Ss   11:54   0:00 /usr/sbin/httpd -DFOREGROUND
apache    2212  0.0  0.2 226012  2860 ?        S    11:54   0:00 /usr/sbin/httpd -DFOREGROUND
```

Meaning of columns:

USER = user owning the process
PID = process ID of the process
%CPU = It is the CPU time used divided by the time the process has been running.
%MEM = ratio of the process’s resident set size to the physical memory on the machine
VSZ = virtual memory usage of entire process (in KiB)
RSS = resident set size, the non-swapped physical memory that a task has used (in KiB)
TTY = controlling tty (terminal)
STAT = multi-character process state
START = starting time or date of the process
TIME = cumulative CPU time
COMMAND = command with all its arguments


##How to change the ps default settings

$PS_PERSONALITY env variable controls the default ps settings

#top

Sample output:


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

1. Command line options `top [OPTIONS]`
  1. How to show only processes for a specific user? -> `top -u USERNAME`
  2. How to specify the process id's you want to view -> `-pPROCESSID1,PROCESSID2...` Great tool to watch just one or two processes of a beta program
  3. How to specify the amount of updates and then quit? -> `-n NUMBEROFUPDATES` so `-n 5` will make sure top updates 5 times and then quits
  4. How to set the update time? -> `-d SECONDS`, so `-d 1` sets upDate time of 1 second
  5. How to operate in batch mode? -> `-b`. With batch mode top runs until it's killed or the program reaches the max number of input via `-n`. This means commands can not be entered during execution
2. Commands to enter during `top` execution:
  1. Sorting:
    1. `SHIFT + m`  -> resort on memory utilization
    2. `SHIFT + p` -> resort on cpu (processor) utilization
  2. Searching:
    1. `L` -> locate a string in the COMMAND column
    2. `o` -> filter on a column, example: `o COMMAND=http`. Press `o` again for a new filter
    3. `CRTL+o` -> see all filters
    4. `=` -> clear all the filters and brings you back to the start screen of top
  3. Manipulate proceses:
    1. `r` -> renice a value; give a new value for nice
    2. `k` -> kill a process with a [signal](https://bash.cyberciti.biz/guide/Sending_signal_to_Processes):
      1. 9 (SIGKILL)-> force quit for when a process is hung
      2. 15 (SIGTERM)-> nicer way of terminating a process (this is the default!)
    3. `s` -> change delay (same as `-d` when starting top). **mnemonic** Sjeens delay

#Using Nice to Change Linux Process Priorities

1. What is the highest nice value? -> -20
2. What is the lowest nice values? -> 19
3. What is the default nice value? -> 10
4. How to set a nice value for a program you are starting? -> `nice -n NICEVALUE COMMAND`, example: `nice -n -20 top`. **You need to be root** Logical otherwise every user would increase the priority of it's own priority

##How to renice from the command line? -> 

`renice OPTIONS`
  1. `renice -n -20 -p 1650` where `-p 1650` signifies processid 1650
  2. `renice -n -20 -u root`, set for all processes from root.

#Killing Processes In Linux

## `kill` and `killall`

`kill -s SIGNAL PROCESSID...` or shorthand without -s: `kill -SIGNALID PROCESSID`

Following signals:
1. What to signal to send with a frozen project? -> 9 hard kill
2. What to signal a restart? -> 1 restart
3. What to signal to properly shutdown? -> 15 graceful shutdown

How to kill multiple processes with 1 command? 2 ways:
1. `kill -SIGNAL PROCESSID1 PROCESSID2...`
2  `killal -SIGNAL NAME` where NAME is the name of the command, so:

```
[root@t-degroot1 tom]# ps aux | grep httpd
root      2105  0.0  0.4 226012  4980 ?        Ss   11:49   0:00 /usr/sbin/httpd -DFOREGROUND
apache    2106  0.0  0.2 226012  2860 ?        S    11:49   0:00 /usr/sbin/httpd -DFOREGROUND
apache    2107  0.0  0.2 226012  2860 ?        S    11:49   0:00 /usr/sbin/httpd -DFOREGROUND
apache    2108  0.0  0.2 226012  2860 ?        S    11:49   0:00 /usr/sbin/httpd -DFOREGROUND
apache    2109  0.0  0.2 226012  2860 ?        S    11:49   0:00 /usr/sbin/httpd -DFOREGROUND
apache    2110  0.0  0.2 226012  2860 ?        S    11:49   0:00 /usr/sbin/httpd -DFOREGROUND
root      2130  0.0  0.0 112648   964 pts/0    R+   11:50   0:00 grep --color=auto httpd
[root@t-degroot1 tom]# killall -9 httpd
[root@t-degroot1 tom]# ps aux | grep httpd
root      2138  0.0  0.0 112648   964 pts/0    R+   11:50   0:00 grep --color=auto httpd
```

##nohup

Normally when you exit you tty, all the processes associated with it will be killed. Use `nohup` to prevent this

#`uname` (=Unix Name)

`uname` -> Give information about the system. Flags:

1. How to get the operating system -> `-o`
2. How to get the host name? -> `-n` or `--nodename`
3. How to get the kernel name? -> `-s` or `--kernel-name`
4. How to get kernel release number -> `-r` or `--kernel-release`
5. How to get kernel version number -> `-v` or `--kernel-version` 
6. How to get the machine hardware name (e.g. x86_64)-> `-m`
7. How to get the hardware platform (e.g. x86_64) ->  `-i` or `--hardware-platform`
8. How to get the processor type (e.g. x86_64 or i386) -> `-p` 
9. Give all information add once -> `-a` (`uname -a | sed 's/ /\n/g'` for nice `-aA` for nice formatting)

#Understanding Background vs Foreground jobs

A job is shell concept (not a kernel concept as a process (= running program with own address space)) and is an interactive program that doesn't detach (i.e. a daemon) [source](http://unix.stackexchange.com/questions/4214/what-is-the-difference-between-a-job-and-a-process)

**mind you**: jobs are only related to the current tty

1. How to send a job to the background? -> `CRTL+Z` this causes the job to be stopped
2. How to see which jobs are running in the current tty? -> `jobs`
3. How to send a job to the foreground? `fg JOBID`
4. How to launch a job in the background? With the ampersand (&) = `COMMAND &`
5. How to send a job to the background and keep it running? -> `bg JOBID` 

Example:

```
[root@t-degroot1 tom]# vi &
[1] 3053
[root@t-degroot1 tom]# jobs
[1]+  Stopped                 vi
```

6. How to kill a job? -> `kill %JOBNUMBER` Example:

```
[root@t-degroot1 tom]# jobs
[1]+  Running                 ping -c 5000 yahoo.com > ping.out 2>&1 &
[root@t-degroot1 tom]# kill %1
[root@t-degroot1 tom]# jobs
[1]+  Terminated              ping -c 5000 yahoo.com > ping.out 2>&1
[root@t-degroot1 tom]# jobs
```

So the first time after killing a job, the `jobs` command will show a terminated job. After that, the `jobs` command will no longer output the job


7. If you exit the tty all the stopped jobs and it's related processed will be killed

#nohup(=no hang up)

Launch a command immune to terminal hangups (such as closing a terminal, which sends a hangup signal)

1. How to run `nohup COMMAND`
2. How to make the command executed with nohup run in the background? -> `nohup COMMAND &`
3. Where does `nohup` send the STDOUT by default? -> *./nohup.out*
4. How to set a different output location? -> `nohup COMMAND > redirectlocation 2>&1`, the 2>&1 makes sure the STDERROR goes to the same location

#free

How to display the free and used memory on a system? -> `free [OPTIONS]`

1. What is the default output of free -> kilobytes
2. How to get the output in bytes? -> `-b`
3. How to get the output in megabytes -> `-m`
4. How to set an interval for refresh in Seconds? -> `-s INTERVALINSECONDS`

Swap space allows the kernel to offload some memory to the file system. So if swap space is used quite a lot, you probably need more memory.

The buffers and cache on the first line are used for incoming and outgoing data. Such as your keyboard.

The buffers/cache on the second line are used by programs for I/O via system calls


