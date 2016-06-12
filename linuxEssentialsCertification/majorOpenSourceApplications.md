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

`apt-get install packageName` -> Install a package  
`apt-get remove packageName` -> Remove a package  
`apt-get purge packageName` -> Remove package and remove any configuration files (To purge means to clean). This will also show you packages that are no longer required and which can be removed via apt-get autoremove.  
`apt-get autoremove [packageName]` -> Remove unnecessary packages  

Note: `apt-get autoremove [packageName]` is the best way to completely remove a package. If you only use apt-get remove, you can still see parts of the package are installed if you use the `which` command

##Hands-on: YUM, rpm##

###Background###

####RPM####

Red Hat introduced RPM in 1995. RPM is now the package management system used for packaging in the Linux Standard Base (LSB). The rpm command options are grouped into three subgroups for:

1. Querying and verifying packages
2. Installing, upgrading, and removing packages
3. Performing miscellaneous functions

We will focus on the first two sets of command options in this tutorial. You will find information about the miscellaneous functions in the man pages for RPM.

We should also note that rpm is the command name for the main command used with RPM, while .rpm is the extension used for RPM files. So "an rpm" or "the xxx rpm" will generally refer to an RPM file, while rpm will usually refer to the command.

####YUM####

YUM adds automatic updates and package management, including dependency management, to RPM systems. In addition to understanding the installed packages on a system, YUM is like the Debian Advanced Packaging Tool (APT) in that it works with repositories, which are collections of packages and are typically accessible over a network connection.

###Hands-on: RPM###

`rpm -ihv packageFile`

-i -> install
-h -> shows the progress
-v -> verbose

`whereis` -> locates the bin source and manual page for a command  
`rpm -q packageName` -> query the package, filename = applicationName.Version-BuildNumber.Architecture  
`rpm -qi packageName` -> -i for information  
`rpm -e packageName` -> Remove a package via RPM  

###Hands-on: YUM###

Like apt, yum gets the packages from repos and resolves dependencies.
Repo config is in */etc/yum.repos.d*

`yum update` -> upgrade off all your system software (!different from APT)  
`yum update packageName` -> upgrade a specific package  
`yum search packageName` -> search for a package  

Tip: sometimes a package is called differently in a different OS family (example: apache & httpd). Seach with `yum search` | grep '[A|apache]' to find the corresponding package for a different OS family.

`yum deplist packageName` -> list dependencies  
`yum remove packageName` -> remove a package  
`yum clean packages` -> removes any cached packages (no longer needed)  
`yum clean all` -> remove everything from the [cache](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/6/html/Deployment_Guide/sec-Working_with_Yum_Cache.html#tabl-Yum-clean_options)  
