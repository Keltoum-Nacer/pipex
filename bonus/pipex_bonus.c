/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:47:01 by knacer            #+#    #+#             */
/*   Updated: 2024/03/28 18:12:48 by knacer           ###   ########.fr       */
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
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path = ft_substr(env[i], 5, 62);
			break ;
		}
		i++;
	}
	return (path);
}

void	check_patth(char *av, char *path)
{
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

char	*check_buffer(char *av, char **buffer)
{
	char	*exec;
	char	*cmd;
	int		i;

	i = 0;
	cmd = ft_strjoinn("/", av);
	while(buffer[i] != NULL)
	{
		exec = ft_strjoinn(buffer[i], cmd);
		if (access(exec, X_OK) == 0)
			break;
		free(exec);
		i++;
	}
	if (buffer[i] == NULL && access(exec, X_OK) == -1)
	{
		free_arr(buffer);
		write(2, "bash: ", 6);
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return(exec);
}

char	*find_path(char *av, char **env)
{
	char	*path;
	char	**buffer;
	char	*exec;
	
	if (access(av, X_OK) == 0)
		return (av);
	path = check_path(env);
	check_patth(av, path);
	buffer = ft_split(path, ':');
	free(path);
	exec = check_buffer(av, buffer);
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
