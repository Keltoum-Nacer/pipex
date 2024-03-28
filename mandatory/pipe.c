/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:50:32 by knacer            #+#    #+#             */
/*   Updated: 2024/03/28 12:27:57 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handling_error(char **av)
{
	if (access(*av, F_OK) == -1)
	{
		write(1, "bash: ", 6);
		perror(*av);
		exit(1);
	}
}

void	handling_command(char **av)
{
	if (!ft_strcmp(*av, "") || !ft_strcmp(*av, " "))
	{
		write(1, "bash: ", 6);
		ft_putstr_fd(*av, 1);
		ft_putstr_fd(": command not found\n", 1);
		exit(127);
	}
}

void	child2_process(char **av, char **env, t_pipex *pipex)
{
	pipex->p_child2 = fork();
	if (pipex->p_child2 == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pipex->p_child2 == 0)
	{
		handling_error(&av[4]);
		if (access(av[4], W_OK) == -1)
		{
			write(1, "bash: ", 6);
			perror(av[4]);
			exit(1);
		}
		handling_command(&av[3]);
		dup2(pipex->file2, STDOUT_FILENO);
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[1]);
		close(pipex->file2);
		close(pipex->fd[0]);
		execute_cmd(av[3], env);
	}
}

void	child1_process(char **av, char **env, t_pipex *pipex)
{
	pipex->p_child1 = fork();
	if (pipex->p_child1 == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pipex->p_child1 == 0)
	{
		handling_error(&av[1]);
		if (access(av[1], R_OK) == -1)
		{
			write(1, "bash: ", 6);
			perror(av[1]);
			exit(1);
		}
		handling_command(&av[2]);
		dup2(pipex->file1, STDIN_FILENO);
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->file1);
		close(pipex->fd[1]);
		execute_cmd(av[2], env);
	}
	else
		child2_process(av, env, pipex);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
