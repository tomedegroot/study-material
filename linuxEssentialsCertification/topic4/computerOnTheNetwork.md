#Your Computer on the Network#

##Internet, Network, Routers##

A Linux computer can fullfil lots of different roles in a network, such as:

1. Domain Controller
2. Database Server
3. DHCP Server
4. Web Server
5. E-Mail Server
6. File and Print Server
7. Packter-filtering, stateful or even application-level firewalls
8. Proxy Server
9. Content Filter Server
10. Router

Goals of this section:

1. Understand basic networking concepts
2. Understand requirements for integrating Linux computers into a LAN
3. How to troubleshoot networking issues

Networking Basics:

1. Network use protocols to talk to one another (think of a protocol as a language).
2. Computer Systems need to speak the same language to send and receive data.
3. IP Protocol
  1. Used on the internet
  2. Works with other protocols such as Transmission Control Protocol (TCP)
  3. Works with User Datagram Protocol (UDP)
4. OSI Reference model -> breaks down the complete communication process into specific tasks (modularity). This way you can buy from different vendors per layer, instead having to buy the complete proprietary technology.

###OSI (Open Systems Interconnection) model###

The OSI model has 7 layers:  
1. Physical -> Transmits electrical signals. This is the network card.  
2. Data link -> Defines the rules and procedures for accessing the physical layer: (1) Defines how hosts are identified and how hosts are accessed, (2) Specifies how to verify the data received from the physical layer, (3) Organises information from the upper layers into datagrams.  
3. Network -> Enables routing of data. How to determine next network point for a packet. The IP-protocal operates here.  
4. Transport -> Receives data from the upper layer and divides these into small transmittable chuncks (packets). This happens vica versa on the receiving hosts. TCP and UDP operate on this layer.  
5. Session -> Establisihing and maintaing connections.  
6. Presentation -> Responsible for ensuring the information is formatted correctly for the application.  
7. Application -> The application using the network.  

Information flows from PC1' application to the physical layer to PC2'2 physical layer and then the application layer.

###IP, TCP, UDP basics###

The IP Protocol makes sure that a packet reaches it destination. The TCP and UDP fragment the data for sending an reassemble the data at the receiving host.

The internet uses the IP protocol. The IP protocol is designed to make sure the data arrives reliable at the receiver. The IP protocol relies on receiving transmittable chunks (or packets). The packets are received as seperate data units. IP protocol is only concerned with reliably delivering these units.

TCP/IP is used so much that is referred to as the TPC/IP suite. This is technically incorrect since UDP is also used within this suite. TCP ensures data is exchanged reliable directly between two network hosts. It does this by requiring achknowledgement from the receiver that the package is received. If a packet is lost, TCP sends package again. Because of this reliability, the following applications use TCP/IP:

1. Web Servers
2. E-mail Servers
3. FTP Servers

The fidelity of the data comes with a cost: latency. TCP requires quit some network processing overhead.

UDP is a connectionless protocol where the packets are sent unacknowledged. Used by applications that can tolerate less reliability, such as Streaming Audio, VoIP, Gaming.

Next to TCP and UDP there is also ICMP. Used for testing and verifying network communication between hosts. (part of the IP protocol)

###Ports###

1. TCP and UDP both provide ports for upper layer protocols. A port is a logical connection between TCP and UDP for upper layer protocals. 

2. Ports allow a single host with a single IP address to provide multiple network services. Therefor each of those services uses the same IP, but a different port number.

3. Port numbers range from 0 to 65536 (= 256x256 = 2 bytes) for each indivual IP address.

4. Well known ports are within the 0-1023 range. Some examples:
  1. 20 and 21: FTP
  2. 22 SSH
  3. 23 Telnet
  4. 25 SMTP
  5. 80 HTTP
  6. 110 POP3
  7. 137, 138, 139 NetBios
  8. 443 HTTPS

5. Registered ports range from 1024-49151 -> Organizations can program their own network service and can then apply for a port within this list

6. Dynamic ports (or private ports) range from 49152-65535 -> available for use by any network service. A dynamic port may be used for one client.

###More specific info on IP addresses###

1. Every hosts in an IP-based network must have a unique IP address assigned to it.
2. IP addresses can change at any time. The media access control (MAC) address never changes and is burned into the network board.
3. IP address consists of four numbers between 0 and 255 and is separated by periods:

  1. 10.10.0.1
  2. 127.0.0.1

4. Each number in the address is an eight-bit binary numer, called an octet. (takes exactly one byte to store)
5. Each octet of a binary number can be represented by 0's and 1's. For example the address 192.168.1.1 in binary:

11000000.10101000.00000001.00000001

Converting a decimal number to a binary number could be part of the exam. Best thing to do: write the bits 1 - 8 on a scratch paper with the corresponding decimal number:

1. -> 128
2. -> 64
3. -> 32
4. -> 16
5. -> 8
6. -> 4
7. -> 2
8. -> 1

Some IP addresses are reserved:

1. The last octet in an IP address cannot be a 0. This is reserved as the address of the network segment itself.
2. The last octet in an IP address cannot be 255. This number is meant as the broadcoast address.

On the internet, which is a network, every IP address must be unique. IPv4 only has 255^4 unique addresses. Therefor IPv6 is created:

1. IPv4: 32 bit IP scheme
2. IPv6 128 bit IP scheme. IPv6 is composed of four character hexadecimal number separated by colins. For example:

FE80:0000:0000:0000:0202:B3FF:FE1E:8329

Must Linux distro's support both IPv4 and IPv6.

###Network Address Translation (NAT)###

We use a NAT router that creates 'private' IP address space on our LAN with multiple devices and computers but the outside, 'the router' has only 1 public IP address in which the internal network gets translated through:

		   Public Internet
		         |
		   Public Network
(NAT Router) Public IP 72.23.130.135 & Private IP 192.168.0.1
			 |
			LAN
       |				|
PC1 192.168.0.10		PC2 192.168.0.15

This enables you to be on a private network and still use a public network such as the internet. Private IP address ranges are necessary to facilitate this:

1. 10.0.0.0 - 10.255.255.255 (Class A)
2. 172.16.0.0 - 172.31.255.255 (Class B)
3. 192.168.0.0 - 192.168.255.255 (Class C) 

These are non-routable addresses. They are translated via NAT through a public IP address.

Subnet Mask

IP addresses are divided into two parts:
1. Network Address
2. Node Address

Every system within a network must have the same number in the network portion of the address. However, they have to have a unique node portion. How much of the IP address belongs to the network portion and how much belongs to the network and the node portion is determined by the subnet mask.

Example: 255.255.255.0

Every 255 in a subnet mask octet identifies a portion of a IP address that is used for the network portion.

Address classes:

1. Class A:
  1. First octet between 1 and 126
  2. First octet is the network address
  3. Last three octets is the node address
  4. Default subnet mask class A 255.0.0.0
  5. Class A allows 126 total possible networks
  6. Class A can offer 16.7 million possible node addresses.

2. Class B:
  1. First octet between 128 and 192
  2. First two octets are the network address
  3. Last two octets are the node address
  4. Default subnet mask class B 255.255.0.0
  5. Class B allows 16,384 total possible networks
  6. Class B can offer 65,534 possible node addresses.

3. Class C:
  1. First octet between 192 and 223 
  2. First three octets are the network address
  3. Last octet is the node address
  4. Default subnet mask class B 255.255.255.0
  5. Class C allows 2,097,152 total possible networks
  6. Class C can offer 254 possible node addresses.

So these classes and aspects help you to determine how you could setup a private network.

Subnetmask can be notated using shorthand:

192.168.1.1/24 indicates that 24 bits are used for the subnet mask
192.168.1.1 255.255.255.0

Partial Subnet:
1. You do not have to use the default subnet. Example: A class A address could use only part of the octet fot the address such as 255.255.252.0. This means that the first 6 bits in the 3rd octet are used for the network portion of the address.
2. However, for PC3 to speak with PC2 and PC1 we need a router, because it is a different subnet. Without this route, PC3 (using subnet mask 255.255.252.0) can not communicate to the other host using 255.255.255

##Domain Name Service (DNS) & Default Gateway (aka Network Router)##

Domain names have to be translated to an IP Address. DNS Servers do this.

The IP protocol was designed with routers in mind. In order to have different subnets communicate with one another, a router is necessary. When an ip address is not available in the own network (subnet), the IP protocol will redirect the the packet through the default gateway. This is usually the router. The router will use routing protocols to further redirect the packet.

`dig` -> find an IP address for a domain name. Could also use `nslookup`

See picture 1 to see how routing happens between subnets.

There are two networks:
1. 192.168.1.0
2. 10.10.30.0

The router has two network interface cards for the two networks. Mostly routers use 1 or 254 for the node segment of the addres, so in this example:

1. 192.168.1.254
2. 10.10.30.254

By looking at the subnet mask, the router can determine that the packet needs to go to the 10.10.30.0 network.

Therefor, the router can connect you to the internet **and** to other local network segments via subnetting.

##Network Configuration##

A few important network tools:

1. `ping` -> Testing of connectivity of a remote network device
2. `dig` -> Allows us to loopup IP address for DNS names (also: `nslookup`)
3. `netstat` -> List network connections, routing info, NIC info
4. `route` -> Current route/net settings
5. `traceroute` -> Traces the route a packet takes
6. `ifconfig` -> Current network settings
7. `ip addr` -> Current IP address and network settings

*/etc/resolv.cong/* -> This is where DNS Server info is stored

`route` -> default location the pc is going to use to reach the outside network

Each network interface has its own startup script and config, for example:
*/etc/sysconfig/network-scripts/ifcfg-eth0/*

NOTE: network configs of the server lab machines, chances are it is no longer reachable. This is because of the network setup of the server lab.

Example of */etc/sysconfig/network-scripts/ifcfg-eth0/*

```
TYPE=Ethernet
BOOTPROTO=dhcp
DEFROUTE=yes
IPV4_FAILURE_FATAL=no
IPV6INIT=yes
IPV6_AUTOCONF=yes
IPV6_DEFROUTE=yes
IPV6_FAILURE_FATAL=no
NAME=eth0
UUID=1e0c18a8-ae6f-4672-a141-baa83d251558
DEVICE=eth0
ONBOOT=yes
PEERDNS=yes
PEERROUTES=yes
IPV6_PEERDNS=yes
IPV6_PEERROUTES=yes
```

Example of how to get a static IP address:

BOOTPROTO=static
IPADDR=10.0.2.41
NETMASK=255.255.255.0 (or: IPADDR=10.0.2.41/24 -> shorthand notation of the netmask)
NETWORK=10.0.2.0 ->to specify the network segment

1. `route` -> [info](http://www.thegeekstuff.com/2012/04/route-examples/)
  1. `route add -net network_address netmask subnet_mask gw router_address` -> add a route
  2. `route delete -net network_address netmask subnet_mask gw router_address`->delete a route

2. `netstat` 
  1. `-a` All listening and non-listening sockets
  2. `-i` Stats of network interfaces
  3. `-l` Listening sockets
  4. `-s` Summary
  5. `-r` Routing table -> same as `route`

3. `traceroute` -> uses icmp echo response packet to see how a route is. Helps you to see at which router the route stops.
