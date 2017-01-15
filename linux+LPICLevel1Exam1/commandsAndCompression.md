#screen

Have multiple screens open within one session and share a screen between sessions

`screen [OPTIONS]`

Without options, **screen will do nothing if you have an attached window or open a new window.**

OPTIONS:
1. How to see all your open windows? -> `-list`; from the man: `prints a list of pid.tty.host strings identifying your screen sessions.`
2. How to detach the current window? -> `-d`
3. How to reattach a different window? -> `-r WINDOWNUMBER`
4. How to start a new session and give it a meaningful sessionname? -> `-S SESSIONNAME`

How to exit a window? -> `exit`; it will exit the screen and brings you to the most recently atttached window.

How to execute a command and terminate the screen once it's done executing? -> `screen COMMAND`

##How to share a screen? (Only share windows between the same user)

1. Create a screen session: `screen -S SESSIONNAME`
2. Attach to a screen that is attached somewhere else? -> `screen -x SESSIONNAME`

or

3. Attach to a screen that is detached? -> `screen -r 'USERNAME/WINDOWNUMBER'`

#xz compression

xz and gzip are the most used compression utilities. 

Why `xz`?
1. xz has a better compression ratio that gzip.
2. xz requires more memory to compress

`xz [OPTIONS] [FILE]`

OPTIONS:

1. How to zip a file? -> `-z`
2. How to decompress a file? -> `-d` or use the `unxz` command (if you don't write the result to STDOUT, the filename must have know suffix, such as '.xz', otherwise you will get an error)
3. How to list information of a zipped file? -> `-l`
4. How to write to STDOUT? -> '-c', same as unzip (Mind you, compressed data cannot be written to a terminal (results in error), but it can be redirected to a file). Example: `echo "haaaaaaaai" | xz -z > test`

```
`echo "haaaaaaa    ai" | xz -z > test`
[tom@t-degroot1 ~]$ xz -dc test
haaaaaaaai
```

```
[tom@t-degroot1 ~]$ echo "Haaaaai" | xz -zc > buffer && xz -dc < buffer
Haaaaai
```

You can never compress a dir or multiple files. You first need to create an archive via tar. You can filter tar through `xz` via the `-J` option. Same as the `-z` option, but then for `xz`

#pkill and pgrep

look up or signal processes based on name and other attributes

`pgrep|pkill [OPTIONS] pattern`

OPTIONS:
1. Sending a signal:
   1. `-SIGNAL` -> send signal (15=SIGTERM, 9=SIGKILL). 15 is default. (pkill only)
2. Getting info:
  1. `-l` -> list the process name (pgrep only)
  2. `-a` -> list the command that was issued. 
3. These options are all filters:
  1. `-u USERNAME|USERID` -> filter based on USERNAME
  2. `-v` -> invert matching (pgrep only)
  3. `-n` -> get the most recent process

Examples:
     
1. You don't have to use a filter and 15 is the default signal, so with `pkill httpd` all processes with the name httpd will be killed with a SIGTERM
2. `pgrep -u tom -n` -> get user tom's newest process

#dmesg

Used for troubleshooting the Linux kernel

A buffer is portion of the memory for temporary storing info (from for example a harddrive or a keyboard). A ring buffer is a constant size buffer, so it's LIFO storage. `dmesg` helps you to interact with the kernel ring buffer.

`dmesg [OPTIONS]`

OPTIONS:
1. `-C` -> Clear the kernel ring buffer
