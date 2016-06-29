#Turning commands into a Scripts/VI#

##Nano###
1. `CTRL+K` -> Cut line
2. `CTRL+O` -> Save file
3. `CTRL+U` -> Uncut text

##Vi##

Diifferent modes (is in the bottom line):
1. Normal mode -> after opening a file
2. Insert mode -> edit the text file.`i`,`INSERT`,`s`,`o`, or `a`
3. Command mode:  
  Deleting:  
  1. `dw` -> delete word after cursor **and the space after the word**
  2. `de` -> delete word after cursor
  3. `dd` -> delete entire line  
  Yanking(copying):  
  4. `yw` -> yank (copy) entire word *and the space after the word**
  5. `ye` -> yank (copy) entire word
  6. `yy` -> yank (copy) entire line  
  Paste:  
  7. `p`  -> paste what was just deleted or yanked  
  Moving:  
  8. `/` -> search for a term, this will highlight the term  
  9. `w` -> move to next word  
  10. `b` -> move to previous word  
  11. `nG` -> move to the nth line of file  
  12. `G` -> move to last line of file  
4. Command **line** mode via `:` -> Enter commands
  1. `w [nameOfFile]` -> write out to file that was opened or to [nameOfFile]
  2. `q` -> quit
  3. `!` -> several meanings:
     1. It forces a command, such as `:q!` to force quiting even though changes have not been saved
     2. It work as a toggle for certain commands, so `:set cursorline` `:set nocursorline` to `:set cursorline!`
  4. `:noh` -> remove highlight (e.g. after search)
  5. `:set number` -> line numbers
  6. `:scriptnames` -> get all the .vim files that Vim loaded, including .vimrc (Add user settings to *$HOME/vimrc*)
##Basic Shell Scripting##

Scripts need an interperteter (*/bin/bash*). The script has access to:
1. Variables, e.g. $USER
2. Arguments:
  1. `$1` -> First Argument
  2. `$2` -> Second Argument
  3. `$?` -> Exit code/Status of previous statement (0 for success, non-zero for an error)

