#Software Libraries

Libraries provide code that can be used in between software packages. But since they are shared, issues with:

1. Locating the correct library
2. Getting the right version of the library

Might occur. We will learn how to fix those.

##Configuration

Main configuration file for libraries is */etc/ld.so.conf*. This way is just an include for the dir with config files in it:

```
include ld.so.conf.d/*.conf
```

If you update this file, you have to run a command to update the cache: `ldconfig`

Extra: it is called ld.so* because it Links Dynamically Shared Objects

**Mind you, the core libraries are always available:** 
1. The */lib/* dir is always included, it doesn't need to be configured
2. The */usr/lib/* dir is always included, it doesn't need to be configured

9.50
