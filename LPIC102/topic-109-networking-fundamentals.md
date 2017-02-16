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

On classes:

The first three bits of the first octet determine what class the IP address is in.

The class the IP address is in determin which part of the address is the network part and which part of the address is the host address

Why create the address classes? -> Because some networks have different sizes (e.g. need to place more hosts than other networks):

```
IP Address classes were the original organizational structure for IP addresses. The specific address class would determine the maximum potential size for a computer network. The address class would define which of the specific bits of the address would be used to identify the network and network identification, the bits to identify the host computer and host ID, and total number of host subnets permitted per network. Five total classes of IP addresses were defined, class A through E. Although the IP class term will commonly be used to describe the difference between one network and another, the practical use of addressing is not commonly used any more. It has been replaced with classless addressing where a netmask can be assigned to any IP address range.
```

More info on classes:

1. https://docs.oracle.com/cd/E19455-01/806-0916/6ja85399v/index.html
2. https://technet.microsoft.com/en-us/library/cc940018.aspx
