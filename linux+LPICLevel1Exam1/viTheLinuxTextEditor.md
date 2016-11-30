#Vi Modes & The Importance of Vi

Check the course notes for the information on VI. Three modes:

1. Command mode (starting mode)
2. Ex mode (or colon mode)
3. Insert mode

#Vi Commands and Usage

Most  distro's have vim. The commands of vi are upwards compatible

##Commmand mode

###Navigation
1. Up -> k
2. Down -> j
3. Right -> l
4. Left -> h

5. Move to last line of SCREEN -> L
6. Move to first line of SCREEN -> H

7. Move to last line of FILE -> G
8. nG -> go to nth line

9. Begin of word -> b
10. End of word -> w

11. Begin of line -> B
12. End of line -> W
###Yanking

1. Yank (copy) line -> yy
2. Yank n lines -> nyy

###Deleting

1. Delete line -> yy
2. Delete n lines -> nyy
3. Delete till x -> dtx
4. Delete with (f) x -> dfx
5. Delete till end of word and space after word -> dW(ith space)
6. Delete till End of word without space -> dE

###Visual Selection
1. Visual select -> v

###Pasting

1. Paste on line after cursor -> p
2. Paste on line before cursor -> P

###Undo & Redo

1. Undo -> u
2. Redo -> R

###Search

1. search -> / or ?
2. next -> n
3. previous -> N

###Various

1. Change until end of word -> cw (= change word)
2. Delete line and insert -> cc

##Insert mode

Type `i` in command mode to go to insert mode

Type `R` in command mode to go to replace mode. This replaces the text the cursor is on.

##Ex mode

Type `:` in command mode

###[Search and replace](http://vim.wikia.com/wiki/Search_and_replace)

General command:

`:SEARCHRANGE/search/replace[/OPTION]`

SEARCHRANGE:
`s` -> current line
`%s` -> all lines
`5,12s` -> lines 5 to 12
`'<,'>s` -> visual selection

OPTIONS:
1. without option it searches only for first occurences in per line
2. `g` -> global search for all occurences per line
3. `c` -> ask for confirmation

SEARCH:
1. By default the string in search
2. \<string\> -> change only whole words 'string'

###Save and Quit

quit -> q
save -> w(rite)
force (so quit without saving) -> q!

###Load a file

1. Load file -> `:edit FILEPATH`
2. Load a contents of file in cursor place -> r/FILEPATH, example: `:r/etc/ssh/ssh_config`

###Execute bash commands

1. :!COMMAND -> execute the COMMAND, except for chdir:
2. :cd DIR -> change dir, so withouth the **!**
