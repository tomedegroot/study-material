#Simple Commands & Shortcuts For The Linux Shell

##pwd

Print the local working directory

##time

How to measure execution of a command? -> `time COMMAND`

##shortcuts tom $HOME

1. `cd`
2. `cd ~`
3. `cd $HOME`

##exit shell after executing a program

How to exit shell after executing a program? -> `exec PROGRAM`

The exec command replaces the shell process, thus when the program terminates it terminates the shell.

##history

Stored in ~/.bash_history

Cycle through commands: `UP ARROW`

Search the history: `CRTL+R`
Next entry: `CRTL+R`

Cancel search and return original entry: `CRTL+G`

##shortcuts

End of line: `CRTL+E`
Beginning of line: `CRTL+A`

Remove till beginning of line: `CRTL+U` or `CRLT+X` and then `BACKSPACE`
Remove till end of line: `CRTL+K`
Remove word: `CRTL+W`
Remove char: `CRTL+D`

Paste removed material: `CRTL+Y`; **different from VIM**

Transpose a char: `CRTL+T`

##Bash configuration

To make an environment variable persistent (so use it again after the current session) alter either the

1. *~/bash_profile* file -> persistent for one use.
2. */etc/profile* or */etc/profile.d* -> persistent for all users.

```
Bash as login shell will load /etc/profile, ~/.bash_profile, ~/.bash_login, ~/.profile in the order

Bash as non-login interactive shell will load ~/.bashrc
```

#Environment Variables, Redirection Operators & Data Pipes

##export

How to make a variable available to all sub-processes? -> `export key=value`

This way all child processes can access the variable

2.29
