/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:52:39 by knacer            #+#    #+#             */
/*   Updated: 2024/03/26 21:31:01 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_infile(char **av)
{
	if (access(*av, F_OK) == -1)
	{
		write(1, "bash: ", 6);
		perror(*av);
		exit(1);
	}
	else if (access(*av, R_OK) == -1)
	{
		write(1, "bash: ", 6);
		perror(*av);
		exit(1);
	}
}

void	check_outfile(char **av)
{
	if (access(*av, F_OK) == -1)
	{
		write(1, "bash: ", 6);
		perror(*av);
		exit(1);
	}
	else if (access(*av, W_OK) == -1)
	{
		write(1, "bash: ", 6);
		perror(*av);
		exit(1);
	}
}

void	check_command(char **av)
{
	if (!ft_strcmp(*av, "") || !ft_strncmp(*av, " ", 1))
	{
		write(1, "bash: ", 6);
		ft_putstr_fd(*av, 1);
		ft_putstr_fd(": command not found\n", 1);
		exit(127);
	}
}

void	first_command(t_pipe *pipex, char **av)
{
	check_infile(&av[1]);
	dup2(pipex->file1, STDIN_FILENO);
	close(pipex->file1);
	check_command(&av[pipex->j]);
}

void	multiple_pipes(t_pipe *pipex, char **av, char **env, int i)
{
	if (pipex->arr[i] == 0)
	{
		if (pipex->j == 2)
		{
			first_command(pipex, av);
			dup2(pipex->fdd[i][1], STDOUT_FILENO);
		}
		else if (pipex->j == pipex->i)
		{
			check_outfile(&av[pipex->ac - 1]);
			check_command(&av[pipex->i]);
			dup2(pipex->file2, STDOUT_FILENO);
			close(pipex->file2);
			dup2(pipex->fdd[i - 1][0], STDIN_FILENO);
		}
		else
		{
			dup2(pipex->fdd[i - 1][0], STDIN_FILENO);
			check_command(&av[pipex->j]);
			dup2(pipex->fdd[i][1], STDOUT_FILENO);
		}
		ft_close(pipex);
		execute_cmd(av[pipex->j], env);
	}
}
