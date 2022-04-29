/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:39 by epilar            #+#    #+#             */
/*   Updated: 2022/04/29 11:44:41 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_pathstr_from_env(char **env)
{
	int	j;
	char	*path_str;
	char	*tmp;

	path_str = NULL;
	tmp = NULL;
	j = 0;
	while(env[j])
	{
		tmp = ft_strnstr(env[j], "PATH=", 5);
		if (tmp)
		{
			path_str = ft_strdup(tmp);
			return path_str;
		}
		++j;
	}
	return NULL;
}

char	*cut_pathstr(char *str)
{
	int	len;
	char	*new;
	int i;

	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len - 5 + 1));
	if (!new)
		return NULL;
	i = 0;
	while(str[5 + i])
	{
		new[i] = str[5 + i];
		++i;
	}
	new[i] = '\0';
	free(str);
	return new;
}

char	**get_paths_arr(char **env)
{
	char	*paths_str;
	char	**paths_arr;

	paths_str = get_pathstr_from_env(env);
	if (!paths_str)
		return NULL;
	paths_str = cut_pathstr(paths_str);
	if (!paths_str)
		return NULL;
	paths_arr = ft_split(paths_str, ':');
	free(paths_str);
	return paths_arr;
}
