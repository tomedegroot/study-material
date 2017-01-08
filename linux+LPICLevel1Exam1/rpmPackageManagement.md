#RPM Package Management

Used for RedHat based system

**For study: read the course notes, not all the rpm commands and flags for the exam are in the video**

##RPM command structure

If a package is already installed with the same name, you can't install a package with the same name. Packagenames must be unique for Nano.

Check the man of rpm. The first option is the kind of action:

1. Query `-q`
2. Verify `-V`
3. Install `-i`
4. Upgrade `-U`
5. Freshen `-F` -> same as upgrading, but only upgrades if a previous version is installed. This is handy if you have a bunch of rpm's and want to use those to update, but only if an older version is already installed (so in a script, piping or redirecting)
5. Erase a package `-e`

And the second option is an option specific for that action or one of the general options, suc as `v` for verbose. See:

```
QUERYING AND VERIFYING PACKAGES:
       rpm {-q|--query} [select-options] [query-options]

       rpm {-V|--verify} [select-options] [verify-options]

   INSTALLING, UPGRADING, AND REMOVING PACKAGES:
       rpm {-i|--install} [install-options] PACKAGE_FILE ...

       rpm {-U|--upgrade} [install-options] PACKAGE_FILE ...

       rpm {-F|--freshen} [install-options] PACKAGE_FILE ...

       rpm {-e|--erase} [--allmatches] [--nodeps] [--noscripts]
           [--notriggers] [--test] PACKAGE_NAME ...
```

So `rpm -q -i PACKAGE_NAME` will query and get info, but `rpm -i PACKAGE_FILE` will install 

`select-options` means the way to select a file. By default this is the PACKAGE_NAME (for example nano), but with `-p`  you can specify the PACKAGE_FILE. This makes it possible to query a package before installing it
  1. `-p` -> specify package file
  2. `-v` -> verbose information

##Packagename convention:

Example: nano-2.2.6-1.x86_64.rpm

Convention: name-version-buildNumber-cpuArchitecture.rpm

##Querying

`rpm -q [select-options] [query-options]` -> get the full packagename, so `rpm -q nano` returns nano-2.2.6-1.x86_64.rpm
  1. `-i` -> Display  package information, including name, version, and description.
  2. `-l` -> List files of package
  3. `-p = select-option`, example: `rpm -qlp PACKAGE_FILE` -> query and list files of package before installing (select option to use package file instead of package name)
  4. `-R` -> requirements, list dependencies
  5. `-a` -> query all installed packages
  6. `-v` = select-option  -> see if a pacakge is installed

##Installing

`rpm -i PACKAGE_FILE` -> install, will give a warning if the package is already installed
  1. '-h' -> print hash marks as package is installed

If you miss dependencies, you will get a message. First fixt the missing dependency via:

`yum install -y [dependency name]`

##Remove

`rpm -e PACKAGE_NAME` -> erase(=remove) a package
  1. `-h`-> Print 50 hash marks (=#)as the package archive is unpacked.  Use with `-v|--verbose` for a nicer display.
 
##Rebuilddb##
`rpm --rebuilddb` -> This command rebuilds the RPM database from the installed packages, the file named Packages in the /var/lib/rpm directory.

More advanced stuff:
*/usr/lib/rpm/rpmrc* -> rpm config file
*/usr/lib/rpm/rpm.log* -> log file of rpm

#YUM

Yellowdog Updater Modified -> package manager.

Different from apt-get since:
1. Config is different
2. It's rpm based

##YUM config files

*/etc/yum/**
*/etc/yum.conf* -> add repos
*/etc/yum.repos.d* -> add repos

##Operating YUM

###Searching and info

`yum search PACKAGENAME`

1. `yum list [OPTIONS] [PACAKGENAME]` -> list and status of package
2. `yum list all [PACKAGENAME]` -> list all available and installed packages
3. `yum list installed [PACKAGENAME]` -> list installed packages
4. `yum list available [PACKAGENAME]` -> list available packages

`yum info PACKAGENAME` -> get info on a package (name, version, install date)

`yum deplist PACKAGENAME` -> get dependencies of packages

YUM itself can **not** list the contents of a package. If you want to list the contents of a package, use `rpm -ql PACKAGENAME`, however:

- This only works if a package is installed.
- Or if you specify a package file via the -p option.

You can use (rpm2cpio to list the contents of a package)[##rpm2cpio]

###Installing

`yum install PACKAGENAME` -> install
  1. `--force` -> force installation. Use it when a dependency isn't available, but you still want to install it. **not recommended**

###Updating

`yum check-update` -> check if packages need to be updated`

`yum update` -> If  run  without  any packages, update will update every currently installed package.  If one or more packages or package globs are specified,  yum will update only those packages. Will not delete obsolete packages by default.
  1. `--obsoletes` -> delete obsolete packages. Same as `yum upgrade`. So in short: `yum update` will **not** delete obsolete packages, `yum upgrade` will. Thus a yum upgradewill update the entire system @todo difference between update and upgrade
###Removing

`yum remove PACKAGENAME`

`yum autoremove PACKAGENAME` -> works like `-clean_requirements_on_remove remove`; it removes all the config files as well

###Cleaning

`yum clean all` -> clean the yum cache (*/etc/cache/yum*)

#yumdownloader & rpm2cpio

##yumdownloader

With YUM we download and install te package. What if we just want to have the package? This way we can:

- See the files in a package
- Redistribute packages in our own network

`yumdownloader [OPTIONS] PACKAGENAME`
  1. `--resolve` -> download the .rpm **and the dependencies** @todo: get this to work


##rpm2cpio

cpio is a (file archiver utility used by rpm)[https://en.wikipedia.org/wiki/Cpio]

rpm uses cpio and it is possible to extract the cpio from an rpm. With that you can use cpio to see the contents of an rpm

`rpm2cpio PACKAGEFILE` -> extract the cpio from the .rpm

cpio always reads from stdin by default, thus:

`cpio [OPTIONS] < .cpio`
  1. `-t` -> list the contents of the cpio
  2. `--files .cpio` -> don't read from stdin, but read contents of the file

So in one go for example:

`rpm2cpio httpd-2.4.6-40.el7.centos.4.x86_64.rpm  | cpio -t`

