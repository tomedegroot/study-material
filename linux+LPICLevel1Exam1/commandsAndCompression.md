#screen

Have multiple screens open within one session and share a screen between sessions

`screen [OPTIONS]`

Without options, **screen will do nothing if you have an attached window or open a new window.**

OPTIONS:
1. How to see all your open windows? -> `-list`; from the man: `prints a list of pid.tty.host strings identifying your screen sessions.`
2. How to detach the current window? -> `-d`
3. How to reattach a different window? -> `-r WINDOWNUMBER`

How to exit a window? -> `exit`; it will exit the screen and brings you to the most recently atttached window.

How to execute a command and close the screen once it's done executing? -> `screen COMMAND`

6.55
