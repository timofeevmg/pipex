/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:45:19 by epilar            #+#    #+#             */
/*   Updated: 2022/05/18 14:09:55 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		check_heredoc(char *arg)
{
	if (arg && ft_strncmp("here_doc", arg, 9) == 0)
		return (1);
	return (0);
}

void	prepare_struct(t_pipex *pipex, char **av)
{
	pipex->openedfds = NOFDS;
	pipex->isheredoc = check_heredoc(av[1]);
}

int		count_commands(int ac, t_pipex *pipex)
{
	if (ac < 5 || (ac < 6 && pipex->isheredoc))
		return (-1);
	pipex->cmd_num = ac - 3 - pipex->isheredoc;
	return (0);
}

void	create_heredoc(char *limiter)
{
	
}

int		open_inputfile(char **av, t_pipex *pipex)
{
	char	*input;
	int		ret;
	int		fd;

	if (pipex->isheredoc)
	{
		create_heredoc(av[2]);
		input = ft_strdup(HEREDOC_FILE);
	}
	else
		input = ft_strdup(av[1]);
	ret = access(input, F_OK | R_OK);
	if (ret < 0)
	{
		free(input);
		return (ret);
	}
	fd = open(input, O_RDONLY);
	ret = read(fd, NULL, 0);
	if (ret < 0)
	{
		free(input);
		return (ret);
	}
	free(input);
	return (fd);
}

int	create_outputfile(char *path)
{
	int	ret;
	int	fd;

	ret = access(path, F_OK);
	if (ret == 0)
	{
		ret = access(path, W_OK);
		if (ret < 0)
			return (ret);
	}
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

void	open_inoutfiles(int ac, char **av, t_pipex *pipex)
{
	pipex->infile = open_inputfile(av, pipex);
	if (pipex->infile < 0)
	{
		perror(OPEN_INFILE);
		exit(1);
	}
	pipex->outfile = create_outputfile(av[ac - 1]);
	if (pipex->outfile < 0)
	{
		perror(CREAT_OUTFILE);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex		pipex;

	if (!av || !env)
	{
		perror(WRONG_ARGS);
		exit(1);
	}
	prepare_struct(&pipex, av);
	if (count_commands(ac, &pipex) < 0)
	{
		perror(WRONG_ARGS_NUM);
		exit(1);
	}
	open_inoutfiles(ac, av, &pipex);
	printf("%d\n", pipex.cmd_num);
	return (0);
}