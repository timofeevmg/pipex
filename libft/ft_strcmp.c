/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:16:32 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 14:16:38 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;
	int		r;

	i = 0;
	r = 0;
	while (s1[i])
	{
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (r)
			return (r);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
