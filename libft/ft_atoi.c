/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:11:53 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 14:12:05 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sign_decision(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		sign;
	int		k;

	i = 0;
	res = 0;
	k = 0;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	sign = sign_decision(str[i]);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		k++;
		if (k >= 19 && sign == 1)
			return (-1);
		if (k >= 19 && sign == -1)
			return (0);
	}
	return (res * sign);
}
