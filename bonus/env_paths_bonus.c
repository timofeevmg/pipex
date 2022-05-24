/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_paths_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:39 by epilar            #+#    #+#             */
/*   Updated: 2022/05/24 10:43:05 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

char	*find_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*try;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!try)
			return (NULL);
		if (access(try, F_OK | X_OK) == 0)
			return (try);
		free(try);
		paths++;
	}
	return (NULL);
}
