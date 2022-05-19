/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:53:55 by epilar            #+#    #+#             */
/*   Updated: 2022/05/19 12:54:19 by epilar           ###   ########.fr       */
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
	print_error(msg);
	if (pipex->filelst & INFD)
		close(pipex->infile);
	if (pipex->filelst & HDFD)
		unlink(HEREDOC_FILE);
	if (pipex->filelst & OUTFD)
		close(pipex->outfile);

	exit(1);
}
