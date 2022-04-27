/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:17:07 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 14:17:10 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	if (src == NULL)
		return (0);
	while (src[count] != '\0')
		count++;
	i = 0;
	if (size)
	{
		while (i < size - 1)
		{
			if (src[i] == '\0')
				break ;
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (count);
}
