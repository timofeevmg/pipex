/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:21:33 by epilar            #+#    #+#             */
/*   Updated: 2022/05/16 12:55:35 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	prepare_struct(t_pipex *pipex)
{
	pipex->opened_fds = NOFDS;
	pipex->cmd_paths = NULL;
	pipex->cmd_place = NULL;
	pipex->cmd_args = NULL;
}

void	wait4process(t_pipex *pipex)
{
	if (waitpid(pipex->pid1, NULL, 0) < 0)
		clean_exit(pipex, WAIT_FAIL);
	if (waitpid(pipex->pid2, NULL, 0) < 0)
		clean_exit(pipex, WAIT_FAIL);
}

void	do_pipe(t_pipex *pipex, char **av, char **env)
{	
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		clean_exit(pipex, FORK_FAIL);
	if (!pipex->pid1)
		child_proc1(pipex, av, env);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		clean_exit(pipex, FORK_FAIL);
	if (!pipex->pid2)
		child_proc2(pipex, av, env);
	close_pipe(pipex);
	wait4process(pipex);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	check_arguments(ac, av, env);
	prepare_struct(&pipex);
	open_inoutfiles(&pipex, ac, av);
	if (pipe(pipex.pipe_fds) < 0)
		clean_exit(&pipex, MAKE_TUBE);
	pipex.opened_fds = pipex.opened_fds | PIPE0FD | PIPE1FD;
	pipex.cmd_paths = get_paths_arr(env);
	if (!pipex.cmd_paths)
		clean_exit(&pipex, NO_PATHS);
	do_pipe(&pipex, av, env);
	close_pipe(&pipex);
	close_files(&pipex);
	clean_memory(&pipex);
	return (0);
}
