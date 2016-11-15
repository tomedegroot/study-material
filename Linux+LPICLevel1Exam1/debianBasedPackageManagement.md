#Apt-Get Command Set

##Extra:

`/` -> search keyword in man and vi:
  1. `n` -> next match
  2. `N` -> previous match

If you cursor is on a word in vi, you can use:
  1. `*` -> net instance
  2. `#` -> previous instance


##Core:

(Ubuntu offical info)[https://help.ubuntu.com/community/AptGet/Howto]

Package managers helps you manage your software by:
1. Searching repositories
2. Manage dependencies

*/etc/apt/sources.list* -> holds repository information. Sometimes third parties offer you a repository to install software via that repository. You an then add that repository. BUT only do it if you trust the third party source.

`apt-get update` -> update the repo info in apt cache

`apt-cache search PACKAGENAME` -> The most relative search result is at the top. So with `apt-cache search apache2`, the apache2 package is at the top.
`apt-get clean` -> remove all /deb packages from the package cache, which is in */var/cache/apt/archives/*. Only the lock file remains.
`apt-get autoclean` -> This command removes .deb files for packages that are no longer installed on your system.

`apt-get install PACKAGENAME` -> install a package
  1. `-s` simulate an installation. This wasy you can see the packages that would be installed without installing them. With the `-s` parameter any action can be simulated, so also others than installing
  2. `-y` -> always return 'yes' to prompts
  3. `-q` -> omit progress information, keeps the screen clean

`apt-get source SOURCENAME` -> download the source files to the current dir

`apt-get upgrade` -> upgrade you packages to the newest version, but will never remove a package or install a package currently not installed  Extra info on major versions:

```
Basically, versions from Ubuntu's main package sources will always stay the same save for some exceptions like Firefox.
```

This is why you always install php55 or php56

`apt-get dist-upgrade` -> handles changing dependencies and might remove packages or install packages currently not installed

#Apt-Cache Package Management

Allows us to create a local repo of info of all the packages available on our repo's. Updating the cache via `apt-get update` is important beforing actually upgrading.

`apt-cache stats` -> get info on repo's.
`apt-cache depends PACKAGENAME` -> get dependencies of PACKAGENAME
`apt-cache pkgnames` -> get all the packagenames
`apt-cache unmet` -> see all unmet dependencies within the local repo
`apt-cache search PACKAGENAME` -> search for PACKAGENAME
