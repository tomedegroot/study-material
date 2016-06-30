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
