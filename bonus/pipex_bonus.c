/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:45:19 by epilar            #+#    #+#             */
/*   Updated: 2022/05/20 15:39:06 by epilar           ###   ########.fr       */
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

char	*find_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*try;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!try)
			return (NULL);
		if (access(try, F_OK | X_OK) == 0)
			return (try);
		free(try);
		paths++;
	}
	return (NULL);
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
//////////////////////////////////////////////////////

/* init pipe_fds array */
	pipex.pipe_fds = (int **)malloc(sizeof(int *) * pipex.pipe_num);
	int i = 0;
	while (i < pipex.pipe_num)
	{
		pipex.pipe_fds[i] = (int *)malloc(sizeof(int) * 2);
		pipe(pipex.pipe_fds[i]);
		i++;
	}
/**********************/

	pipex.cmd_id = 0;
	while(pipex.cmd_id < pipex.cmd_num)
	{
		pipex.pid = fork();
		if (pipex.pid == 0)
		{
			if (pipex.cmd_id == 0)
			{
				dup2(pipex.infile, 0);
				dup2(pipex.pipe_fds[0][1], 1);
			}
			else if (pipex.cmd_id == pipex.cmd_num - 1)
			{
				dup2(pipex.outfile, 1);
				dup2(pipex.pipe_fds[pipex.pipe_num - 1][0], 0);
			}
			else
				dup2(pipex.pipe_fds[pipex.cmd_id][0], 0);
				dup2(pipex.pipe_fds[pipex.cmd_id][1], 1);
		}
		pipex.cmd_id++;
	}

	// char	**cmd_args;
	// char	*cmd_place;
	// int		i;
	// int		in;
	// int		fd[2];

	// in = 0;
	// i = 0;
	// while (i < pipex.cmd_num - 2)
	// {
	// 	pipe(fd);
	// 	spawn_proc(in, fd[1], av[i + 2 + pipex.isheredoc], env, &pipex);
	// 	close(fd[1]);
	// 	in = fd[0];
	// 	i++;
	// }
	// if (in != 0)
	// 	dup2(in, 0);
	// cmd_args = ft_split(av[i + 2 + pipex.isheredoc], ' ');
	// cmd_place = find_cmd(pipex.cmd_paths, cmd_args[0]);
	// execve(cmd_place, cmd_args, env);
	// waitpid(-1, NULL, 0);
	

	return (0);
}
