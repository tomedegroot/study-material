#topic 110: Security

##Gaining acces to another account (such as root)

###`su`

`su [OPTIONS] [ACCOUNTNAME]` -> provides you with a **non-login** shell for the root user by default. Specify the account name to change to another user's account.

1. `-l` or just `-` -> get a login shell

* switching to another account form the user account **doesn't require a password**. This is so that the root user can test the correct config of an account.

###`sudo`

You don't want to give the root password (needed for root access via `su`) to a lot of people. Solution:

`sudo COMMAND`

The user only needs to:

1. Give his or her own password
2. Have the following line in the */etc/sudoers* `tom ALL=(ALL) ALL [FULLPATHTOCOMMAND...]`. 
  1. Edit via `visudo`
  2. If [FULLPATHTOCOMMAND] is given, the user can only execute that command via sudo

##Providing services on demand

Services cost resources. 3 ways of services running:

1. Always on
2. On demand
3. Off or disables

`inetd` and the newer `xinetd` allows you to run services on demand to limit resource usage. Very similar in usage. They are deamons to control other daemons (which slows down performance because `xinetd` needs to start another daemon).

Some services controlled via `inetd|xinetd` 

1. finger (used to provide login info)
2. imap (daemon to enable storing email on a server)
3. ktalk/ntalk (chat service)
4. rsh/rexec/rlogin (unsecure, replaced with ssh and scp)
5. telnet (sends passwords in plain text thus replaced via ssh)

###config

####`inetd`

*/etc/inetd.conf*, look it up in p. 577

####`xinetd`

*/etc/xinetd.conf* includes some settings:

1. The includdir ( */etc/xinetd.d*, (file name must match the service name in */etc/services*))
2. defaults for services, some settings:
  1. `instances = 50` -> max number of daemon instances allowed
  2. `cps = 50 10` -> max conn per second. If more than 50 connections in a second, the service is disabled for 10 seconds (will be in exam)

####`/etc/xinet.d/servicename`

An example file in */etc/xinet.d/* (see p. 580) has the following content:

1. service SERVICENAME
2. disable -> is the service disabled?
3. flags -> most common is REUSE which allows the port and service to accept multiple connections
4. socket type -> stream, dgram, raw etc.
5. wait -> for single threaded servers: grab the socket and wait
6. user -> user under which the server should run
7. server -> full path to daemon program
8. log_on_failure
9. access_times -> allow when the service can be accessed (handig for Reformatorisch Dagblad)
10. only_from -> list of hostnames, IPs etc

####`chkconfig`

The `disable` parameter can also be set via : `chkconfig telnet on|off`

After editing the */etc/xinetd.conf*, restart `xinetd` via `chkconfig` (however not necessary for */etc/xinetd.d/* since these files are read dynamically)

##TCP Wrappers

Works like a firewall to prevent certain hosts to access your tcp services. [Unlike iptables, tcp wrappers work on the application layer and operate in the user space and not in the kernel](http://wenchao-wang.blogspot.nl/2013/04/what-is-difference-between-iptables-and.html)

Goals: place a controlling daemon with instructions on who is allowed access and who is denied access for each service that runs on the machine.
 
###*/etc/hosts.allow* and */etc/hosts.deny*

In order for this to work, the service needs to be using the libwrap.a library. Apache doesn't use this library.

Using this library is the new way, using `tcpd` is the old way (p.581)

####General format: 

`daemons: hosts : option : option`

1. daemons:
  1. ALL (all services)
  2. service (a single service name)
  3. daemon, daemon (specify multiple)
2. hosts:
  1. ALL
  2. hostname
  3. ip
  4. PATHTOFILENAME (will then be referred to as list of hosts)

####Read order:

1. */etc/hosts.allow* is read first. If a match (on daemon and hosts), */etc/hosts.deny* is skipped
2. Read dynamically (no reloading after config change)
3. Files are read sequentially and the first that matches is used

####Strategy

1. Deny by default: add `ALL: ALL` in */etc/hosts.deny* and only allow access from some hosts in */etc/hosts.allow*
2. Allow all: don't make a */etc/hosts.allow* file

See p.584 for diagrams on security

####Using Rule Options

On the end of the line you can place options. 3 point out:

1. `severity auth.info` -> log the blocked host
2. `twist COMMAND` -> boobytrap the service by outputting the result of a different command. Example `twist echo "je moeder"`
3. `spawn COMMAND` -> do allow access, but execute a command (such as emailing info)

###Understanding Permission Problems

[Full info](https://github.com/tomedegroot/study-material/blob/d3a578dcf62640c07b03e4314886a552c2b394f2/LPIC101/managingFilesInLinux.md)


The setuid, setgid, and sticky bit can be set using chmod where:

```
1 = sticky bit, files in folder with this bit can only by deleted by its owner
2 = SGID, execute program as the group or if on dir, new files in that dir inherit ownership
4 = SUID, execute program as the owner
```
For example to set the setuid bit along with permissions 766:

`chmod 4766 filename`

And to search:

`find -perm +7000` to find files where all of perm bit set and use `find -perm /7000` to find files where any of the named perm bits are set.

