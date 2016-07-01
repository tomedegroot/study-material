#Where Data is Stored#

##Kernel##

1. Is a UNIX-like OS.
2. The kernel is responsible for managing every other piece of software on a running Linux computer. Lowest level of easily replacable software that interfaces with the computer hardware.
3. The kernel is loaded very early in the boot process and is responsible for running every other piece of software on the computer.
4. To maintain order in the chaos of system processes, the kernel imposes order by using **hierarchy**
5. When the system boots, the kernal runs one process called the init process which starts /sbin/init that in turn manages child processes. This could enter in a subset of many processes, such as:

	   init
	    |
    login-------login
      |           |
     bash        bash
      |           |
  ps-----ls   cp-----vi

##Processes##

1. Every process has a PID
2. Every parent process has a parent PID (PPID)
3. Identify PID and PPID via `ps`

1. `ps` -> report a snapshot of the current processes. Also get the command (CMD) which initiated the process
  1. `-u USER` ->  get processes for a user
  2. `--forest` -> see child and parent relationships
  3. `-U` -> give more info, such as %CPU, %MEM, START
  4. `-a` -> all with tty, except session leaders
  5. `-x` -> processes without controlling ttys
2. `top` -> interactive version of ps. When running enter commands:
  1. `h` of `?` -> display help
  2. `k` -> kill a process
  3. `r` -> renice, change a process' priority
  4. `p` -> sort by CPU usage (default)
  5. `m` -> sort by memory usage

Top also provides load average (a measure of demand on CPU) by applications (at the first line of the screen is the load average)

For example:
  1. A load average of 0 is a system that not programs are demanding CPU time.
  2. A load average of 1 with one program running a CPU intensive task.
  3. A system that has higher load averages on a single CPU system reflect programs competing for available CPU time.
  4. On a system that multuple cores, load average can reach the number of cores available. A system with 4 cores and a load average of is demanding exactly as much CPU time as the computer has available.

A high load average could indicate that a program is hung (= unresponsive). Use top to find them and kill them.

You can also use top to find a program that has a high and increasing memory usage. This indicates a memory leak. A program than requests the kernel for memory, but fails to return the memory space. This is a bug in a program.

Use `free` to generate a report on the memory. Use -h to get human readable output in MB's

##syslog, klog and dmesg##
