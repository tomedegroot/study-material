#Apt-Get Command Set

(Ubuntu offical info)[https://help.ubuntu.com/community/AptGet/Howto]

Package managers helps you manage your software by:
1. Searching repositories
2. Manage dependencies

*/etc/apt/sources.list* -> holds repository information. Sometimes third parties offer you a repository to install software via that repository. You an then add that repository. BUT only do it if you trust the third party source.

`apt-get update` -> update the repo info in apt cache

`apt-cache search PACKAGENAME` -> The most relative search result is at the top. So with `apt-cache search apache2`, the apache2 package is at the top.
`apt-get clean` -> remove all /deb packages from the package cache, which is in */var/cache/apt/archives/*. Only the lock file remains.
`apt-get autoclean` -> This command removes .deb files for packages that are no longer installed on your system.

5.51
