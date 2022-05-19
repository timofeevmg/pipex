/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:45:19 by epilar            #+#    #+#             */
/*   Updated: 2022/05/19 15:02:40 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	count_commands(int ac, t_pipex *pipex)
{
	if (ac < 5 || (ac < 6 && pipex->isheredoc))
		return (-1);
	pipex->cmd_num = ac - 3 - pipex->isheredoc;
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

	//char	**tmp = av;
	int	cmd_id = 1;
	while (cmd_id <= pipex.cmd_num)
	{
		int		pipe_fds[2];
		pid_t	pid;
		char	**cmd_args;
		char	*cmd_place;

		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
		{
			if (cmd_id == 1)
				dup2(pipex.infile, STDIN_FILENO);
			if (cmd_id == pipex.cmd_num)
				dup2(pipex.outfile, STDOUT_FILENO);
			dup2(pipe_fds[1], STDOUT_FILENO);
			dup2(pipe_fds[0], STDIN_FILENO);
			cmd_args = ft_split(av[cmd_id + 1 + pipex.isheredoc], ' ');
			cmd_place = find_cmd(pipex.cmd_paths, cmd_args[0]);
			execve(cmd_place, cmd_args, env);
		}
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	waitpid(-1, NULL, 0);
	return (0);
}
