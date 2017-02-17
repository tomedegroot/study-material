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

###IP Address Classes (Key Topic) & private network ranges:

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

###Network Masks

A network masks sets where the network bits of the IP address ends and the host bits begins. Each class comes with a default network mask:

1. A: 255.0.0.0 or /8
2. B: 255.255.0.0 or /16
3. C: 255.255.255.0 or /24

The '/N' notation sets the number of bits that represent the network part. This form of notation is referred to as Classless Inter-Domain Routing (CIDR). It's called classless because one can determine the network and host part of an address not on the first 3 bits, but on the subnet mask.

