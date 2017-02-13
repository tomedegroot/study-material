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

If you are using NTP, it will write the system clock to the hardware clock every 11 minutes.

###Network Time Protocol (NTP)



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


