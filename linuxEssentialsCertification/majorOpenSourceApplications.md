#Major Open Source Applications#

##Desktop Applications##

###Major GUIS###
* KDE (Suse)
* LXDE (Leightweight version of KDE)
* UNITY (Developed by Canonical for Ubuntu)
* XFCE (Consume as few resources as possible)

###Yum Package Manager###

YUM can install packages. Packages can be applications or libraries. YUM installs depencies for you. APT is another major package manager.

###GIMP###
Image manipulator

(LTS = Long Term Support, focus on stability)

###Audacity###
Audio manipulator

###Blender###
Open Source 3D Renderer

###Pidgin###
Instant Messaging Tool. Integrates with multiple providers.

##Server Applications##
Common Ports:
* `22-SSH`
* `23-TELNET`
* `25-SMTP`
* `53-DNS`
* `67-BOOTP` (For DHCP)
* `80-HTTP`
* `443-HTTPS`

Applications:
* Apache-Web Server
* MySQL  = RDMS
* MONO   = Open Source Implementation of Microsoft's .NET
* CUPS   = Printing Server
* POSTFIX= Mail Transfer Agent

##Mobile Applications##
* Apps on Android

##Development Languages##

###Software Development Models###

####Cathedral Model####
Structered in Nature. Each developer is assigned a specific part of the project/. Only the developers can see the source code during development

####Bazaar model####
Less structured. Philosophy: Developers bring more perspective which increases tthe quality of the end project.

####Development Languages####
* Java (Compiled)
* C and C++ (Compiled)
* Javascript (Interpreted)
* Python (Interpreted)
* Ruby (Interpreted)
* Pearl (Interpreted)
* PHP (Interpreted)

Compiled    = Translate symbolic code to binary. Fast, more difficult to develop.
Interpreted = Translated during runtime. Slower, easier to develop.
Assembly    = Computer low level. Very compact and efficient programs. Extremely hard to develop.

##Package Management Tools & Repositories##
Linux uses packages to install programs and library.

Package contains the following information:

1. Dependency Information
2. Version information
3. Architecture information
4. Binary packages are packages that have an executable built from source(Architecture specific)

Package tools software keeps a database of information about the installed applications uncluding the locations of the files that were placed on the Linux file system.

Two common package systems:

1. RPM (YUM for CLI, YUMEX for GUI)
2. Debian 

A distro has it's own package system. You can use it out of the box.

The package systems have online distro's to download the packages.

##Hands-on: APT, dpkg##

Location of the list of repositories:
*/etc/apt/sources.list*
Only add repositories that you trust!

###Update package list###
`apt-get update` -> Updates the local cache (package list) with information on the newest packages.  
`apt-get cache search` -> Search the cache  

###Install & Remove packages###

`apt-get install *packageName*` -> Install a package  
`apt-get remove *packageName*` -> Remove a package  
`apt-get purge *packageName*` -> Remove package and remove any configuration files (To purge means to clean). This will also show you packages that are no longer required and which can be removed via apt-get autoremove.  
`apt-get autoremove [*packageName*]` -> Remove unnecessary packages  

Note: `apt-get autoremove [*packageName*]` is the best way to completely remove a package. If you only use apt-get remove, you can still see parts of the package are installed if you use the `which` command

