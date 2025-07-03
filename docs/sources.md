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

## To remember:
'<' 	Input Redirection
'<<' 	Heredoc
'|'		
'>' 	Output Redirection: (Overwrites)
'>>' 	Output Redirection: (Appends)
