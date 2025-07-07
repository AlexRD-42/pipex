Your program should be executed as follows:

`./pipex file1 cmd1 cmd2 file2`

• **file1** and **file2** are file names.

• **cmd1** and **cmd2** are shell commands with their parameters

It must behave exactly like the following shell command:
`< file1 cmd1 | cmd2 > file2`
file1 becomes standard input for cmd1
cmd1's output is piped to cmd2's input
cmd2's output is redirected to file2



`./pipex file1 "ls -l" "wc -l" file2` 	== `< file1 ls -l | wc -l > file2`

`./pipex file1 "grep a1" "wc -w" file2` == `< file1 grep a1 | wc -w > file2`

Bonus:

• Handle multiple pipes:

`./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2` == `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`

• Support « and » when the first parameter is "here_doc"

`./pipex here_doc LIMITER cmd cmd1 file` == `cmd << LIMITER | cmd1 >> file`