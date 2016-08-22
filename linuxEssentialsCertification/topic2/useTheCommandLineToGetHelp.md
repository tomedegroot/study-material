#Use the Command Line to get help#

##`man`##

The Linux MAN are manuals for commands, config files etc. Man is in a reference format, it is **not** a tutorial.

###man sections###

The manual sections:

1. Executable programs and shell commands
2. System calls provided by the jernel
3. Library calls provided by program libraries
4. Device file (usually stored in /dev)
5. File formats
6. Games
7. Miscellaneous (macro packages, conventions etc.)
8. System administration commands (for programs run mostly or exclusively as root)
9. Kernel routines

`man man` -> get these sections

###man usage###

Use man by via `man [keyword]` where `keyword` is a command, config file or other keyword we wanat help with. This takes you directly to the correct section.  
Example: `man passwd` for info on the passwd **application** (You can see that this information on the application by the first line in the man page which is 'PASSWD(1)' where 1 is the section number.)

To get to a specific section, type `man [section] keyword`.   
Example: `man 5 passwd` for information on the password file (*/etc/passwd*)

###`whatis` & `apropos`###
What if you don't know where to look in man?

`whatis keyword` -> Search for summary information in man pages. It returns the NAME section of the MAN page
`apropos keyword` -> Returns **everything** in the man pages with the keyword in it. (is the same as `man -k keyword`)

###man page organisation###

MAN is organised like:
1. Name
2. Sypnosis (provides brief description on how to use the command with [optional params] and ... for repeatable set params). Multiple lines indicate some options are dependant on other options.
3. Description (what does the command do)
4. Options (explain what all the flags will do)
5. Files (list files that are associated with the subject such as config files)
6. See Also (related material)
7. Bugs (describe known bugs or limitations)
8. History (programs history)
9. Author

Exercise: look at man ls synopsis: `ls [OPTION]... [FILE]...`  
This mean we can in ~ dir `ls -al dirtest1/dirtest2 dirtest1/testfile1`

Synopsis of `man mv`:
**SYNOPSIS**
       **mv** [OPTION]... [-T] SOURCE DEST
       **mv** [OPTION]... SOURCE... DIRECTORY
       **mv** [OPTION]... -t DIRECTORY SOURCE...

Move multiple files to one dir: `mv testfile1 testfile2 testdir`

###`less`###

`less` is a pager reader which show one page at a time. Use the following for navigation:

1. `H` or `h` -> help
2. `Down arrow`, `Enter`, `CTRL+N`, `CTRL+E`, `CTRL+J` -> move down one line
3. `Page Down`, `spacebar`, `CTRL+V` `CTRL+F` -> move down one screen
4. `Up Arrow`, `y`, `CTRL+y` -> move up one line
5. `Page Up`, , `CTRL+B` -> move up one screen
6. `g` -> start of page
6. `G` -> end or page
7. `/pattern` -> search forward for 'pattern'
8. `?pattern` -> search backword for `pattern`
9. `n` or `/` -> repeats previous search
10. `q` -> quits`

###`info`###

Newer information system than `man`. Most notable: support for hyperlinks.

`info keyword`

Keys to control info:

1. `?` -> displays help info
2. `N` -> Moves to next node in series or level
3. `P` -> Moves back in a series or level
4. `U` -> Moves up one level in the hierarchy
5. `Arrow Keys` -> move around the screen
6. `Page Up` or `DEL` -> scroll up within a node
7. `Page Down or `SPACE` -> scroll down within a node
8. `Enter` -> Move to selected node
9. `L` -> Display last info page you read
10. `T` -> Display the top page for a topic
11. `Q` -> Exit

'*' is a link

###README, Config files, RPM, `locate`, `find`, `whereis`, */usr/share/doc/*

####README####

README for unzipped source files are usually in:

1. */usr/doc/packagename*
2. */usr/share/doc/packagename*
3. */usr/share/doc/packages/packagename*

Sometimes the format is PostScript, PDF or HTML instead of plain text

####Config Files####

Can be found in: */etc*

####RPM####

`rpm -ql packagename | grep doc` -> shows where documentation is

####`locate`, `find` `whereis`

1. `find /usr/share/doc -name "*passwd*"' -> find in /usr/share/doc anything with name *passwd*
2. locate passwd
3. whereis passwd 

