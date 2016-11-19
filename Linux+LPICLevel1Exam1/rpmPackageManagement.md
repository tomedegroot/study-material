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
5. Freshen `-F` -> same as upgrading, but only upgrades if a previous version is installed. This is handy if you have a bunch of rpm's and want to use those to update, but only if an older version is already installed.
5. Remove `-e`

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

##Packagename convention:

Example: nano-2.2.6-1.x86_64.rpm

Convention: name-version-buildNumber-cpuArchitecture.rpm

##Installing

`rpm -i PACKAGE_FILE` -> install, will give a warning if the package is already installed
  1. '-h' -> 
##Remove

`rpm -e PACKAGE_NAME` -> erase(=remove) a package
  1. `-h`-> Print 50 hash marks (=#)as the package archive is unpacked.  Use with `-v|--verbose` for a nicer display.
 
##Querying

`rpm -q [select-options] [query-options]` -> get the full packagename, so `rpm -q nano` returns nano-2.2.6-1.x86_64.rpm
  1. `-i` -> Display  package information, including name, version, and description.
  2. `-l` -> List files of package
  3. `-p = select-option`, example: `rpm -qlp PACKAGE_FILE` -> query and list files of package before installing
  4. `-R` -> requirements, list dependencies

##Miscelaneous##
`rpm --rebuilddb`

More advanced stuff:
*/usr/lib/rpm/rpmrc* -> rpm config file

 */usr/lib/rpm/rpm.log* -> log file of rpm
