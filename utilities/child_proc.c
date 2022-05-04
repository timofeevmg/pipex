/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:34:32 by epilar            #+#    #+#             */
/*   Updated: 2022/05/04 13:44:03 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*try;

	while(*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return NULL;
		try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!try)
			return NULL;
		if (access(try, F_OK | X_OK) == 0)
			return try;
		free(try);
		paths++;
	}
	return NULL;
}

void	child_proc1(t_pipex *pipex, char **av, char **env)
{
	if (dup2(pipex->infile, 0) < 0)
	{
		clear_pipex(pipex);
		print_error(DUP_FAIL);
	}
	if (dup2(pipex->pipe_fds[1], 1) < 0)
	{
		clear_pipex(pipex);
		print_error(DUP_FAIL);
	}
	close(pipex->pipe_fds[0]);
	pipex->cmd_args = ft_split(av[2], ' ');
	if (!pipex->cmd_args)
	{
		clear_pipex(pipex);
		print_error(CMD_AV_F);
	}
	pipex->cmd_place = find_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
	if (!pipex->cmd_place)
	{
		clear_pipex(pipex);
		print_error(CMD_PLACE);
	}
	execve(pipex->cmd_place, pipex->cmd_args, env);
}

void	child_proc2(t_pipex *pipex, char **av, char **env)
{
	if (dup2(pipex->outfile, 1) < 0)
	{
		clear_pipex(pipex);
		print_error(DUP_FAIL);
	}
	if (dup2(pipex->pipe_fds[0], 0) < 0)
	{
		clear_pipex(pipex);
		print_error(DUP_FAIL);
	}
	close(pipex->pipe_fds[1]);
	pipex->cmd_args = ft_split(av[3], ' ');
	if (!pipex->cmd_args)
	{
		clear_pipex(pipex);
		print_error(CMD_AV_F);
	}
	pipex->cmd_place = find_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
	if (!pipex->cmd_place)
	{
		clear_pipex(pipex);
		print_error(CMD_PLACE);
	}
	execve(pipex->cmd_place, pipex->cmd_args, env);
}
