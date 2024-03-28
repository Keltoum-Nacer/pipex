/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:35:08 by knacer            #+#    #+#             */
/*   Updated: 2024/03/26 22:59:41 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac == 5)
	{
		pipex.file1 = open(av[1], O_RDONLY);
		pipex.file2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (pipe(pipex.fd) == -1)
		{
			perror("pipe failed");
			exit(1);
		}
		child1_process(av, env, &pipex);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		waitpid(pipex.p_child1, NULL, 0);
		waitpid(pipex.p_child2, NULL, 0);
	}
	else
	{
		ft_putstr_fd(ft_strjoin("error,you have to put five arguments :",
				"./pipex <file1> <cmd1> <cmd2> <file2>"), 1);
	}
}
