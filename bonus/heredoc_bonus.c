/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:06:01 by knacer            #+#    #+#             */
/*   Updated: 2024/03/28 15:22:28 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_limiter(t_pipe *pipex, char **av)
{
	char	*line;
	char	*delimiter;

	delimiter = ft_strjoinn(*av, "\n");
	write(0, "> ", 2);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			free(delimiter);
			exit(0);
		}
		else
		{
			write(pipex->fd[1], line, ft_strlen(line));
			free(line);
			write(0, "> ", 2);
			line = get_next_line(0);
		}
	}
}

void	parent(t_pipe *pipex)
{
	wait(NULL);
	dup2(pipex->fd[0], STDIN_FILENO);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
}

void	here_doc(char **av, t_pipe *pipex, char **env)
{
	if (pipe(pipex->fd) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	pipex->p_child1 = fork();
	if (pipex->p_child1 == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pipex->p_child1 == 0)
	{
		if (pipex->j == 2)
			check_limiter(pipex, &av[2]);
		check_command(&av[pipex->j]);
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		execute_cmd(av[pipex->j], env);
	}
	else
		parent(pipex);
}

void	redirect_output(t_pipe *pipex, char **av, char **env)
{
	wait(NULL);
	check_outfile(&av[pipex->i + 1]);
	check_command(&av[pipex->i]);
	dup2(pipex->file, STDOUT_FILENO);
	dup2(pipex->fd[0], STDIN_FILENO);
	close(pipex->file);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	execute_cmd(av[pipex->i], env);
}

void	check_heredoc(t_pipe *pipex, char **av, char **env)
{
	pipex->j = 2;
	pipex->file = open(av[pipex->i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
	while (pipex->j < pipex->i)
	{
		here_doc(av, pipex, env);
		pipex->j++;
	}
	redirect_output(pipex, av, env);
}
