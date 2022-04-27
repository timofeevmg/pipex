/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:30:11 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 15:28:00 by epilar           ###   ########.fr       */
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

# define WRONG_ARG_NUM	"Number of arguments should be 4.\n"
# define OPEN_INFILE	"Attempt to open input file"
# define CREAT_OUTFILE	"Attempt to create output file"

void	print_error(char *msg);
int		open_inputfile(char *path);
int		create_outputfile(char *path);
void	pipex(int f_in, int f_out, char **av, char **env);

#endif