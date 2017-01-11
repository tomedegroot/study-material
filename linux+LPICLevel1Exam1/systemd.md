#SysVinit vs Systemd

##SysVinit

SysVinit comes from the first commercial version of Unix, [SystemV](https://en.wikipedia.org/wiki/UNIX_System_V). This OS needed an init program which started services for this OS. This was [SysVinit](https://en.wikipedia.org/wiki/Init). These services could also be interacted with via `service SERVICENAME start|status|stop`. The `service` command just calls a */etc/init.d/SCRIPT* with the appropriate command.

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

Check `man systemd.unit`. A unit is a config file for a service. Some of these units live in */usr/lib/systemd/*

`systemctl -t help` -> get available unit types (`-t` specifies a type for systemctl`)

##targets

In */usr/lib/systemd/user* we have different targets.

`systemctl get-default` -> get the current default target.

```
[root@t-degroot1 system]# systemctl get-default
multi-user.target
```

multi-user.target is the target that correspond with runlevel 2,3,4,5 in the old SysVinit system.

##services

In */usr/lib/systemd/system* are the services which are managed via systemd and thus controlled via `systemctl`.

##runlevels
@todo learn about runlevels. You need to know this for the LPIC Exam.

#Using Systemd With Services And Service Unit Files

[Systemd works with units.](https://www.digitalocean.com/community/tutorials/how-to-use-systemctl-to-manage-systemd-services-and-units) 

1. A service is a type of units(suffixed with .service)
2. A targetfile is also a units (suffixed with .target) A target file is used to group other units and with this describe a system state (much like a runlevel)

Unit files live in 2 locations:
1. */usr/lib/systemd/system*
2. */etc/systemd/system*

Service files in location 1 have precedence over location 2

1.23
