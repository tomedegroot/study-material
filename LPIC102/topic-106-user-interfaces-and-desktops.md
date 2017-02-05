#Topic 106 

**Read the pdf notes for this rather confusing and messy part**

##X Window System, X Window Manager, X Display Manager Desktops

![Overview of the relations between X Window System, X Window Manager and Desktop relate](https://en.wikipedia.org/wiki/X_window_manager#/media/File:Schema_of_the_layers_of_the_graphical_user_interface.svg)

###Overview of how it works

####X Window System

X is a server-client Window System that provides the basis for a GUI. Responsibilities of X:

1. Draw bitmaps etc.
2. Interface with hardware, such as mouse, video card and monitor
3. Provide a protocol via which the client and server can communicate. The client says what it wants to have drawn and the server draws it.

####X Window managers

Runs on top of the X Window System. The role of the window manager is that when X server draws a window on the screen, the windo manager puts the scrolls bars, minimize buttons, maximize buttons etc there.

####X Display Managers

Manage Login and Sessions on an X Server. So the client needs to have this to connect to an X Server [source](https://en.wikipedia.org/wiki/X_display_manager_(program_type))

Name, Location, Config files

1. XDM, */usr/bin/xdm/*, */etc/X11/xdm/*
2. KDM, */usr/bin/kdm/*, */etc/kde/kdm/*
3. GDM, */usr/sbin/gdm/*, */etc/gdm/*

###Linux Desktop

A desktop environment is built on top of the X Window System to provide the desktop metaphor. GNOME and KDE are well known Linux desktop environments

###Into and Out of X

The tty's are mapped to F1-F7 where tty7 represents the GUI

If in text mode:

1. `ALT+F1-F6` -> switches text terminals
2. `ALT+F7` -> back to X if running

While in an X sessions:

1. `CRTL+ALT+F1-F6` -> switch to to text terminals
2. `ALT+F7 or CRTL+ALT+F7` -> switches back to X 

So in short, if you are in X you need to add `CRTL` to switch between 

####Configuring

###X Server Config

1. */etc/X11/xorg.conf*, however This is old, [nowadays X will load the files in */usr/lib/X11/xorg.conf.d/*](https://wiki.ubuntu.com/X/Config). Use `X -configure` to make a config files:

Sections in a X config files: (see p. 403)

1. Files -> files used by X server, such as fonts
2. Module -> associates devices with module files
3. InputDevice -> input devices such as keyboard an mouse
4. Monitor -> describe the monitor
5. Screen -> Describe feature of the screen including the color depth

###Fonts

1. */etc/X11/fonts/* for fonts

You can uset a system font server for fonts called `xfs`. The benefit of this server is that it can multithread and thus render complex images quicker. To use this, place

```
FontPath "unix/:7100" [or "unix:/:-1"]
```

In X server config (such as */usr/lib/X11/xorg.conf.d/*)

###xhost

`xhost` -> used to add and delete host names/IPs to the list allowed to make connections to the X window system.

3 modes:
1. `xhost` -> show current state
2. `xhost - ` -> Enables security: only those authorized can connect
3. `xhost + ` -> Disables security: anoyone can connecti

`xhost +HOSTNAME` -> allow connections from HOSTNAME

###Common commands and environment variables

`startx` -> Starts the X Window System. Calls and uses X, `xinit` and `xauth` to set up the environment with desktop.

`xinit` -> Initializes the X window system and often starts the first X client application.

`xvidtune` -> Fix problems when output is being cut off screen.

`xwininfo` -> Click a window and then query it for information on a specific window.

`xdpyinfo` -> Display information on the underlying X Window System.

`$DISPLAY` -> determines the display and screen that X applications are to display on/

###X11 forwarding via SSH

`ssh -X user@host` -> Execute a graphical application on the remote machine and show the output on the local machine.

`ssh -Y user@host` -> does the same, but without X11 Security Extension Protocols and is this less secure

##Accessability 

###Key Options which can be enabled:

1. Sticky Keys: Instead of typing `CRTL + C`, you first type `CRTL` and then `C`
2. Repeat Keys: Press a key once and a value such as a char will outputted as long as the key is pressed
3. Slow Keys: Only type when a key is shortly touched (for people with heavy hands)
4. Bounce Keys: DO not register a second touch of the same key. (for people with shaky hands)
5. Toggle Keys: Give a sound when a modifer key such as the `SHIFT` key is pressed
6. Mouse keys: Move the mouse when typing numbers on the num pad

###Desktop Themes

1. A contrast desktop theme allows for easier viewing
2. Large print theme prints fonts larger than normal

###Screen Reader

Verbalises the text on a screen (helpful for blind/analfabetic people)

1. Orca
2. Emacspeak
3. espeak
4. festival

###Braille Display

Is monitor that provides Braille output

###Screen Magnifier

###Onscreen Keyboard

Example: GNONE's GOK
