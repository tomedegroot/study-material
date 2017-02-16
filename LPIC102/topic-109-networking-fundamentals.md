#Topic 109: Networking Fundamentals

##109.1: Fundamentals of Internet Protocols

###Introduction

Hosts are the smallest unit on a network: one single entity that can respond to a ping.

Subnets are logical groupings of hosts on a network based on their addressing.

Segments are physical groupings of hosts on a network based on how they are connected via hubs, switches and wires.

Great analogy:

1. A host is a house on a street.
2. A network is the street.
3. A gateway is where two streets intersect. (a gateway is a router)

###Necessary config to operate in a network:

1. An IP Address
2. A Network Mask
3. A Gateway Address

###Networks and host relationship in the IP address

An IP addres (of 198.168.1.200) is broken up into two parts:

1. The network address (192.168.1) (analogy: the street address)
2. The host address (200) (analogy: the house address)

What determines the network part of the IP address is determined by subnetting
