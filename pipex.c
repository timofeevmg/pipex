/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:21:33 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 15:33:16 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	pipex(int f_in, int f_out, char **av, char **env)
// {
	
// }
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
	return fd;
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
	return fd;
}

int	main(int ac, char **av, char **env)
{
	int	f_in;
	int	f_out;
	int	ret;

	if (ac != 5)
	{
		print_error(WRONG_ARG_NUM);
		exit(1);
	}
	f_in = open_inputfile(av[1]);
	if (f_in < 0)
	{
		print_error(OPEN_INFILE);
		exit(1);
	}
	f_out = create_outputfile(av[4]);
	if (f_out < 0)
	{
		print_error(CREAT_OUTFILE);
		exit(1);
	}
	// pipex(f_in, f_out, av, env);
	return (0);
}
