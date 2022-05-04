/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:43:38 by epilar            #+#    #+#             */
/*   Updated: 2022/05/04 14:29:03 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_inputfile(char *path)
{
	int	ret;
	int	fd;
	char	buf[8];

	ret = access(path, F_OK | R_OK);
	if (ret < 0)
		return ret;
	fd = open(path, O_RDONLY);
	ret = read(fd, buf, 1);
	if (ret < 0)
		return ret;
	return (fd);
}

int create_outputfile(char *path)
{
	int	ret;
	int	fd;

	ret = access(path, F_OK);
	if (ret == 0)
	{
		ret = access(path, W_OK);
		if (ret < 0)
			return ret;
	}
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

void	open_inoutfiles(t_pipex *pipex, int ac, char **av)
{
	pipex->infile = open_inputfile(av[1]);
	if (pipex->infile < 0)
		print_error(OPEN_INFILE);
	pipex->outfile = create_outputfile(av[ac - 1]);
	if (pipex->outfile < 0)
	{
		close(pipex->infile);
		print_error(CREAT_OUTFILE);
	}
}

void	check_arguments(int ac, char **av, char **env)
{
	if (ac != 5)
		print_error(WRONG_ARGS_NUM);
	if (!av || !env)
		print_error(WRONG_ARGS);
}
