/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:05:44 by epilar            #+#    #+#             */
/*   Updated: 2022/05/04 14:16:05 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipe(int	*pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

void	close_files(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
}

void	clear_pipex(t_pipex *pipex)
{
	int	i;

	close_files(pipex);
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
