#Files, Dirs#

##Archiving files on the command line##

 `tar` -> A Linux utility to archive things. It **just sticks multiple files together in one file.** Traditionally tar was used to creacte tape backup. Hence the name Tar. Tar stands for tape archive.
  1. `-cf` (creates file) 
    1. Example of tar of dir: `tar -cf folder1tar.tar folder1`
    2. Example of tar of files: `tar -cf folder1tar.tar file1.txt file3.txt`
  2. `-xf` (extracts file) Example: `tar -xf folder1tar.tar`
  3. `-tf` (list files) Example: `tar -tf file.tar`. Add -v for more verbose output


