/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:48:02 by epilar            #+#    #+#             */
/*   Updated: 2022/05/19 12:49:48 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	create_heredoc(t_pipex *pipex, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(HEREDOC_FILE, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		clean_exit(pipex, CREAT_HEREDOC);
	pipex->filelst |= HDFD;
	while (1)
	{
		write(1, "> ", 2);
		if (get_next_line(0, &line) < 0)
		{
			close(fd);
			clean_exit(pipex, READ_STDIN);
		}
		if (ft_strcmp(limiter, line) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}
