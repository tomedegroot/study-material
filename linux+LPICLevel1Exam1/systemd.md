#SysVinit vs Systemd

##SysVinit

SysVinit comes from the first commercial version of Unix, [SystemV](https://en.wikipedia.org/wiki/UNIX_System_V). This OS needed an init program which started services for this OS. This was [SysVinit](https://en.wikipedia.org/wiki/Init). These services could also be interacted with via `service SERVICENAME start|status|stop`. The `service` command just calls a */etc/init.d/SCRIPT* with the appropriate command.

###runlevels

SysVinit is build around runlevels (0-6):

To get the runlevel:
1. `runlevel`
2. `who -r` -> get it in plain English

Going to a runlevel via `init N` where N is the runlevel. For older systems there is a `telinit` command which symlinks to `init`

##Systemd

Systemd allows starting processes in parallel (in contrast with SysVinit). SystemD has pid 1. It's the first process which starts a lot of other processes.

In Systemd there are no runlevels; Systemd uses targets.

Systemd controls shutdown, cron, journalctl and other low level components. For backwards compatibility, the `shutdown` command is notw a symlink to systemctl (systemctl is the command to *control* the systemd system`):

```
[tom@t-degroot1 sbin]$ ls -al /usr/sbin | grep shutdown
lrwxrwxrwx.  1 root root          16 Dec 14 20:43 shutdown -> ../bin/systemctl
```

In older programs, shutdown was it's own program

In systemd we can configure to start services after other services has started (such as httpd after the network service)

##systemd.unit

[Systemd works with units.](https://www.digitalocean.com/community/tutorials/how-to-use-systemctl-to-manage-systemd-services-and-units) 

Check `man systemd.unit`. A unit is a config file for a service or target.

`systemctl -t help` -> get available unit types (`-t` specifies a type for systemctl`)

See also the notes in the next lesson

##targets

In */usr/lib/systemd/user* we have different targets.

`systemctl get-default` -> get the current default target. The default target is in /etc/systemd/system/default.target and symlinks to another target

```
[root@t-degroot1 system]# systemctl get-default
multi-user.target
```

multi-user.target is the target that correspond with runlevel 2,3,4,5 in the old SysVinit system.

Targets use .wants to set the dependencies for a state. So the multi-user.target has ultimately a dependency that is comparable to runlevel 0-3 (see page 37)

#Using Systemd With Services And Service Unit Files

Types of units:

1. A service is a type of unit(suffixed with .service)
2. A targetfile is also a unit(suffixed with .target) A target file is used to group/order other units such as services. These targets are used to describe a system state (like a runlevel)

Unit files live in 2 locations:
1. */usr/lib/systemd/system*
2. */etc/systemd/system*

Service files in location 1 have precedence over location 2

@todo read from p.42 in Linux book for all the kill, shutdown, halt, reboot and systemctl commands

