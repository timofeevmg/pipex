/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:43:38 by epilar            #+#    #+#             */
/*   Updated: 2022/04/28 12:43:59 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_inputfile(char *path)
{
	int	ret;
	int	fd;
	char	buf[8];

	ret = access(path, F_OK | R_OK);
	if (ret < 0)
		return ret;
	fd = open(path, O_RDONLY);
	ret = read(fd, buf, 1);
	if (ret < 0)
		return ret;
	return fd;
}

int create_outputfile(char *path)
{
	int	ret;
	int	fd;

	ret = access(path, F_OK);
	if (ret == 0)
	{
		ret = access(path, W_OK);
		if (ret < 0)
			return ret;
	}
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return fd;
}
