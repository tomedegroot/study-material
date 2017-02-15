#Topic 108: Essential System Services

##108.1:Maintaining Time

Time is very important: some protocols will no longer work if the clock is even a few seconds off.

###clocks

Linux has two clocks: 

1. The **system clock** is part of the Linux kernel
2. The hardware clock, called the **real-time clock (rtc)**

These two times differ because of a phenomenom that is called **drift**. A clock drifts because it runs slightly slower or faster than the real time.

####system clock

#####Get the system clock time via `date`

`date `[OPTIONS] ['+FORMAT']`

1. By default gets the clock in your default time zone
  1. Extra: from the other lesson: set the $TZ variable to control the timezone for 1 command: `[root@t-degroot1 tom]# TZ="Europe/Amsterdam" date`
2. How to get the time zone in UTC (Universal Coordinated Time): `date -u`
3. Specifying formats with `'+FORMAT'` where `FORMAT` is a literal and interpreted % symbols:
  1. `%y` -> two digit years
  2. `%Y` -> four digit years
  3. `%C` -> century in 2 digits (so like '%Y', but without the last 2 digits)
  3. `%m` -> two digit month
  4. `%d` -> two digit day
  5. `%H` -> current time in 24 hours
  6. `%M` -> current minute such as 09
  7. `%S` -> current second such as 59
  8. `%s` -> The current time since epoch in Seconds, so to get a timestamp in a script: `NOW=$(date '+%s')`. 
  9. `%%` -> literal percentage
  
Example:

```
[tom@t-degroot1 ~]$ date '+This year is: %Y'
This year is: 2017
```

#####Set the system clock time

`date MMDDhhmm[[CC]YY][.ss]` which means:

1. So minimum amount is 'month, day, hour, minute'.
2. Optional: the year without or without century (= in 2 or 4 digits)
3. Optional: the seconds in 2 digits 

####hardware clock

`hwclock` -> get the time of the hardware clock and after it the difference with the system clock:

```
[root@t-degroot1 tom]# hwclock
Mon 13 Feb 2017 09:57:03 PM CET  -0.551346 seconds
```

The hardware clock doesn't know timezones. On installing you can choose to run the hardware clock in UTC or Localtime. This is stored in */etc/adjtime*:

```
0.0 0 0.0
0
UTC
```

The last line is either `LOCAL` or `UTC` to see to which time it is set. If the hardware clock uses UTC, you check it via `hwclock -u`

####Sync between system time clcok and hardware clock

1. Write the system clock to the hardware clock: `hwclock -w` or `hwclock --systohc` **most important**
2. Write the hardware clock to the system clock: `hwclock -s` or `hwclock --hctosys`

Usually you want to use the system clock as the canonical for consistency.

###Network Time Protocol (NTP)

NTP: use remote server to set the correct time on a computer.

reference clocks are official clocks with the correct time (usually from the government or agency etc.)

Hierarchy of clocks:

1. stratum 1 server (gets time **directlu** from reference clock)
2. stratum 2 server (gets time from stratum 1)
3. stratum 3 gets from stratum 2 etc. (p. 505)

####set the ntp time manually

`ntpdate SERVER` -> updates the time 1 time

You can use the pool.ntp.org which is a pool of ntp servers behind a DNS alias: `ntpdate pool.ntp.org`

[More info on pool.ntp.org](http://www.pool.ntp.org/en/)

####`ntpd`

`ntpd` continually adjusts the time.

Config file: */etc/ntp.conf*

Parts of the config:

```
driftfile /var/lib/ntp/drift
...
server 0.centos.pool.ntp.org iburst
```

1. driftfile tracks local clock drift over time, which allows ntpd to compensate
2. server line gives a possible server to get the time from. More server is good, because of redundancy.

`ntpd` has a mode where it can sync to the hardware clock every 11 minutes, but don't need to know for the exam how to do this

#####Monitoring `ntpd`

`ntpq` -> query ntp interactively, 2 commands:

1. `peers` -> give meta details on the servers defined in */etc/ntp.conf*
2. `association` -> give details of the servers defined in */etc/ntp.conf*

##108.2: System Logging

2 log systems:

1. The older syslog
2. The newser systemd's journal

###syslog

3 ways of logging to syslog:

1. within an application via the `syslog` library call
2. use the `logger` command
3. over the network via a syslog server

####syslog severities and facilities

Syslog severities (level: tag: meaning), (**know the level and their meaning**), (p.509):

0: emerg: emergency
1: alert: alert
2: crit: critical
3: err: error
4: warn: warning
5: notice: notice
6: info: informational
7: debug: debug 

Syslog facilities(tag:type):

1. kern: kernel message
2. user: random user level message
3. mail: Email server
4. daemon: daemons
5. auth: security log **which is public**
6. syslog: internal messages for syslog
7. lpr: printing
8. cron: scheduled jobs
9. authpriv: security log **which is private**
10. local0-7: eigth differnt user-definable facilities

[each facility has it's own facility code](https://en.wikipedia.org/wiki/Syslog#Facility) which is used by systemd's journal to as value in the SYSLOG_FACILITY field of an entry

####syslog message distribution

See the scheme on p.511 to see how `syslogd` distributes messages. Messages go to destinations based on the facility and severity of the message. Messages can be:

1. broadcasted (emergencies)
2. files
3. forwarded to another server

####`logger` command

`logger [OPTIONS] message`

So `logger 'Hey!'` genereates the following line:

```
Feb 14 20:49:10 t-degroot1 tom: Hey!
```

So you have 'timestamp hostname username: message'

Possible options:

1. `-i` -> send the pid
2. `-p FACILITY.SEVERITY` -> send the facility and the severity

####configuring `syslogd`

p.512: The syslogd package is part of sysklogd, which is an amalgation of the two components in the package:

1. syslogd -> handles logging as described
2. klogd -> listens to kernel messages and forwards it tot syslogd

Config of syslogd: */etc/syslog.conf*. Example:

```
A configuration file might appear as follows:

# Log all kernel messages, authentication messages of
# level notice or higher and anything of level err or
# higher to the console.
# Don't log private authentication messages!
*.err;kern.*;auth.notice;authpriv.none /dev/console

# Log anything (except mail) of level info or higher.
# Don't log private authentication messages!
*.info;mail.none;authpriv.none         /var/log/messages

# The authpriv file has restricted access.
authpriv.*                             /var/log/secure

# Log all the mail messages in one place.
mail.*                                 /var/log/maillog

# Everybody gets emergency messages, plus log them on
# another machine.
*.emerg                    *
*.emerg                    @arpa.berkeley.edu

# Root and Eric get alert and higher messages.
*.alert                    root,eric

# Save mail and news errors of level err and higher in a
# special file.
uucp,news.crit             /var/log/spoolerr
```

So the some rules:

1. structure is: `FACILITY.SEVERITY [-]DESTINATION[; [-]DESTINATION...]`
2. wildcards can be used to match any FACILITY or SEVERITY
3. a wildcard on the DESTINATION means every logged in users sees the message
4. a dash before destination means the it shouldn't write the log entry to disk, but should the kernel write the message to disk when it has time (to improve performance)
5. an '@' symbol means it should be forwarded to another server. For example: `*.info @logserver@example.com`

In order to let syslog accept message over the network, start it with: `syslog -r`

####Common log and their location:

1. */var/log/messages* -> general purpose messages that do no belong anywhere else 
2. */var/log/maillog* -> mail
3. */var/log/secure* -> security logs (login attempts etc.)
4. */var/log/cron* -> logs of cron
5. */var/log/xferlog* -> ftp log

####other syslog implementations (so other packages)

1. rsyslogd -> very fast, support for plugins and store in a database (is running in CentOS)
2. syslog-ng -> same as rsyslogd but the configuration syntax is reworked

CentOS7 uses `journald` to log and forwards some messages to `rsyslogd` and the config file of `rsyslogd` is in */etc/rsyslog.conf*

###systemd's journal

1. Logs everything to 1 binary file.
2. Log additional metadata, such as the name of a method and the line number of a file
3. journal doesn't have the ability to forward to a remote server, [but you can forward a log message to sys which forward it to a remote server as described above](https://www.loggly.com/blog/why-journald/)
4. Backwards compatible with syslog, so if an application can log to syslog, it can also log to journal



####journald config 

The config file is in */etc/systemd/journald.conf*

Here is an example line:

```
[Journal]
#Storage=auto
...
#ForwardToSyslog=yes
#SystemMaxFileSize=200M
```

See [log and settings in the log info](https://www.loggly.com/ultimate-guide/linux-logging-with-systemd/)

After making changes, restart journald via: `systemctl restart systemd-journald`

####the log

#####log location

journald stores everything in 1 files. The location of this file is:

1. By default: */var/log/journal/*
2. If in the settings the storage is set to auto and */var/log/journal* doesn't exists, then [the log is in](https://loggingguide.wpengine.com/linux-logging-with-systemd/) */run/log/journal*

#####rolling log

`journalctl` keeps a rolling log. This means that expires old entries as the log hits it's limit. By default the limit is 10% of the file system. Set this is in the confi with ``SystemMaxFileSize`

#####querying the journal

To query the journal: `journalctl [FIELD=VALUE] [OPTIONS]`

In `journalctl` you can filter on any of the FIELDS. Some common FIELDS:

1. MESSAGE=STRING -> message of the log entry
2. SYSLOG_IDENTIFIER=STRING -> identifier of the program or user who logged the entry
3. SYSLOG_FACILITY=NUMBER -> the facility number of the message
4. PRIORITY=NUMBER|STRING -> the priority is the severity of the message

Example: You can use the SYSLOG_IDENTIFIER to only search for the output of a certain application or user. Example: `journalctl SYSLOG_IDENTIFIER=sshd`

OPTIONS:

1. `-r` -> see the log in reverse order
2. `-e` -> see only the end of the log
3. `-f` -> follow, just like `tail -f`
4. `-n N` -> get only N entries
4. `-u` -> specify the systemd unit who wrote the log, example `-u sshd`
5. `-o` -> specify the output
  1. `-o verbose` -> get verbose output with all the log fields
  2. `-o json` -> get the output in JSON with all the variables in it such as SYSLOG_IDENTIFIER and SYSLOG_FACILITY

Example of combination: `journalctl SYSLOG_IDENTIFIER=tom MESSAGE=hello -n 1 -o verbose`



##108.3:Mail

Even though some enitities in a mail chain are combined nowadays, the officel entities in the mail chain are:

1.Mail User Agent (MUA), is the client for receiving and sending mail. Sending mail to: 

2.Mail Transfer Agent (MTA), forwards mails to other MTA's via SMTP. 

Some MTA's:

  1. Sendmail (monolithic)
  2. Postfix (compartments, so multiple daemons)
  3. Qmail (compartments, so multiple daemons)
  4. Exim (monolithic)

MTA uses DNS to look up the Mail Exchange records via: `host -t mx DOMAINNAME`

3.A Mail Delivery Agent (MDA) receives a mail from an MTA via SMTP and delivers it to a local mailbox.(usually a server)

  1. MTA and MDA are usually combined
  2. At the MDA there can be aliases so sales@example.com is forwarded to multiple e-mail addresses.
  3. The MDA must write the e-mail to some place where the mail server can access it.

4.A Mail User Agent(MUA) reads the mail server. 
  1. In practice this is the same MUA as is used for sending mails
  2. A MUA cannot use SMTP to get message, since SMTP is only for sending e-mails. POP and IMAP are used by the MUA to read the mail server
 
So what happens in practice is that an MTA receives a mail, passes it on to an MDA which passes it on to a mail server and a MUA connects to a mail server to get the e-mails.

To send a simple mail `echo "Hello" | sendmail tom`

###Aliases for forwarding

####Normal aliases

In */etc/aliases*, aliases can be configured as ` alias: recipient1, recipient2`

```
security:	root
```

After this file has saved, run `newaliases` to update the */etc/aliases.db* file which is compiled and used for speed advantages

####Other alias

You can place an e-mailaddress to forward to an e-mail address, file or script (with `|`)

```
tom: t.degroot@example.com
issues: /var/log/issues.log
support: /usr/local/bin/new_ticket.sh
```

And always run `newaliases`

####User defined forwarding

If a user places *.forward* in there $HOME it can containing forwarding rules. Similar to */etc/aliases* but it ommits the alias part since a *.forward* is already tied to one user:

```
tom@example.com
```

####Managing the mailque `mailq`

`mailq` -> look at the mail queue in */var/spool/mqueue*

####Mail log

The mail log is in */var/log/maillog*

##108.4: Managing Printers

[spooling is a combination of buffering and queueing](https://en.wikipedia.org/wiki/Spooling). The spooler maintains an orderly sequence of jobs and feeds it to another entity (such as peripheal as a printer) and this acts as a mediator. The term originates from the spool, a [cylindrical device on which magnetic tape or rope is round](http://www.dictionary.com/browse/spool) and thus also works as a mediator.

So just know that a printer and it's queue are two different things

###Background

2 older, but still available systems:
  1. BSD line printer remote (`lpr`)
  2. SysV Unix Line Printer (`lp`)

Later, some companies came up with the Internet Printing Protocol (IPP)

###CUPS

The Common Unix Printing System (CUPS) is built around a daemon and has 2 responsibilities:

1. Listen to print requests (coming in via LPR or IPP. LPR is translated to an IPP request) [Request come in on the line printer daemon and are send via lpr](http://www.computerhope.com/unix/ulpr.htm)
2. Manage printers and queues

Communication with the CUPS daemon is done via Internet Printing Protocol, which is built on top of HTTP. This accounts for both resposibilities.

(See p. 469 for the complete flow)

Config file: */etc/cups/cups-pdf.conf*

####CUPS web interface
 
See p. 477 the exam only has questions on the CLI tools, BUT the web interface gives you a good overview of possible statusses of printers and job options

Listens by default to port 631.

[In order to let CUPS bind its socket to a port, SELinux should be configured properly, or be disabled temporarily](http://stackoverflow.com/a/34875267/1941737) and check [for the right Cups config](http://thismightbehelpful.blogspot.nl/2008/09/remote-access-to-cups-web-interface.html)

####Printers

A printer in CUPS can have 4 states:

1. Idle
2. Processing (CUPS is sending data)
3. Stopped (An error happened)
4. Paused (An administrator has suspended printing for this printer) 

####Jobs

Jobs have three options:

1. Hold
2. Cancel
3. Move job

###Command line tools for interacting with the CUPS daemon (lpd)

##m##: `lp` uses the Unix thinking term DESTINATION, thus -d. The more modern `lpr` uses the more modern term PRINTER, thus -p

####`lp` and `lpr` -> print files

`lp|lpr [OPTIONS] [FILES]`

1. How to select the printer (default is the env variable `$PRINTER`):
  1. `lp` : `-d DESTINATION` : `echo "Printed via lp" | lp -d Cups-PDF`
  2. `lpr`: `-P DESTINATION(P for Printer)` : `echo "Printed via lpr" | lp -P Cups-PDF`
2. How to print multiple copies(but all in 1 job, so just N times the pages in one job)? 
  1. `lp` -> `-n N`, so `-n 2` prints 2 copies
  2. `lpr` -> `-# N`, so `-# 3` prints 3 copies #m#: the dash options is more modern, thus `lpr`

Read from STDIN or FILES

####`lpstat` -> provide info on printer config

`lpstat OPTIONS`

1. `-a` -> get info on all printers
2. `-d` -> display name of Default printer
3. `-r` -> indicate wheter CUPS is Running
4. `-s` -> Provide status Summary of how the system is configured
5. `-t` -> Provivde more detailed status lisT

####`lpq` -> provide info on the job queue

`lpq [OPTIONS]` -> get job queue info

1. By default, only the queue for the default printer will be show, to change this:
  1. `-a` -> show for All printers
  2. `-P DESTINATION` -> show for DESTINATION, new thus `-P`

####Remove a print job

`lprm [OPTIONS] [JOBNUMBER]` 
  
1. JOBNUMBER -> remove JOBNUMBER (prints nothing on success) example: `lprm 3`
2. `-a` -> remove all print jobs in the queque
3. `-P DESTINATION` -> specify queue of destination, new thus `-P`
4. No args: current job on give queue will be cancelled

Alternative is `cancel [DESITNATION]- [JOBNUMBER]`

1. JOBNUMBER -> remove JOBNUMBER (prints nothing on success) example: `cancel 3` 
2. DESTINATION` -> specify queue of destination

###CUPS command line tools

####Accept/Reject jobs for a printer queue

`cupsaccept|cupsreject DESTINATION`

Accept/Reject all jobs for a destination queue, thus generating an error when printing to it

####Enable/disable the printer itself

`cupsenable|cupsdisable DESTINATION` -> enable or disable the printer itself (use `lpstat -t` to see the status)

####Control the CUPS daemon: `cupsctl`

`cupsctl [OPTIONS]` -> without opions it give you a list of config options

1. The web interface only allow local administration by default. To change this:
  1. To allow remote administration: `cupsctl --remote-admin`
  2. And to revert: `cupsctl --no-remote-admin`
2. Allow connecting to the daemon from outside the local network:
  1. `cupsctl --remote-any`
  2. `cupsctl --no-remote-any` to revert
3. To allow any user to cancel any jobs (for more smaller informal networks): `cupsctl --user-cancel-any`

All these configs edit the */etc/cups/cupsd.conf*

####Config files for cupsd

The most important config files for cupsd (all in */etc/cups/*)

1. *classes.conf* -> holds the classes (groups) of printers. [Jobs send to a class are forwarded to the first available printer in that class.](https://opensource.apple.com/source/cups/cups-23/doc/sam.shtml#PRINTER_CLASSES)
2. *cupsd.conf* -> main config file. Editable via the web 
3. *cupsd.conf.default* -> if you mess up *cupsd.conf* use this one to restore
4. *printers.conf*-> conf file for each printer on the system
5. *ppd/* -> a dir with all the postscript description files 


