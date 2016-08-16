#Files and Dirs#

1.`touch` -> create empty text file or update timestamp. Updating timestamps also works with dirs.
  1. `-d` -> give a specific timestamp, e.g. `touch -d "February 1 2015" testfile1`
2. `cp [source] [destination]` -> copy.
  1. `cp file.txt file1.txt`
  2. `cp file.txt testdir/` -> copies to testdir/file.txt
  3. `cp file.txt testdir/filetext.1`

  4. `-f` -> force, override existing destination file
  5. `-i` -> prompt before override
  6. `-p` -> preserve ownership. By default the owner of the new file is the user copying the file.
  7. `-r` -> recursive
  8. `-a` -> archive -> recursive and preserve ownership and copy the symbolic links
  9. `-u` -> update -> only copy if the original file is newer than the new file
3. `mv [source] [destination]` -> move
4. `rm [filename]...`
  1. `-r, -R, --recursive` -> remove dir and contents recursively
  2. `-f, --force` -> ignore nonexistent files and arguments
5. `mkdir [dirname]` -> create a dir
  1. `-m, --mode=MODE` -> set mode as in chmod
  2. `-p, or --parents` -> create the parent dir if it doesn't exist yet.
6. `rmdir` -> remove a dir, but you can use `rm -rf` as well  

