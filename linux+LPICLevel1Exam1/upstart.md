#Upstart Overview

In older systems, sysvinit was used. This was the first process to run and started other services. sysvinit was also used to manage these services.

A limitation of sysvinit was it could not start services in asynchronously. sysvinit had to wait until service A was started before it could start service B. As the servers grew, this slowed down the systems. Newer init systems act much like sysvinit. A lot of commands are backwards compatible.

Upstart can start services in parallel (at the same time, asynchronously). It is still the first process to start (PID 1).

##scripts vs jobs

###sysvinit scripts

With sysvinit, you place bash script in */etc/rc[[:digit:]]/*:

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

These dirs correspond with runlevels. When the system entered a runlevel, it would execute the scripts in the corresponding dir.

`initctl list`

list all the init services = jobs. These services live in */etc/init.d/*

###upstart jobs

upstart is only used on Ubuntu, Debian is also going to SystemD just as CentOS.

Upstart uses upstart jobs. These jobs live in */etc/init/*

###events

upstart listens for events and if an event occurs it executes an event which listens to an event. Entering a runlevel is an event.

See for an upstart job which implements listening to events */etc/init/ssh*

(@todo telinit, getting the current runlevel)

###commands for interacting with a service

`restart SERVICENAME`

11.34
