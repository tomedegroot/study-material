#Topic 109: Networking Fundamentals

##109.1: Fundamentals of Internet Protocols

###Introduction on IP

Hosts are the smallest unit on a network: one single entity that can respond to a ping.

Subnets are logical groupings of hosts on a network based on their addressing.

Segments are physical groupings of hosts on a network based on how they are connected via hubs, switches and wires.

Great analogy:

1. A host is a house on a street.
2. A network is the street.
3. A gateway is where two streets intersect. (a gateway is a router)

####Necessary config to operate in a network:

1. An IP Address
2. A Network Mask
3. A Gateway Address

####Networks and host relationship in the IP address

An IP addres (of 198.168.1.200) is broken up into two parts:

1. The network address (192.168.1) (analogy: the street address)
2. The host address (200) (analogy: the house address)

What determines the network part of the IP address is determined by subnetting

####IP Address Classes (Key Topic) & private network ranges:

The first three bits of the first octet determine what class the IP address is and are confusingly also a part of the network address itself

The class the IP address is in determin which part of the address is the network part and which part of the address is the host address

Why create the address classes? -> The internet is a network of networks. And different networks need to be of different sizes (e.g. need to place more hosts than other networks):

```
IP Address classes were the original organizational structure for IP addresses. The specific address class would determine the maximum potential size for a computer network. The address class would define which of the specific bits of the address would be used to identify the network and network identification, the bits to identify the host computer and host ID, and total number of host subnets permitted per network. Five total classes of IP addresses were defined, class A through E. Although the IP class term will commonly be used to describe the difference between one network and another, the practical use of addressing is not commonly used any more. It has been replaced with classless addressing where a netmask can be assigned to any IP address range.
```

5 classes:

1. 1 - 126  : 126 class A networks: 16.777.216 host addresses
2. 128 - 191 : 16.382 class B networks : 65.536 host addresses 
3. 192 - 223: 2.097.150 class C networks : 254 host addresses: 

To calculate: For class B network, the first two octects are the network part of the IP address. There are only 192 - 128 = 64 combinations in the first octect for class B networks (that is because the first octet is used to both indicate it is a class B network(remember, this was before CIDR was devised) and to give the first octect of the network address) The second octect can be used to also indicate the network address, because it is a class B network. Thus there are 64 * 2 ^ 8 = 16,384 class B networks. However, [2 gets substracted, because of the effective subnet, thus the total is 16,382](https://www.pantz.org/software/tcpip/subnetchart.html) @todo: why do 2 get substracted and what is an effective subnet?

So what about the private network ranges (192.168/16, 172.16/12 & 10/8)? [These were 'cut out from' the classes as an afterthought to create private networks (that is a network that is not on the internet, which is a network of networks. That way IP could also be used for private networks)](http://networkengineering.stackexchange.com/questions/5825/why-192-168-for-local-addresses). So basically 192.168/16 is **not** a part of the internet.

More info on classes:

1. https://docs.oracle.com/cd/E19455-01/806-0916/6ja85399v/index.html
2. https://technet.microsoft.com/en-us/library/cc940018.aspx

####Network Masks

A network masks sets where the network bits of the IP address ends and the host bits begins. Each class comes with a default network mask:

1. A: 255.0.0.0 or /8
2. B: 255.255.0.0 or /16
3. C: 255.255.255.0 or /24

The '/N' notation sets the number of bits that represent the network part. This form of notation is referred to as Classless Inter-Domain Routing (CIDR). It's called classless because one can determine the network and host part of an address not on the first 3 bits, but on the subnet mask.

So an IP address of 192.168.10.0 and a subnetmask of 255.255.255.0 (or /24) means 192.168.10 is the network address and the last octet is used for the host address.

####Gateway Address

p. 537: in this book the term gateway means router (Some in the IT use the term gateway to determine the 'default gateway', that is the router wher your computer send packages to if it is on more than one network)

If a host wants to communicate with another host on the same network **it doesn't need a router**, but if the host is on another network it needs a router to get to that network

####Broadcast Address

A broadcast address is used to send traffic to all hosts on the network. This is an address that is not assignable to any hosts. In case of a class C network, the last octect for the host becomes 255. So 192.168.10.255 is a broadcast address. To see an example of how this works:

```
Toms-MacBook-Pro-2:study-material Tom$ ping 192.168.0.255
PING 192.168.0.255 (192.168.0.255): 56 data bytes
64 bytes from 192.168.0.106: icmp_seq=0 ttl=64 time=0.133 ms
64 bytes from 192.168.0.100: icmp_seq=0 ttl=64 time=3.297 ms
64 bytes from 192.168.0.102: icmp_seq=0 ttl=64 time=117.463 ms
```

####Custom network masks

You can use custom network masks for subnetting. Why know subnetting?

1. Determine whether a hosts has a bad gateway address
2. Detect how many hosts are possible on a particular network

[Subnetting is used for speeding up the network and for security purposes](http://yourbusiness.azcentral.com/importance-subnetting-20038.html)

For subnetting, part of the host address are stolen (so for a class C address the host address is the last octect) and from the highest bit in that octect on (128) are used to create a subnet and the subnet mask is altered based on how many of those bits are stolen. The new network mask deviates from the default subnet mask and could become something like 255.255.255.224 or /27 (you added 3 bits to the default subnet mask of /24 that you stole from the network part)

See p. 539 for subnetting. Study this as the last part, because it's difficult and not the only part on the exam. Just know how to solve scenario 1 (p.538) and scenario 2 (p.540)

####Additional protocols

1. IP focusses on addressing, TCP on how the packets should be send (reliable with error checking)
2. IP focusses on addressing, UDP on how the packets should be send (unreliable without error checking)
3. ICMP (Internet Control Message Protocol) allow network devices to send error messages and do queries such as the `ping` command. [ICMP doesn't use port system](https://www.google.nl/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#q=ICMP+port)

####Ports

A port is numeric value assigned to a service. 

How do services determine to which port to listen? It just to be in */etc/services*, however nowadays most services have this in their configuration file. Most defaults in the config files match the entry in */etc/services*

1. ports 0-1023 are designated well known ports (know these ports):
  1. **20 & 21**: FTP
  2. **22**: SSH
  3. **23**: Telnet
  4. **25**: SMTP
  5. **53**: DNS
  6. **80**: HTTP
  7. **110**: POP3
  8. **123**: NTP
  9. **139**: NETNIOS
  10. **143**: IMAP
  11. **161 & 162**: [SNMP](https://www.google.nl/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#q=SNMP)
  12. **389**: LDAP
  13. **443**: HTTPS
  14. **465**: SMTPS
  15. **514**: SYSLOG
  16. **636**: LDAPS
  17. **993**: IMAPS
  18. **995**: POP3S
2. ports 1024 - 49151 registered ports
3. ports 49152 - 65535: dynamic ports (free to use)

####IPv6

You must know some IPv6 commands and the 4 big differences between IPv4 and IPv6:

1. Address scheme. IPv6 uses a 128-bit number in hex notation. This allows for more numbers (biggest reason for IPv6, however due to NAT the number of effective computers connected to the internet via IPv4 is increased)
2. Routing is more efficient
3. Security builtin and not an afterthought
4. Autoconfigure for IP address assigning
5. The beginning of a packet is a header and for IPv6 this is way more robust

###Managing Interfaces

For the exam, you must be able to configure interfaces from the command line.

`lo` means loopback, a way to bound an IP(127.0.0.1) to an interface

Many of the commands we will take a look at have an equivalent form in the `ip` command

#####`ifconfig`

`ifconfig [OPTIONS]`

By default ifconfig shows you all the active interfaces (**including lo**)). What is in the output:

1. ether (Mac address)
2. inet (IPv4 address)
3. broadcast address
4. netmask
5. RX is received
6. TX is transmitted

If on the exam you this screen output, you **must** use it.

Alternative: `ip addr show`

####Red Hat Config (not in exam, study as last)

*/etc/sysconfig/network-scripts/ifcfg-eth0* is a startup script for an interface. Example:

```
DEVICE="eth0"
BOOTPROTO="dhcp"
ONBOOT="yes"
TYPE="Ethernet"
USERCTL="yes"
PEERDNS="yes"
IPV6INIT="no"
PERSISTENT_DHCLIENT="1"
```

Run `service network restart` to load the changes

####Debian Interface Configuration

*/etc/network/interfaces* holds the config file for the interfaces for Debian. Note however that some Debian-based distro's also have files in */etc/sysconfig/network-scripts/ifcfg-eth0 and per distro it differs which one should be altered.

###Viewing and Configuring Gateway Addresses

####Viewing Gateway Addresses

`route` or `netstat -r`

```
$ netstat -rn
Kernel IP routing table
Destination     Gateway         Genmask         Flags   MSS Window  irtt Iface
192.168.1.0     0.0.0.0         255.255.255.0   U         0 0          0 eth0
169.254.0.0     0.0.0.0         255.255.0.0     U         0 0          0 eth0
0.0.0.0         192.168.1.254   0.0.0.0         UG        0 0          0 eth0

This is saying that for each of the network destinations (192.168.1.0 or 169.254.0.0) that the default gateway is the 0.0.0.0 destination, if a packet is NOT destined for any address within that particular network. For the 0.0.0.0 destination, use the IP address 192.168.1.254.
```

1. `0.0.0.0` or `*` in the Destination column means it is the default
2. `0.0.0.0` or `*` in the Gateway column means there is none, (because it is in the same network, no gateway is needed to reach outside the network)

[See what 0.0.0.0 means in the output](http://unix.stackexchange.com/questions/94018/what-is-the-meaning-of-0-0-0-0-as-a-gateway) and [here](http://superuser.com/questions/872479/what-does-0-0-0-0-gateway-mean-in-routing-table)

Extra:

1. [What does link mean in routing table](http://superuser.com/questions/1067732/whats-the-meaning-of-link4-in-macs-route-table)
2. See line `0.0.0.0         192.168.1.254   0.0.0.0         UG        0 0          0 eth0`, in order to reach the gateway `192.168.1.254` the line `192.168.1.0     0.0.0.0         255.255.255.0   U         0 0          0 eth0` must be there (the static route) to know how the gateway can be reached within the local network

####Adding a default gateway

`route add default gw 10.0.0.1`

Meaning:

1. `route` -> route command
2. `add` -> add a route
3. `default` -> indicate it is a default route for if no other route matches
4. `gw` -> note this is a gateway
5. `10.0.0.1` -> the address of the gateway 

###Local Name Configuration

See p.552 for a diagram how hostname resolving works. In short:

1. check */etc/nsswitch.conf* [is Name Service Switch (NSS) configuration file, is used to determine the sources from which to obtain name services info](http://man7.org/linux/man-pages/man5/nsswitch.conf.5.html). Look in the hosts category: `hosts:      files dns nis`. This means:
  1. First look at local files
  2. Then dns
  3. The nis
2. The file you need to know for local resolving is: */etc/hosts*
3. If there is no entry in */etc/hosts*, dns will be used (see step 1). For dns, the file */etc/resolv.conf* to find dns servers and queries the first server (structure of lines in the file: `nameserver ipaddress`)
4. If that fails a NIS server will be queried (this last step seems inlikely, you don't need to know what nis server is)

**Note fo exam**: if a resolution is nmade, the host does not query further. So a usual question is troubleshooting after switching to DNS for name resolution

###Network Config Utilities

There are a lot of utilities. Study the [topics of the exam](https://www.lpi.org/our-certifications/exam-102-objectives#networking-fundamentals) to know which ones to learn.

#####`ifconfig`

`ifconfig [OPTIONS]`

By default ifconfig shows you all the active interfaces (**including lo**)). What is in the output:

1. ether (Mac address)
2. inet (IPv4 address)
3. broadcast address
4. netmask
5. RX is received
6. TX is transmitted

If on the exam you this screen output, you **must** use it.

OPTIONS:
  1. `-a` -> show all interfaces, also the not active ones

####`ifup`

Brings an interface up. Execute scripts in */etc/sysconfig/network-scripts/ifup-*

####`route`

Use `route` to defend against DDoS: `route add ATTACKERSIP lo`. No packets are send across the network because the

Alternative: `ip addr show`

####DHCP Client Tools

3 dhcp tools, one or more are used depending on the distribution:

1. `dhpcd`
2. `dhclient` -> ask a new lease via this command
3. `pump` -> ask a new lease via this command

####`host`, `getent`, `dig`

Used for name lookups. You must know all the tools

1. `getent` -> uses */etc/nsswitch.conf* to determine the search order. (so if can use */etc/hosts*)
2. `host HOST [SERVER]` -> Do a DNS lookup (so this ignores files on the system as */etc/hosts*). If `[SERVER]` is omitted, it will use the server from */etc/resolv.conf*
3. `dig` -> use this to **only do a dns query** and you can specify the server
  1. `dig [@server] name [type]` and the type can be anywhere after the `dig` command

#####`dig`

`dig hostname [OPTIONS]`

1. `[-t] MX` -> specify which servers to query. MX are mail server records. [The full list is way too big to learn them all for the exam](https://en.wikipedia.org/wiki/List_of_DNS_record_types)

Output:


1. HEADER -> info on dig environmnet
2. QUESTION -> echos back the query
3. ANSWER -> reply to query
4. AUTHORITY -> show the servers that are authorative for the targeted server
5. ADDITIONAL -> catch all section
6. STATISTICS how much time the query took

####`netstat`

Get network statistics on both incoming and outgoing socket connections

`netstat [OPTIONS]`

1. `-t` -> show TCP stats
2. `-r` -> routing table
3. `-a` -> show all sockets on functioning interfaces (this will be in the exam) (shows nice formatting)
4. `-c` -> refresh every second
5. `-p` -> show the name and PID related to each socket. [A socket is a combination of IP Address and Port Number](https://en.wikipedia.org/wiki/Network_socket#Socket_addresses)
6. `-s` -> see interface usage stats

Typical `netstat` output:

```
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 0.0.0.0:5901            0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:sunrpc          0.0.0.0:*               LISTEN 
```

Notes: 

1. [0.0.0.0 means all IP addresses on the local machine](http://serverfault.com/a/78058)
2. An asterisk on the foreign address means that the connection is not yet established
3. `netstat -anp`, `-a` is for nice formatting, `-n` is to show numerical port numbers instead of resolving the port number to an interface and `p` is to show the PID

Based on a line of output you need to be able to determine what is the local address and what is the foreign address (without the column headers off course)

####ping

Know `ping6 HOST` which is just like ping, but then voor IPv6. And from the ping manual:

```
ping uses the ICMP protocol's mandatory ECHO_REQUEST
```

####traceroute

`traceroute -n HOSTNAME` -> get the hops between you and another computer. `-n` is to show numerical IP addresses not mapped to a host name

1. If you get `*` in the response it means the router is down or configured to not return ECHO_REQUEST headers
2. `tracepath` is the same command as `traceroute`, but only root can use `traceroute` while everyone can use `tracepath`
3. `traceroute6` and `tracepath6` exist for IPv6

####tcpdump

You can do a lot with tcpdump. For the exam know `tcpdump -w FILENAME` to capture all data on a local network and write it to a file

#### 
