/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:30:11 by epilar            #+#    #+#             */
/*   Updated: 2022/05/16 16:56:20 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/libft.h"

# define WRONG_ARGS_NUM	"Number of arguments should be 4"
# define WRONG_ARGS		"Wrong main argument(-s)"
# define OPEN_INFILE	"Attempt to open input file"
# define CREAT_OUTFILE	"Attempt to create output file"
# define MAKE_TUBE		"Attempt to create a pipe"
# define PATH_ERR		"Can`t find paths to binaries in env"
# define NO_PATHS		"Can`t get paths to binaries"
# define FORK_FAIL		"FORK call failed"
# define WAIT_FAIL		"Attempt to wait proccess"
# define DUP_FAIL		"Attempt to duplicate obj descriptor"
# define CMD_AV_F		"Attempt to get command arguments"
# define CMD_PLACE		"Attemp to find command location"
# define EXE_CMD		"Attemp to execute command"

# define NOFDS		0b00000000
# define INFD		0b00000001
# define OUTFD		0b00000010
# define PIPE0FD	0b00000100
# define PIPE1FD	0b00001000

typedef struct s_pipex
{
	char	opened_fds;
	int		infile;
	int		outfile;
	int		pipe_fds[2];
	char	**cmd_paths;
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd_place;
	char	**cmd_args;
} t_pipex;

void	check_arguments(int ac, char **av, char **env);

void	open_inoutfiles(t_pipex *pipex, int ac, char **av);
int		open_inputfile(char *path);
int		create_outputfile(char *path);

char	**get_paths_arr(char **env);
char	*get_pathstr_from_env(char **env);

void	child_proc1(t_pipex *pipex, char **av, char **env);
void	child_proc2(t_pipex *pipex, char **av, char **env);

void	clean_exit(t_pipex *pipex, char *msg);
void	clean_memory(t_pipex *pipex);
void	close_pipe(t_pipex *pipex);
void	close_files(t_pipex *pipex);
void	print_error(char *msg);

#endif
