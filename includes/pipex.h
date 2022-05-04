/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:30:11 by epilar            #+#    #+#             */
/*   Updated: 2022/05/04 14:16:41 by epilar           ###   ########.fr       */
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

typedef struct s_pipex
{
	int	infile;
	int	outfile;
	int	pipe_fds[2];
	char	**cmd_paths;
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd_place;
	char	**cmd_args;
} t_pipex;

void	print_error(char *msg);

void	check_arguments(int ac, char **av, char **env);

void	open_inoutfiles(t_pipex *pipex, int ac, char **av);
int		open_inputfile(char *path);
int		create_outputfile(char *path);

char	**get_paths_arr(char **env);
char	*get_pathstr_from_env(char **env);

void	child_proc1(t_pipex *pipex, char **av, char **env);
void	child_proc2(t_pipex *pipex, char **av, char **env);

void	clear_pipex(t_pipex *pipex);
void	close_pipe(int	*pipe);
void	close_files(t_pipex *pipex);

#endif