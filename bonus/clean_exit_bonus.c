/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:53:55 by epilar            #+#    #+#             */
/*   Updated: 2022/05/24 10:40:47 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

void	close_pipes(t_pipex *pipex)
{
	int	i;

	if (pipex)
	{	
		i = 0;
		while (i < pipex->pipe_num)
		{
			close(pipex->pipe_fds[i][0]);
			close(pipex->pipe_fds[i][1]);
			i++;
		}
	}
}

void	close_files(t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->filelst & INFD)
			close(pipex->infile);
		if (pipex->filelst & HDFD)
			unlink(HEREDOC_FILE);
		if (pipex->filelst & OUTFD)
			close(pipex->outfile);
	}
}

void	clean_memory(t_pipex *pipex)
{
	int	i;
	
	if (pipex->cmd_paths)
	{
		i = 0;
		while (pipex->cmd_paths[i])
			free(pipex->cmd_paths[i++]);
		free(pipex->cmd_paths);
	}
}

void	clean_exit(t_pipex *pipex, char *msg)
{
	int	i;

	print_error(msg);
	if (pipex)
	{
		close_files(pipex);
		clean_memory(pipex);
		if (pipex->pipe_fds)
		{
			i = 0;
			while(pipex->pipe_fds[i])
			{
				if (i < pipex->pipe_id)
				{
					close(pipex->pipe_fds[i][0]);
					close(pipex->pipe_fds[i][1]);
				}
				free(pipex->pipe_fds[i]);
				i++;
			}
			free(pipex->pipe_fds);
		}
	}
	exit(1);
}
