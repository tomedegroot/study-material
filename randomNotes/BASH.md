#BASH Random Notes#

##`$_`

`$_` -> last arguments of the previous commands. Example usage:
`mkdir testdir`
`cd $_` (Here $_ is substituted for testdir)

##`<<<` Here String

```
<<< word

The word is expanded and supplied to the command on its standard input.
```

Nice trick: `git commit --amend <<< :wq`

`:wq` is feed to VIM and this way the commit messageis not edited
