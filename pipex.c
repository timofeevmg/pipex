/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:21:33 by epilar            #+#    #+#             */
/*   Updated: 2022/04/28 15:33:45 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int *fds, char **av, char **env)
{
	char	**paths;
	char	**cmds;
	char	**cmds_args;
	char	**bin_paths;

	paths = get_paths_arr(env);
	if (!paths)
	{
		close(fds[0]);
		close(fds[1]);
		print_error(PATH_ERR);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	int	fds[2];

	if (ac != 5)
	{
		print_error(WRONG_ARG_NUM);
		exit(1);
	}
	fds[0] = open_inputfile(av[1]);
	if (fds[0] < 0)
	{
		print_error(OPEN_INFILE);
		exit(1);
	}
	fds[1] = create_outputfile(av[4]);
	if (fds[1] < 0)
	{
		print_error(CREAT_OUTFILE);
		exit(1);
	}
	pipex(fds, av, env);
	return (0);
}
