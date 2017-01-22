#Upstart Overview

In older systems, SysV init was used. This was the first process to run and started other services. SysV init was also used to manage these services, and this would be done via the `service` and `systemctl` commands

A limitation of SysV init was it could not start services in asynchronously. SysV init had to wait until service A was started before it could start service B. As the servers grew, this slowed down the systems. Newer init systems act much like SysV init. 

Upstart can start services in parallel (at the same time, asynchronously). It is still the first process to start (PID 1).

##SysVinit vs Upstart

SysVinit is the old tool for managing the system, upstart is the new tool for Ubuntu

###SysV init scripts

With SysV init, you place bash script in */etc/rc[[:digit:]]/*:

```
root@t-degroot2:/etc# ls | grep rc[[:digit:]]
rc0.d
rc1.d
rc2.d
rc3.d
rc4.d
rc5.d
rc6.d
```

These dirs correspond with runlevels. When the system entered a runlevel, it would execute the scripts in the corresponding dir and these scripts start the daemon services

The services can be listed via `service --status-all` and they live in */etc/init.d/*

###upstart jobs

Upstart is only used on Ubuntu, Debian is also going to SystemD just as CentOS.

Upstart uses upstart jobs. `initctl list` lists all the jobs. These jobs live in */etc/init/*

*(There is backwards compatability, so in Ubuntu there a both the SysV services and the Upstart jobs and most can be interacted with in the same way)

###events

upstart listens for events and if an event occurs it executes an event which listens to an event. Entering a runlevel is an event.

See for an upstart job which implements listening to events */etc/init/ssh*


###commands for interacting with a service via upstart

`restart SERVICENAME` (Equivalent of `service SERVICENAME restart`)

###test jobs

####create jobs

Enter the following in */etc/init/test.conf*

```
description     "Our test job"

start on runlevel [2345]
stop on runlevel [!2345]

expect fork
respawn

script
        logger -f /var/log/syslog "Hello world $(date)"
end script
```

####test conf file

Test the conf file:

```
root@t-degroot2:/etc/init# init-checkconf test.conf 
File test.conf: syntax ok
```

####start the job

Start the job


