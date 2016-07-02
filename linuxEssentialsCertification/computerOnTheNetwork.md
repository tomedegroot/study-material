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

###OSI model###

The OSI model has 7 layers:
1. Physical -> Transmits electrical signals. This is the network card.    
2. Data link -> Defines the rules and procedures for accessing the physical layer (1). Defines how hosts are identified and how hosts are accessed. Specifies how to verify the data received from the physical layer. Organises information from the upper layers into datagrams
3. Network -> Enables routing of data. How to determine next network point for a packet. The IP-protocal operates here.
4. Transport -> Receives data from the upper layer and divides these into small transmittable chuncks (packets). This happens vica versa on the receiving hosts. TCP nd UDP operate on this layer.
5. Session -> Establisihing and maintaing connections
6. Presentation -> Responsible for ensuring the information is formatted correctly for the application
7. Application -> The application using the network

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
