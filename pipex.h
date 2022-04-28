/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:30:11 by epilar            #+#    #+#             */
/*   Updated: 2022/04/28 15:36:54 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_SIMPLE
# define PIPEX_SIMPLE

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>

# include "libft/libft.h"

# define WRONG_ARG_NUM	"Number of arguments should be 4"
# define OPEN_INFILE	"Attempt to open input file"
# define CREAT_OUTFILE	"Attempt to create output file"
# define PATH_ERR		"Can`t find paths to binaries in env"

void	print_error(char *msg);

int		open_inputfile(char *path);
int		create_outputfile(char *path);

char	**get_paths_arr(char **env);
char	*get_pathstr_from_env(char **env);
char	*cut_pathstr(char *str);

void	pipex(int *fds, char **av, char **env);

#endif