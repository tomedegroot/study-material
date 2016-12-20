#todo

##gzip

Remember: (A gzip is just one big file)[https://github.com/tomedegroot/study-material/blob/master/linux%2BLPICLevel1Exam1/managingFilesInLinux.md#the-gzip-and-gunzip-command]

###Append a zip to another zip:

```
Multiple  compressed  files  can  be  concatenated.  In this case, gunzip will extract all members at once. For example:

       gzip -c file1  > foo.gz
       gzip -c file2 >> foo.gz

Then

       gunzip -c foo.gz

is equivalent to

cat file1 file2
```

###Append a file to a zip

Well, since a zip is just one compressed item, you can easily just append zip files. See the above paragraph. Only with tar

##tar

###Append a tar to another tar

Use the -A flag. So:

`tar -Avf archive.tar archiveToAppend.tar`, example:

```
[tom@t-degroot1 ~]$ tar cvf file.tar file1
file1
[tom@t-degroot1 ~]$ tar cvf file2.tar file2
file2
[tom@t-degroot1 ~]$ tar -Avf file.tar file2.tar
[tom@t-degroot1 ~]$ tar -tvf file.tar 
-rwxr-xr-- tom/tom          30 2016-12-18 17:44 file1
-rw-rw-r-- tom/tom          20 2016-12-20 09:02 file2
```

###Append a file to a tar

`tar -rvf archive.tar fileToAppend` **Mnemonic**: add file entRy

```
[tom@t-degroot1 ~]$ echo "je moeder" > file3
[tom@t-degroot1 ~]$ tar -rvf file.tar file3
file3
[tom@t-degroot1 ~]$ tar -tvf file.tar
-rwxr-xr-- tom/tom          30 2016-12-18 17:44 file1
-rw-rw-r-- tom/tom          20 2016-12-20 09:02 file2
-rw-rw-r-- tom/tom          10 2016-12-20 09:14 file3
```
