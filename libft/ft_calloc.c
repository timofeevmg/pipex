/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:12:32 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 14:12:35 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	char	*p;
	size_t	sum;
	int		i;

	i = 0;
	sum = n * s;
	p = (char *)malloc(sum);
	if (p == NULL)
		return (NULL);
	while (sum--)
		p[i++] = 0;
	return ((void *)p);
}
