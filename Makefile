all:
	gcc pipex.c utilities/print_error.c \
				utilities/check_open_file.c \
				utilities/path_from_env.c \
				libft/libft.a -o test

debug:
	gcc -g pipex.c utilities/print_error.c utilities/check_open_file.c libft/libft.a