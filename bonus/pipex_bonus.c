/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:45:19 by epilar            #+#    #+#             */
/*   Updated: 2022/05/19 12:16:55 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	print_error(char *msg)
{
	int		len;

	write(STDERR_FILENO, "Error: ", 7);
	if (errno == 0)
	{
		len = ft_strlen(msg);
		write(STDERR_FILENO, msg, len);
		write(STDERR_FILENO, "\n", 1);
	}
	else
		perror(msg);
}

void	clean_exit(t_pipex *pipex, char *msg)
{
	print_error(msg);
	if (pipex->filelst & INFD)
		close(pipex->infile);
	if (pipex->filelst & HDFD)
		unlink(HEREDOC_FILE);
	if (pipex->filelst & OUTFD)
		close(pipex->outfile);

	exit(1);
}

int	check_heredoc(char *arg)
{
	if (arg && ft_strncmp("here_doc", arg, 9) == 0)
		return (1);
	return (0);
}

void	prepare_struct(t_pipex *pipex, char **av)
{
	pipex->filelst = NOFDS;
	pipex->isheredoc = check_heredoc(av[1]);
}

int	count_commands(int ac, t_pipex *pipex)
{
	if (ac < 5 || (ac < 6 && pipex->isheredoc))
		return (-1);
	pipex->cmd_num = ac - 3 - pipex->isheredoc;
	return (0);
}

void	create_heredoc(t_pipex *pipex, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(HEREDOC_FILE, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		clean_exit(pipex, CREAT_HEREDOC);
	pipex->filelst |= HDFD;
	while (1)
	{
		write(1, "> ", 2);
		if (get_next_line(0, &line) < 0)
		{
			close(fd);
			clean_exit(pipex, READ_STDIN);
		}
		if (ft_strcmp(limiter, line) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}

int	open_inputfile(char **av, t_pipex *pipex)
{
	char	*input;
	int		ret;
	int		fd;

	if (pipex->isheredoc)
	{
		create_heredoc(pipex, av[2]);
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
		clean_exit(pipex, OPEN_INFILE);
	pipex->outfile = create_outputfile(av[ac - 1]);
	if (pipex->outfile < 0)
		clean_exit(pipex, CREAT_OUTFILE);
	pipex->filelst = NOFDS | INFD | OUTFD;
}

int	main(int ac, char **av, char **env)
{
	t_pipex		pipex;

	if (!av || !env)
		clean_exit(&pipex, WRONG_ARGS);
	prepare_struct(&pipex, av);
	if (count_commands(ac, &pipex) < 0)
		clean_exit(&pipex, WRONG_ARGS_NUM);
	open_inoutfiles(ac, av, &pipex);
	return (0);
}
