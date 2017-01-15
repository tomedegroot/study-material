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

@todo read from p.42 in Linux book for all the kill, shutdown, halt, reboot and systemctl commands

In systemd we can configure to start services after other services has started (such as httpd after the network service)

##systemd units

[Systemd works with units.](https://www.digitalocean.com/community/tutorials/how-to-use-systemctl-to-manage-systemd-services-and-units) 

Types of units:

1. A service is a type of unit(suffixed with .service) (Apart from a .target, this is the only one you need to know)
2. A targetfile is also a unit(suffixed with .target) A target file is used to group/order other units such as services. These targets are used to describe a system state (like a runlevel)

Systemd loads units from 2 locations (see `man 5 systemd.unit`):
1. */usr/lib/systemd/system*
2. */etc/systemd/system*

Service files in location 1 have precedence over location 2

Check `man systemd.unit`

`systemctl -t help` -> get available unit types (`-t` specifies a type for systemctl`)

(Some units are in */lib/systemd/system/*, nothin found on this location)
##targets

In */usr/lib/systemd/user* we have different targets.

`systemctl get-default` -> get the current default target. The default target is in /etc/systemd/system/default.target and symlinks to another target (by default: */lib/systemd/system/multi-user.target*)

```
[root@t-degroot1 system]# systemctl get-default
multi-user.target
```

multi-user.target is the target that correspond with runlevel 2,3,4,5 in the old SysVinit system.

Targets use .wants to set the dependencies for a state. So the multi-user.target has ultimately a dependency that is comparable to runlevel 0-3 (see page 37)

#Using Systemd With Services And Service Unit Files

Example of a service target (in this case httpd):

```
[root@t-degroot1 system]# cat /usr/lib/systemd/system/httpd.service 
[Unit]
Description=The Apache HTTP Server
After=network.target remote-fs.target nss-lookup.target
Documentation=man:httpd(8)
Documentation=man:apachectl(8)

[Service]
Type=notify
EnvironmentFile=/etc/sysconfig/httpd
ExecStart=/usr/sbin/httpd $OPTIONS -DFOREGROUND
ExecReload=/usr/sbin/httpd $OPTIONS -k graceful
ExecStop=/bin/kill -WINCH ${MAINPID}
# We want systemd to give httpd some time to finish gracefully, but still want
# it to kill httpd after TimeoutStopSec if something went wrong during the
# graceful stop. Normally, Systemd sends SIGTERM signal right after the
# ExecStop, which would kill httpd. We are sending useless SIGCONT here to give
# httpd time to finish.
KillSignal=SIGCONT
PrivateTmp=true

[Install]
WantedBy=multi-user.target
```

##Using systemctl to interact with services

1. Getting info: 
  1. `systemctl status SERVICENAME` -> this shows some info from the journal
  2. `systemctl is-active` -> see if a service is active
2. Starting a service: `systemctl start SERVICENAME` (Executes ExecStart of the service unit)
3. Reload a service: `systemctl reload SERVICENAME` (Executes ExecReload of the service unit and will in general just reload the config files)
4. Restart a service: `systemctl restart SERVICENAME` this does ExecStop and then ExecStart. So a complete shutdown
5. Stopping a service: `systemctl stop SERVICENAME` (Executes ExecStop of the service unit)

##Starting a service by default at a specific target

How to make sure a service is started by systemd at boot? -> `systemctl enable SERVICENAME` Output:

```
[root@t-degroot1 system]# systemctl enable httpd
Created symlink from /etc/systemd/system/multi-user.target.wants/httpd.service to /usr/lib/systemd/system/httpd.service.
```
So now from the multi-user.target.wants there is a symlink to the httpd.service. The reason it chooses the multi-user.target is because it is in the install section of the service:

```
[Install]
WantedBy=multi-user.target
```
So `systemctl enable` looks at the install section, WantedBy key of a service unit.

See `man systemd` the 'SEE ALSO' section to see other relevant info, such as `man systemd.unit` (This describes a unit file such as httpd.service or a target etc.)

#Systemd Targets & Boot Targets

1. How to get the default target (The target entered in booting)? -> `systemctl get-default`
2. How to get a view of the dependencies of a target? -> `systemctl list-dependencies TARGETNAME`. Gives a tree overview:

```
[root@t-degroot1 system]# systemctl list-dependencies multi-user.target
multi-user.target
● ├─auditd.service
● ├─avahi-daemon.service
● ├─brandbot.path
● ├─chronyd.service
[...]
● ├─basic.target
● │ ├─microcode.service
```

3. How to get an overview of units? -> systemctl list-units [OPTIONS]
  1. How to only get certain types? -> `--type=LIST` -> systemctl list-units --type=target,service

Example:

```
[root@t-degroot1 system]# systemctl list-units --type=target
UNIT                   LOAD   ACTIVE SUB    DESCRIPTION
basic.target           loaded active active Basic System
...
```

4. How to get an overview view of all the targets, even if they are disabled? -> `systemctl list-unit-files --type=target --all`

##With sysvinit you could issue a `telinit RUNLEVELNUMBER` command to enter a runlevel. How to move from target to target in SystemD?

Some of the targets we have correspond to certain runlevels from SysVinit

How to enter a target? -> `systemctl isolate graphical.target` -> so you basically execute a set of dependencies

##How to set the default mode?

`systemctl get-default` -> get the current default target. The default target is in /etc/systemd/system/default.target and symlinks to another target (by default: */lib/systemd/system/multi-user.target*)

`systemctl set-default TARGET` -> set the default target.

```
[root@t-degroot1 system]# systemctl set-default graphical.target
Removed symlink /etc/systemd/system/default.target.
Created symlink from /etc/systemd/system/default.target to /usr/lib/systemd/system/graphical.target.
```

For backwards compatibility there are runlevelN.target file which symlinks to equivalent targets

```
ls -l /usr/lib/systemd/system | grep runlevel
lrwxrwxrwx. 1 root root 15 Sep 4 13:59 runlevel0.target -> poweroff.target
lrwxrwxrwx. 1 root root 13 Sep 4 13:59 runlevel1.target -> rescue.target
drwxr-xr-x. 2 root root 49 Sep 4 13:59 runlevel1.target.wants
lrwxrwxrwx. 1 root root 17 Sep 4 13:59 runlevel2.target -> multi-user.target
drwxr-xr-x. 2 root root 49 Sep 4 13:59 runlevel2.target.wants
lrwxrwxrwx. 1 root root 17 Sep 4 13:59 runlevel3.target -> multi-user.target
drwxr-xr-x. 2 root root 49 Sep 4 13:59 runlevel3.target.wants
lrwxrwxrwx. 1 root root 17 Sep 4 13:59 runlevel4.target -> multi-user.target
drwxr-xr-x. 2 root root 49 Sep 4 13:59 runlevel4.target.wants
lrwxrwxrwx. 1 root root 16 Sep 4 13:59 runlevel5.target -> graphical.target
drwxr-xr-x. 2 root root 49 Sep 4 13:59 runlevel5.target.wants
lrwxrwxrwx. 1 root root 13 Sep 4 13:59 runlevel6.target -> reboot.target
```

#Identify Enabled Services and Running Services

1. How to list all the units? -> `systemctl list-units [OPTIONS]`
2. How to list all the units files? -> `systemctl list-unit-files [OPTIONS]`

OPTIONS for `list-units` and `list-unit-files`:
1. `--type=LIST` -> list only the unit types from the list. `systemctl list-units --type=service,target`
2. `--all` -> also list of the non-active targets

Example: `systemctl list-units --type=service --all`

#wall

Send a message to all logged in users -> `wall [OPTIONS] [MESSAGE]`
1. How to suppress the the name of the user who sends the message? -> `-n` **Mnemonic**: Not show the username

1. Where can you find these messages from the past? -> */var/log/messages*
2. All the users can use wall, not just root

#journalctl

How to control the systemd journal? -> `journalctl [OPTIONS]`

1. `-n[=N]` -> Only show the last N lines, or if N is not given, the last 10 lines
2. `-x` -> Add eXplanatory help on the journal

#halt, poweroff, shutdown

```
halt terminates all processes and shuts down the cpu.

poweroff is exactly like halt, but it also turns off the unit itself (lights and everything on a PC). It sends an ACPI command to the board, then to the PSU, to cut the power.

shutdown is like poweroff, but it also runs the shutdown scripts.
```

1. `shutdown -k` -> only show the shutdown message to all logged in users. **Mnemonic** k is for Kidding
