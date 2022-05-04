/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:21:33 by epilar            #+#    #+#             */
/*   Updated: 2022/05/04 13:48:40 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int	*pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

void	clear_pipex(t_pipex *pipex)
{
	int	i;

	close(pipex->infile);
	close(pipex->outfile);
	close_pipe(pipex->pipe_fds);
	if (pipex->cmd_paths)
	{
		i = 0;
		while(pipex->cmd_paths[i])
			free(pipex->cmd_paths[i++]);
		free(pipex->cmd_paths);
	}
	if (pipex->cmd_args)
	{
		i = 0;
		while(pipex->cmd_args[i])
			free(pipex->cmd_args[i++]);
		free(pipex->cmd_args);
	}
	if (pipex->cmd_place)
		free(pipex->cmd_place);
}

void	check_arguments(int ac, char **av, char **env)
{
	if (ac != 5)
		print_error(WRONG_ARGS_NUM);
	if (!av || !env)
		print_error(WRONG_ARGS);
}

void	prepare_struct(t_pipex *pipex)
{
	pipex->cmd_paths = NULL;
	pipex->cmd_place = NULL;
	pipex->cmd_args = NULL;
}

void	wait4process(t_pipex *pipex)
{
	if (waitpid(pipex->pid1, NULL, 0) < 0)
	{
		clear_pipex(pipex);
		print_error(WAIT_FAIL);
	}
	if (waitpid(pipex->pid2, NULL, 0) < 0)
	{
		clear_pipex(pipex);
		print_error(WAIT_FAIL);
	}
}

void	do_pipe(t_pipex *pipex, char **av, char **env)
{	
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
	{
		clear_pipex(pipex);
		print_error(FORK_FAIL);
	}
	if (!pipex->pid1)
		child_proc1(pipex, av, env);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
	{
		clear_pipex(pipex);
		print_error(FORK_FAIL);
	}
	if (!pipex->pid2)
		child_proc2(pipex, av, env);
	close_pipe(pipex->pipe_fds);
	wait4process(pipex);
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
	if (!pipex.cmd_paths)
	{
		clear_pipex(&pipex);
		print_error(NO_PATHS);
	}
	do_pipe(&pipex, av, env);
	clear_pipex(&pipex);
	return (0);
}
