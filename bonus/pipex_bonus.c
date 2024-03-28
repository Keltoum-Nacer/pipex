/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:47:01 by knacer            #+#    #+#             */
/*   Updated: 2024/03/26 23:10:57 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*check_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (!ft_strcmp(env[i], ft_strjoinn("PATH=/usr/local/bin:/usr/bin:/bin:",
					"/usr/sbin:/sbin:/usr/local/munki")))
		{
			path = ft_substr(env[i], 5, 62);
			break ;
		}
		i++;
	}
	return (path);
}

void	check_patth(char *av, char **env)
{
	char	*path;

	path = check_path(env);
	if (!path)
	{
		free(path);
		write(2, "bash: ", 6);
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	if (!ft_strncmp(av, "/", 1))
	{
		write(2, "bash: ", 6);
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

void	check_cmd(char *av)
{
	write(2, "bash: ", 6);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

char	*find_path(char *av, char **env)
{
	char	*path;
	char	**buffer;
	char	*exec;
	int		i;

	i = 0;
	if (access(av, X_OK) == 0)
		return (av);
	path = check_path(env);
	check_patth(av, env);
	buffer = ft_split(path, ':');
	while (buffer[i] != NULL)
	{
		exec = ft_strjoinn(buffer[i], ft_strjoinn("/", av));
		if (access(exec, X_OK) == 0)
			break ;
		free(exec);
		i++;
	}
	if (buffer[i] == NULL && access(exec, X_OK) == -1)
	{
		free_arr(buffer);
		check_cmd(av);
	}
	return (exec);
}

void	execute_cmd(char *av, char **env)
{
	char	**ag;
	char	*path;

	ag = ft_split(av, ' ');
	path = find_path(ag[0], env);
	if (!path)
		free_arr(ag);
	execve(path, ag, env);
	perror("execve failure");
}
