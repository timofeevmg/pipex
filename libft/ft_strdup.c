/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:16:34 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 14:16:35 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;
	int		s;
	int		i;

	s = 0;
	i = 0;
	while (str[s])
		s++;
	dst = (char *)malloc((s + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (i < s)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
