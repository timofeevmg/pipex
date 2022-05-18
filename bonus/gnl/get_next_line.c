/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:03:59 by epilar            #+#    #+#             */
/*   Updated: 2022/05/18 15:05:14 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_line(char *str)
{
	int		i;
	char	*ret;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	ret[i] = '\0';
	i--;
	while (i >= 0)
	{
		ret[i] = str[i];
		i--;
	}
	return (ret);
}

char	*cut_accum(char *accum)
{
	char	*new;
	int		i;
	int		j;

	if (!accum)
		return (NULL);
	i = 0;
	while (accum[i] && accum[i] != '\n')
		i++;
	if (!accum[i])
	{
		free(accum);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(accum) - i + 1));
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (accum[i])
		new[j++] = accum[i++];
	new[j] = '\0';
	free(accum);
	return (new);
}

int	error_ret(char *buf)
{
	if (buf)
		free(buf);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	int			rd;
	static char	*accum;

	rd = 1;
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (!ft_strchr(accum, '\n') && rd != 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (error_ret(buf));
		buf[rd] = '\0';
		accum = ft_strjoin(accum, buf);
	}
	free(buf);
	*line = find_line(accum);
	accum = cut_accum(accum);
	if (rd == 0)
		return (0);
	return (1);
}
