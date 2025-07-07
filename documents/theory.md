## Heredoc (https://linuxize.com/post/bash-heredoc/)

'CMD << DELIMITER'
	'     '
	'DELIMITER'

cat << EOF
The current working directory is: $PWD
You are logged in as: $(whoami)
EOF

<<- 	Makes it so leading tabs are stripped
'EOF'	Makes it so env vars are ignored

## Operators
'<' 	Input Redirection
'<<' 	Heredoc
'|'		
'>' 	Output Redirection: (Overwrites)
'>>' 	Output Redirection: (Appends)
'&'


## Useful:
### lsof
Checks for open fds

## Function summaries:

### pipe 
Takes an int fd[2] as input, and outputs two fds:
fd[0] becomes the read end and fd[1] becomes the write end

### fork
Duplicates a running process, copying it's memory space but sets the pid of the child process to 0. 

### execve
Executes a program, replacing the process image with the program's.

### dup/dup2
dup duplicates the specified file descriptor to the first fd available. It's the equivalent to creating a tmp variable but for fds.
Dup2 replaces an fd with another, dup2(src, dst)

Example:
stdin_tmp = dup(0);
open new_fd
dup2(new_fd, 0);
read from new_fd
dup2(stdin_tmp, 0);
close(new_fd);


### wait/waitpid
Waits for the child process to complete

### access: [int access(const char *path, int amode)]
Checks for permissions and verifies if the file exists

(R_OK 4, W_OK 2, X_OK 1, F_OK 0)
0 	--- (F)
1 	--x (X)
2 	-w- (W)
4 	r-- (R)
3 	-wx (W | X)
5 	r-x (R | X)
6 	rw- (R | W)
7 	rwx (R | W | X)

Files and directories store three accesses:
Owner, Group, All

### unlink
Deletes a file
