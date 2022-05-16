all:
	gcc mandatory/pipex.c \
		mandatory/check_open.c \
		mandatory/env_paths.c \
		mandatory/child_proc.c \
		mandatory/clean_close_exit.c \
		libft/libft.a -o pipex

debug:
	gcc -g pipex.c utilities/print_error.c utilities/check_open_file.c libft/libft.a