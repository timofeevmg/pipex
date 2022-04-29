/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:30:11 by epilar            #+#    #+#             */
/*   Updated: 2022/04/29 11:10:28 by epilar           ###   ########.fr       */
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

# include "libft/libft.h"

# define WRONG_ARGS_NUM	"Number of arguments should be 4"
# define WRONG_ARGS		"Wrong main argument(-s)"
# define OPEN_INFILE	"Attempt to open input file"
# define CREAT_OUTFILE	"Attempt to create output file"
# define MAKE_TUBE		"Attempt to create a pipe"
# define PATH_ERR		"Can`t find paths to binaries in env"

typedef struct s_pipex
{
	int	infile;
	int	outfile;
	int	pipe_fds[2];
	char	**cmd_paths;
} t_pipex;


void	print_error(char *msg);

int		open_inputfile(char *path);
int		create_outputfile(char *path);

char	**get_paths_arr(char **env);
char	*get_pathstr_from_env(char **env);
char	*cut_pathstr(char *str);

#endif