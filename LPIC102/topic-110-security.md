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

```
find . -perm -664 -> Search for files which have read and write permission for their owner and group, and which other users can read, without regard to the presence of any extra permission bits (for example the executable bit). This will match a file which has mode 0777, for example.

find . -perm /222 -> Search for files which are writable by somebody (their owner, or their group, or anybody else).
```

1. `find -perm -7000` to find files where all of named permission bits are set, without regard to any other bits that might be set (**m** `-` = cumulatief), so in this case all the perm bits must be set because they are all named
2. `find -perm /7000` to find files where any of the named perm bits are set, without regard to any other bits that might be set (**m** `/` = facultatief) (can be written as `+7000`), so in this case any of the special perm bits might be set

##GnuPG

Used to encrypt data via private and public keys

1. To create these keys: `gpg -gen-key`
2. The keys are stored in you home dir (list via `gpg --list-keys`)
3. To convert the binary key to a text based key: `gpg -a -o PUBKEYTEXTFILE --export KEYIDENTIFIER`
4. To encrypt: `gpg -e RECIPIENT FILE`

Another use of a key is to verify a package: `gpg -verify PACAKGENAME`

See p. 590 for more commands (not sure if I need to know all the commands, just know generating and -verify)
1. To encrypt a file: `gpg -e recipient file`

##SSH

Some ssh programs:

1. `ssh` -> the agent
2. `scp` -> agent to copy via SSH
3. `sshd` -> the SSH daemon
4. `ssh-agent` -> is a wrapper on `ssh` and provides authentication when needed
5. `ssh-add` -> load keys into the agent

Config files:

1. Global config: */etc/ssh/sshd_config
2. The hosts private keys: */etc/ssh/ssh_host_[dr]sa_key (mode 600, thus protected from everbody reading)
3. The hosts public keys: */etc/ssh/ssh_host_[dr]sa_key.pub (mode 644, should be readable by anyone, but only writable for root)
4. */etc/nologin* -> if present, only the root user can login via ssh and non-root users see the contents of */etc/nologin*

Known hosts:

2 files:

1. */etc/ssh/ssh_known_hosts* (World readable, root writable) -> used by server to check the public key of a host trying to connect (not enable by default)
2. *~/.ssh/known_hosts* (Owned and writable for the user) -> used by client to store the public key trying to connect to

If you try to connect to a new host, you are asked if you want to add the servers public key. This is then added to *~/.ssh/known_hosts*

To login: `ssh -l tom REMOTEHOST`

###Logging in without a password

*~/.ssh/authorized_keys* -> This file holds a list of authorized public keys for servers. When the client connects to a server, the server authenticates the client by checking its signed public key stored within this file.

See p. 596 for notes on how to log in without a password

To generate a key: `ssh-keygen -b 1024 -t rsa`

##Special Commands

1. See which users are using a file: `fuser FILEORSOCKER`
2. List open files: `lsof`
