/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:53:55 by epilar            #+#    #+#             */
/*   Updated: 2022/05/23 15:00:30 by epilar           ###   ########.fr       */
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

void	clean_exit(t_pipex *pipex, char *msg)
{
	int	i;

	print_error(msg);
	if (pipex)
	{
		if (pipex->filelst & INFD)
			close(pipex->infile);
		if (pipex->filelst & HDFD)
			unlink(HEREDOC_FILE);
		if (pipex->filelst & OUTFD)
			close(pipex->outfile);
		if (pipex->cmd_paths)
		{
			i = 0;
			while (pipex->cmd_paths[i])
				free(pipex->cmd_paths[i++]);
			free(pipex->cmd_paths);
		}
		if (pipex->pipe_fds)
		{
			i = 0;
			while(pipex->pipe_fds[i])
			{
				close(pipex->pipe_fds[i][0]);
				close(pipex->pipe_fds[i][1]);
				free(pipex->pipe_fds[i++]);
			}
			free(pipex->pipe_fds);
		}
	}
	exit(1);
}
