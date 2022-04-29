/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:21:33 by epilar            #+#    #+#             */
/*   Updated: 2022/04/29 11:30:11 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	do_pipe(t_pipex *pipex, char **av, char **env)
// {
// 	char	**path_arr;
// 	char	**paths;
// 	char	**args;
// 	char	**bin_paths;

// 	path_arr = get_paths_arr(env);
// 	if (!paths)
// 	{
// 		close(pipex->infile);
// 		close(pipex->outfile);
// 		print_error(PATH_ERR);
// 		exit(1);
// 	}
// }

void	clear_pipex(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	close(pipex->pipe_fds[0]);
	close(pipex->pipe_fds[1]);
	// if (pipex->cmd_paths)
	// 	free(pipex->cmd_paths)...
}

void	check_arguments(int ac, char **av, char **env)
{
	if (ac != 5)
		print_error(WRONG_ARGS_NUM);
	if (!av || !env)
		print_error(WRONG_ARGS);
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

void	prepare_struct(t_pipex *pipex)
{
	pipex->cmd_paths = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	check_arguments(ac, av, env);
	prepare_struct(&pipex);
	open_inoutfiles(&pipex, ac, av);
	if (pipe(pipex.pipe_fds) < 0)
	{
		clear_pipex(&pipex);
		print_error(MAKE_TUBE);
	}
	pipex.cmd_paths = get_paths_arr(env);
	// do_pipe(&pipex, av, env);
	return (0);
}
