/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:51:23 by knacer            #+#    #+#             */
/*   Updated: 2024/03/28 17:07:18 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->ac - 4)
	{
		close(pipex->fdd[i][0]);
		close(pipex->fdd[i][1]);
		i++;
	}
}

void	ft_pipe(t_pipe *pipex)
{
	int	i;

	pipex->fdd = ft_malloc((pipex->ac - 4) * sizeof(int *));
	i = 0;
	while (i < pipex->ac - 4)
	{
		pipex->fdd[i] = ft_malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < pipex->ac - 4)
	{
		if (pipe(pipex->fdd[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

void	open_files(t_pipe *pipex, char **av, char **env)
{
	int	i;

	pipex->file1 = open(av[1], O_RDONLY);
	pipex->file2 = open(av[pipex->i + 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_pipe(pipex);
	pipex->arr = ft_malloc(sizeof(int) * (pipex->ac - 3));
	i = 0;
	pipex->j = 2;
	while (pipex->j < pipex->ac - 1)
	{
		pipex->arr[i] = fork();
		if (pipex->arr[i] == -1)
		{
			perror("fork");
			exit(1);
		}
		multiple_pipes(pipex, av, env, i);
		i++;
		pipex->j++;
	}
}

void	ft_wait(t_pipe *pipex, int *status)
{
	int	i;

	ft_close(pipex);
	i = 0;
	while (i < pipex->ac - 3)
	{
		waitpid(pipex->arr[i], status, 0);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int status;

	if (ac >= 5)
	{
		pipex.ac = ac;
		pipex.i = ac - 2;
		if (!ft_strcmp(av[1], "here_doc"))
		{
			if (ac >= 6)
				check_heredoc(&pipex, av, env);
			else
				ft_putstr_fd("error, enter the right parameters ", 1);
		}
		else
		{
			open_files(&pipex, av, env);
			ft_wait(&pipex, &status);
			free(pipex.arr);
			if ( WIFEXITED(status) ) 
        		exit(WEXITSTATUS(status));
		}
	}
	else
		ft_putstr_fd("error, enter the right parameters ", 1);
}
