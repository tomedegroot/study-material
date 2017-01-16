#Apt-Get Command Set

Advanced Packaging Tool

##Extra:

`/` -> search keyword in man and vi:
  1. `n` -> next match
  2. `N` -> previous match

If you cursor is on a word in vi, you can use:
  1. `*` -> net instance
  2. `#` -> previous instance


##Core:

[Ubuntu offical info](https://help.ubuntu.com/community/AptGet/Howto)

Package managers helps you manage your software by:

1. Searching repositories
2. Manage dependencies

*/etc/apt/sources.list* -> holds repository information. Sometimes third parties offer you a repository to install software via that repository. You an then add that repository. BUT only do it if you trust the third party source.

##Installing

`apt-get update` -> update the repo info in apt cache. Good practice to always do this.

`apt-get download PACKAGENAME` -> download the package(.deb) to current dir

`apt-get source PACKAGENAME` -> download the source files to the current dir

`apt-get install PACKAGENAME` -> install a package
  1. `-s` simulate an installation. This wasy you can see the packages that would be installed without installing them. With the `-s` parameter any action can be simulated, so also others than installing
  2. `-y` -> always return 'yes' to prompts
  3. `-q` -> produces output suitable for logging, omitting progress indicators. More q's will produce more **quiet** up to a maximum of 2.

##Upgrading & and fixing unmet dependencies

`apt-get upgrade` -> upgrade you packages to the newest version, but will never remove a package or install a package currently not installed. This is because:

```
Basically, versions from Ubuntu's main package sources will always stay the same save for some exceptions like Firefox.
```

This is why for example you always install php55 or php56

`apt-get dist-upgrade` -> handles changing dependencies and might remove packages or install packages currently not installed

`apt-get -f upgrade|install` -> fix unmet dependencies, even if the package which has a dependency issue is installed via dpkg

##Removing

`apt-get [OPTIONS]remove PACKAGENAME` -> remove a package
  1. `--purge` -> remove config files

`apt-get autoremove` -> autoremove is used to remove packages that were automatically installed to satisfy dependencies for other packages and are now no longer needed.

##Cleaning up the local cache

`apt-get autoclean` -> This command removes .deb files for packages that are no longer installed on your system from the cache

`apt-get clean` -> remove all /deb packages from the package cache, which is in */var/cache/apt/archives/*. Only the lock file remains.

#Apt-Cache Package Management

Allows us to create a local repo of info of all the packages available on our repo's. Updating the cache via `apt-get update` is important beforing actually upgrading (see previous section on `apt-get`).

`apt-cache pkgnames` -> get all the packagenames


`apt-cache search PACKAGENAME` -> The most relative search result is at the top. So with `apt-cache search apache2`, the apache2 package is at the top.

`apt-cache stats` -> get info on repo's.

`apt-cache depends PACKAGENAME` -> get dependencies of PACKAGENAME (In yum `yum deplist`)

`apt-cache showpkg PACKAGENAME` -> The available versions and reverse dependencies of each package listed are listed, as well as forward dependencies for each version.

`apt-cache unmet` -> see all unmet dependencies within the local repo

#DPKG Command Set

Packages for Debian-based system. First we need to get the package:

`wget --no-check-certificate https://www.dropbox.com/download?dl=packages/ubuntu/dropbox_1.6.0_amd64.deb` -> download to working dir

`dpkg [OPTIONS...] ACTION`

##getting info

For packages that are installed on your systems

1. `dpkg --get-selections` -> get installed packages
2. `dpkg -L PACKAGENAME` -> list the files of the package installed on your system.

For packages not yet installed, so use the package file:

1. `dpkg --info PACKAGEFILE` -> get info on package by packagefile.
2. `dpkg --contents PACKAGEFILE` -> see the owner, permissions and install location of the contents by packagefile. So `--contents` is suitable for a not-installed packages, and `-L` can be used for a package that is installed

##installing & reconfiguring

`dpkg -i PACKAGENAME` -> install a package, if a dependency error occurs, do:

(You can use `apt-get -f install` -> fix unmet dependencies, even if done with dpkg)

Now, you should be able to use `dpkg -i PACKAGENAME` to complete the installation of the package

`dpkg -reconfigure PACKAGENAME` -> reconfigure PACKAGENAME

##removing a package

1. `dpkg --remove PACKAGENAME` -> remove PACKAGENAME, leave config files
2. `dpkg --purge PACKAGENAME` -> remove PACKAGENAME including config files 

#Summary & Overview aptitude

High level interface for Debian based package manager. To open that, type `aptitude`

Other possible commands:

`aptitude install PACKAGENAME`
`aptitude search PACKAGENAME`
`aptitude update` -> update the cache

#dselect

Interface to apt-get package manager, similar to aptitude. Not so important, it's deprecated.
