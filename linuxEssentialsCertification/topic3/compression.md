#Compression#

##Archiving files on the command line##

 `tar` -> A Linux utility to archive things. It **just sticks multiple files together in one file.** Traditionally tar was used to creacte tape backup. Hence the name Tar. Tar stands for tape archive.
  1. `-cf` (creates file) 
    1. Example of tar of dir: `tar -cf folder1tar.tar folder1`
    2. Example of tar of files: `tar -cf folder1tar.tar file1.txt file3.txt`
  2. `-xf` (extracts file) Example: `tar -xf folder1tar.tar`
  3. `-tf` (list files) Example: `tar -tf file.tar`. Add -v for more verbose output
    1. `tar -xf folder1.tar folder1/file1.txt -C . --strip-components=1` 
    2. folder1/file1.txt in the above example specifies one file to extract. 
    3. `-C` -> Choose dir to extract to
    4. `--strip-components=1` -> strips components of the path name in the archive, in this case folder1

##Compression##

3 tools for compression:

1. Gzip
  1. `gzip FILE` -> compresses to FILE.gz (FILE no longer exists)
  2. `gunzip FILE.gz` -> decompresses to file
2. Bzip2 -> better compression algorithm than gzip, especially for large file types. Same format and flags as gzip
  1. `bzip2` ->
  2. `bunzip2
`
3. Zip -> universal (also Windows), **compresses and achives**
  1. `zip ZIPFILE.zip file1.txt [...file2.txt]`
  2. `unzip [list]` -> unzip the files in the list. Without `[list]` extract everything int the zip file.
    1. `-v` -> list verbosely the contents of a zip file
    2. Unzip one file: `unzip zipfile.zip file1.txt`
    3. `-r` -> recursive for dirs
  3. Not installed by default on CentOS
The `tar` command archives, it does not compress. **However with options `tar` can also compress via gzip and bzip2:**

1. gzip: `tar -zcf file.tar.gz or file.tgz`
2. bzip2: `tar -jcf file.tar.bz2 or file.tb2`

