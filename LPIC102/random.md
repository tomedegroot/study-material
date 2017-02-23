##Random

1. `last` -> see:
  1. Who logged in
  2. Host of the logged in users
  3. Reboot
2. 

##Configs

###X11

1. */etc/X11/xorg.conf.d/*
2. */usr/share/X11/xorg.conf.d/*

1. XDM, */usr/bin/xdm/*, */etc/X11/xdm/*
2. KDM, */usr/bin/kdm/*, */etc/kde/kdm/*
3. GDM, */usr/sbin/gdm/*, */etc/gdm/*

###Timezones

1 `tzconfig` -> GUI to set timezones

###`useradd`

1. */etc/default/useradd* -> defaults for `useradd`


###anacron

1. */etc/anacrontab*

###ntp

1. */etc/ntp.conf*

###logging

1. */etc/[r]syslog.conf*

1. */etc/systemd/journald.conf*
2. */etc/journald.conf*

1. */etc/logrotate.conf*
2. */etc/logrotate.d/*

###mail

1. */etc/aliases*

###printing

The most important config files for cupsd (all in */etc/cups/*)

1. *cupsd.conf* -> main config file. Editable via the web 
2. *cupsd.conf.default* -> if you mess up *cupsd.conf* use this one to restore
3. *printers.conf*-> conf file for each printer on the system
4. *classes.conf* -> holds the classes (groups) of printers. [Jobs send to a class are forwarded to the first available printer in that class.](https://opensource.apple.com/source/cups/cups-23/doc/sam.shtml#PRINTER_CLASSES)
5. *ppd/* -> a dir with all the postscript description files 

