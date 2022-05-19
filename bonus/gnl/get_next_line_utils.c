/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:04:47 by epilar            #+#    #+#             */
/*   Updated: 2022/05/19 11:16:15 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i] != '\0')
		{
			if (str[i] == (unsigned char)c)
				return ((char *)&str[i]);
			i++;
		}
		if (str[i] == '\0' && c == '\0')
			return ((char *)str + i);
	}
	return (NULL);
}

char	*ft_strjn(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	i = -1;
	j = -1;
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	if (s1)
		while (s1[++i])
			s[i] = s1[i];
	else
		i = 0;
	if (s2)
		while (s2[++j])
			s[i + j] = s2[j];
	else
		j = 0;
	s[i + j] = '\0';
	if (s1)
		free(s1);
	return (s);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (*str != '\0')
		{
			i++;
			str++;
		}
	}
	return (i);
}
