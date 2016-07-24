#Vi#

Reference material:
  1. [Vimgifs](https://vimgifs.com/)
  2. [Vimwikia](http://vim.wikia.com/wiki/Vim_Tips_Wiki)

Different modes (is in the bottom line):

1. Normal mode -> after opening a file
2. Insert mode -> edit the text file.`i`,`INSERT`,`s`,`o`, or `a`
3. Command **line** mode via `:` -> Enter commands
  1. `w [nameOfFile]` -> write out to file that was opened or to [nameOfFile]
  2. `q` -> quit
  3. `!` -> several meanings:
     1. It forces a command, such as `:q!` to force quiting even though changes have not been saved
     2. It work as a toggle for certain commands, so `:set cursorline` `:set nocursorline` to `:set cursorline!`
  4. `:noh` -> remove highlight (e.g. after search)
  5. `:set number` -> line numbers
  6. `:scriptnames` -> get all the .vim files that Vim loaded, including .vimrc (Add user settings to *$HOME/vimrc*)
4. Command mode, default mode to quickly navigate via shortkeys:
 
Deleting:
   
  1. `dw` -> delete word after cursor **and the space after the word**
  2. `de` -> delete word after cursor
  3. `dd` -> delete entire line
 
Yanking(copying):
 
  1. `yw` -> yank (copy) entire word *and the space after the word**
  2. `ye` -> yank (copy) entire word
  3. `yy` -> yank (copy) entire line
   
Paste:

  1. `p`  -> paste what was just deleted or yanked

Moving:
   
 1. `/` -> search for a term, this will highlight the term
 2. `w` -> move to next word
 3. `b` -> move to previous word
 4. `nG` -> move to the nth line of file
 5. `G` -> move to last line of file

Selecting:

  1. 'v' -> enter visual select. Move with Arrows or use nG to move to a line.

Group alteration
  1. '>' or '<' -> (un)indent a group selection

Replace:

  1. '%s/search/replace/g' -> search an replace global

  [More options](http://vim.wikia.com/wiki/Search_and_replace)
  
