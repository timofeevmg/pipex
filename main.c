/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:21:33 by epilar            #+#    #+#             */
/*   Updated: 2022/04/26 14:55:58 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int	main(int ac, char **av, char **env)
{
	int	f_in;
	int	f_out;

	if (ac != 5)
	{
		write(STDERR_FILENO, "Error: count of arguments should be 4.\n", 39);
		exit(1);
	}
	f_in = open(av[1], O_RDONLY);
	if (f_in < 0)
	{
		write(STDERR_FILENO, "Error: could not open input file.\n", 34);
		exit(1);
	}
	f_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f_out < 0)
	{
		write(STDERR_FILENO, "Error: could not create output file.\n", 37);
		exit(1);
	}
	return (0);
}
