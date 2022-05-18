/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:41:15 by epilar            #+#    #+#             */
/*   Updated: 2022/05/18 14:27:21 by epilar           ###   ########.fr       */
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
# define MAKE_TUBE		"Attempt to create a pipe"
# define PATH_ERR		"Can`t find paths to binaries in env"
# define NO_PATHS		"Can`t get paths to binaries"
# define FORK_FAIL		"FORK call failed"
# define WAIT_FAIL		"Attempt to wait proccess"
# define DUP_FAIL		"Attempt to duplicate obj descriptor"
# define CMD_AV_F		"Attempt to get command arguments"
# define CMD_PLACE		"Attemp to find command location"
# define EXE_CMD		"Attemp to execute command"

# define HEREDOC_FILE	".here_doc"

# define NOFDS		0b0000
# define INFD		0b0001
# define OUTFD		0b0010
# define HDFD		0b0100

typedef struct s_pipex
{
	char	openedfds;
	int		isheredoc;
	int		cmd_num;
	int		infile;
	int		outfile;

}	t_pipex;

// void	check_arguments(int ac, char **av, char **env);

// void	open_inoutfiles(t_pipex *pipex, int ac, char **av);
// int		open_inputfile(char *path);
// int		create_outputfile(char *path);

// char	**get_paths_arr(char **env);
// char	*get_pathstr_from_env(char **env);

// void	child_proc1(t_pipex *pipex, char **av, char **env);
// void	child_proc2(t_pipex *pipex, char **av, char **env);

// void	clean_exit(t_pipex *pipex, char *msg);
// void	clean_memory(t_pipex *pipex);
// void	close_pipe(t_pipex *pipex);
// void	close_files(t_pipex *pipex);
// void	print_error(char *msg);

#endif