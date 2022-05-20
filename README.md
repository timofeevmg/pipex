# pipex
C programm, behaves like bash "pipe" command

test commands:
````
input:
1 test
2 fail
3 nothing
hello
````
- ./pipex input "grep hello" "wc -l" ouput\
  < input grep "hello" | wc -l > output

````
input:
.
````
- ./pipex input "ls -l" "wc -l" output\
  < input ls -l | wc -l > output
  
````
input:
libft
````
- ./pipex input "cat -e" "cat -e" output\
  < input cat -e | cat -e > output

echo $?

/* BONUS */
````
cat << ALL | cat -e | wc -l >> output
````
