/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:39 by epilar            #+#    #+#             */
/*   Updated: 2022/05/16 12:12:25 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_pathstr_from_env(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

char	**get_paths_arr(char **env)
{
	char	*paths_str;
	char	**paths_arr;

	paths_str = get_pathstr_from_env(env);
	if (!paths_str)
		return (NULL);
	paths_arr = ft_split(paths_str, ':');
	return (paths_arr);
}
