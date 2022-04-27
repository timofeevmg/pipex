/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:45:02 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 14:40:42 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	print_error(char *msg)
{
	int		len;

	write(STDERR_FILENO, "Error: ", 7);
	if (errno == 0)
	{
		len = ft_strlen(WRONG_ARG_NUM);
		write(STDERR_FILENO, WRONG_ARG_NUM, len);
	}
	else
		perror(msg);
}