/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:43:41 by epilar            #+#    #+#             */
/*   Updated: 2022/05/24 11:04:35 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	prepare_struct(t_pipex *pipex, char **av)
{
	pipex->filelst = NOFDS;
	pipex->isheredoc = check_heredoc(av[1]);
	pipex->cmd_paths = NULL;
	pipex->cmd_id = 0;
	pipex->pipe_id = -1;
}

int	open_inputfile(char **av, t_pipex *pipex)
{
	char	*input;
	int		ret;
	int		fd;

	if (pipex->isheredoc)
	{
		create_heredoc(pipex, av[2]);
		input = ft_strdup(HEREDOC_FILE);
	}
	else
		input = ft_strdup(av[1]);
	ret = access(input, F_OK | R_OK);
	if (ret < 0)
	{
		free(input);
		return (ret);
	}
	fd = open(input, O_RDONLY);
	free(input);
	ret = read(fd, NULL, 0);
	if (ret < 0)
		return (ret);
	return (fd);
}

int	create_outputfile(char *path, t_pipex *pipex)
{
	int	ret;
	int	fd;

	ret = access(path, F_OK);
	if (ret == 0)
	{
		ret = access(path, W_OK);
		if (ret < 0)
			return (ret);
	}
	if (pipex->isheredoc)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

void	open_inoutfiles(int ac, char **av, t_pipex *pipex)
{
	pipex->infile = open_inputfile(av, pipex);
	if (pipex->infile < 0)
		clean_exit(pipex, OPEN_INFILE);
	pipex->outfile = create_outputfile(av[ac - 1], pipex);
	if (pipex->outfile < 0)
		clean_exit(pipex, CREAT_OUTFILE);
	pipex->filelst |= INFD;
	pipex->filelst |= OUTFD;
}

void	init_pipes(t_pipex *pipex)
{
	if (pipex)
	{
		pipex->pipe_fds = (int **)malloc(sizeof(int *) * pipex->pipe_num);
		if (!pipex->pipe_fds)
			clean_exit(pipex, MALLOC_FAIL);
		pipex->pipe_id = 0;
		while (pipex->pipe_id < pipex->pipe_num)
		{
			pipex->pipe_fds[pipex->pipe_id] = (int *)malloc(sizeof(int) * 2);
			if (!pipex->pipe_fds[pipex->pipe_id])
				clean_exit(pipex, MALLOC_FAIL);
			if (pipe(pipex->pipe_fds[pipex->pipe_id]) < 0)
				clean_exit(pipex, MAKE_TUBE);
			pipex->pipe_id++;
		}
	}
}
