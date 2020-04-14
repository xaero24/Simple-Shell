# Simple Shell

A simple implementation of a shell interface. Supported commands are:

`pwd` - print PWD
`cd DIRNAME` - change directory
`Cat > FILENAME` - write to file
`nano FILENAME` - write to file
`cat FILENAME` - show file contents
`wc [-l|-w|-c] FILENAME` - count lines, words or chars of a filename
`cp SRCFILE DSTFILE` - copy source file to dest file
`sort [-r] FILENAME` - sort file or sort in reverse
`grep [-c] PATTERN FILENAME` - find patterns in a file nd print them or their count
`man COMMAND` - command's manpage
`exit` - exit the simple shell

For more information refer to th manpage of each command.

Also the shell supports the pipe operator (`|` between commands).

### How to run:
In the shell type:
`$ make`
`$ ./sshell`
Then, in the simple shell interface, type your commnds, e.g.:
```
+: pwd
/home/User/Documents/Simple-Shell/shell
+: nano file1.txt
this
is
my new
file

+: cat file1.txt
this
is
my new
file
+: grep my file1.txt
my new
+: exit
```

### TODO:
- [X] pwd
- [X] cd
- [X] Cat > + nano
- [X] cat
- [X] wc
- [X] cp
- [ ] pipe
- [ ] sort
- [ ] grep
- [X] man
- [ ] exit
- [ ] Put all declarations in header file
- [ ] TEST ALL