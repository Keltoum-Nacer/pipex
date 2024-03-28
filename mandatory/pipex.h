/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:36 by knacer            #+#    #+#             */
/*   Updated: 2024/03/24 15:14:22 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		file1;
	int		file2;
	int		fd[2];
	pid_t	p_child1;
	pid_t	p_child2;
}			t_pipex;

void		child1_process(char **av, char **env, t_pipex *pipex);
void		child2_process(char **av, char **env, t_pipex *pipex);
void		execute_cmd(char *av, char **env);
int			count_nbsub(char const *s, char c);
int			count_char(const char *s, char c);
char		**free_arr(char **arr);
char		**affect_str(char **arr, int nbsub, char const *s, char c);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
char		*find_path(char *av, char **env);
char		*check_path(char **env);
size_t		ft_strlen(char *str);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		**free_arr(char **arr);
int			ft_strncmp(char *s1, char *s2, size_t n);

#endif