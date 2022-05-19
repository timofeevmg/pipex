/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_close_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:05:44 by epilar            #+#    #+#             */
/*   Updated: 2022/05/19 11:53:08 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipe(t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->opened_fds & PIPE0FD)
			close(pipex->pipe_fds[0]);
		if (pipex->opened_fds & PIPE1FD)
			close(pipex->pipe_fds[1]);
	}
}

void	close_files(t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->opened_fds & INFD)
			close(pipex->infile);
		if (pipex->opened_fds & OUTFD)
			close(pipex->outfile);
	}
}

void	clean_memory(t_pipex *pipex)
{
	int	i;

	if (pipex)
	{
		if (pipex->cmd_paths)
		{
			i = 0;
			while (pipex->cmd_paths[i])
				free(pipex->cmd_paths[i++]);
			free(pipex->cmd_paths);
		}
		if (pipex->cmd_args)
		{
			i = 0;
			while (pipex->cmd_args[i])
				free(pipex->cmd_args[i++]);
			free(pipex->cmd_args);
		}
		if (pipex->cmd_place)
			free(pipex->cmd_place);
	}
}

void	print_error(char *msg)
{
	int		len;

	write(STDERR_FILENO, "Error: ", 7);
	if (errno == 0)
	{
		len = ft_strlen(msg);
		write(STDERR_FILENO, msg, len);
		write(STDERR_FILENO, "\n", 1);
	}
	else
		perror(msg);
}

void	clean_exit(t_pipex *pipex, char *msg)
{
	print_error(msg);
	close_files(pipex);
	close_pipe(pipex);
	clean_memory(pipex);
	exit(1);
}
