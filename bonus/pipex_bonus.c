/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:45:19 by epilar            #+#    #+#             */
/*   Updated: 2022/05/24 11:05:20 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	count_commands(int ac, t_pipex *pipex)
{
	if (ac < 5 || (ac < 6 && pipex->isheredoc))
		return (-1);
	pipex->cmd_num = ac - 3 - pipex->isheredoc;
	pipex->pipe_num = pipex->cmd_num - 1;
	return (0);
}

int	dup_fds(t_pipex *pipex)
{
	if (pipex->cmd_id == 0)
	{
		if (dup2(pipex->pipe_fds[0][1], 1) < 0)
			return (-1);
		if (dup2(pipex->infile, 0) < 0)
			return (-1);
	}
	else if (pipex->cmd_id == pipex->cmd_num - 1)
	{
		if (dup2(pipex->pipe_fds[pipex->pipe_num - 1][0], 0) < 0)
			return (-1);
		if (dup2(pipex->outfile, 1) < 0)
			return (-1);
	}
	else
	{
		if (dup2(pipex->pipe_fds[pipex->cmd_id - 1][0], 0) < 0)
			return (-1);
		if (dup2(pipex->pipe_fds[pipex->cmd_id][1], 1) < 0)
			return (-1);
	}
	return (0);
}

void	do_pipe(t_pipex *pipex, char **av, char **env)
{
	while (pipex->cmd_id < pipex->cmd_num)
	{
		pipex->pid = fork();
		if (pipex->pid < 0)
			clean_exit(pipex, FORK_FAIL);
		if (pipex->pid == 0)
		{
			if (dup_fds(pipex) < 0)
				clean_exit(pipex, DUP_FAIL);
			close_pipes(pipex);
			pipex->cmd_args = \
			ft_split(av[pipex->cmd_id + 2 + pipex->isheredoc], ' ');
			pipex->cmd_place = find_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
			if (execve(pipex->cmd_place, pipex->cmd_args, env) < 0)
				clean_exit(pipex, EXE_CMD);
		}
		pipex->cmd_id++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex		pipex;

	if (!av || !env)
		clean_exit(&pipex, WRONG_ARGS);
	prepare_struct(&pipex, av);
	if (count_commands(ac, &pipex) < 0)
		clean_exit(&pipex, WRONG_ARGS_NUM);
	open_inoutfiles(ac, av, &pipex);
	pipex.cmd_paths = get_paths_arr(env);
	if (!pipex.cmd_paths)
		clean_exit(&pipex, NO_PATHS);
	init_pipes(&pipex);
	do_pipe(&pipex, av, env);
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	close_files(&pipex);
	clean_memory(&pipex);
	return (0);
}
