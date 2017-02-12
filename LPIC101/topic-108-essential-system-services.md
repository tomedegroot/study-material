#Topic 108: Essential System Services

##Managing Printers

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

1. *classes.conf* -> holds the classes (groups) of printers. If you print to a class, you print to the first available printer in that class.
2. *cupsd.conf* -> main config file. Editable via the web 
3. *cupsd.conf.default* -> if you mess up *cupsd.conf* use this one to restore
4. *printers.conf*-> conf file for each printer on the system
5. *ppd/* -> a dir with all the postscript description files 


