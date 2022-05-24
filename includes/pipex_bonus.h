/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:41:15 by epilar            #+#    #+#             */
/*   Updated: 2022/05/24 11:06:12 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/libft.h"
# include "../bonus/gnl/get_next_line.h"

# define WRONG_ARGS_NUM	"Wrong number of arguments"
# define WRONG_ARGS		"Wrong main argument(-s)"
# define OPEN_INFILE	"Attempt to open input file"
# define CREAT_OUTFILE	"Attempt to create output file"
# define CREAT_HEREDOC	"Attempt to create temporary file"
# define READ_STDIN		"Attempt to read from STDIN"
# define MAKE_TUBE		"Attempt to create a pipe"
# define PATH_ERR		"Can`t find paths to binaries in env"
# define NO_PATHS		"Can`t get paths to binaries"
# define FORK_FAIL		"FORK call failed"
# define WAIT_FAIL		"Attempt to wait proccess"
# define DUP_FAIL		"Attempt to duplicate obj descriptor"
# define CMD_AV_F		"Attempt to get command arguments"
# define CMD_PLACE		"Attemp to find command location"
# define EXE_CMD		"Attemp to execute command"
# define MALLOC_FAIL	"Attemp to allocate memory"

# define HEREDOC_FILE	".here_doc"

# define NOFDS		0b0000
# define INFD		0b0001
# define OUTFD		0b0010
# define HDFD		0b0100

typedef struct s_pipex
{
	char	filelst;
	int		isheredoc;
	int		infile;
	int		outfile;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd_place;
	int		cmd_num;
	int		cmd_id;
	int		pipe_num;
	int		pipe_id;
	int		**pipe_fds;
	pid_t	pid;
}	t_pipex;

void	open_inoutfiles(int ac, char **av, t_pipex *pipex);
int		open_inputfile(char **av, t_pipex *pipex);
void	create_heredoc(t_pipex *pipex, char *limiter);
int		create_outputfile(char *path, t_pipex *pipex);
void	init_pipes(t_pipex *pipex);

int		check_heredoc(char *arg);
void	prepare_struct(t_pipex *pipex, char **av);

char	**get_paths_arr(char **env);
char	*get_pathstr_from_env(char **env);
char	*find_cmd(char **paths, char *cmd);

void	print_error(char *msg);
void	clean_exit(t_pipex *pipex, char *msg);
void	close_files(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	clean_memory(t_pipex *pipex);

#endif