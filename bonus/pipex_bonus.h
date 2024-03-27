/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:51:46 by knacer            #+#    #+#             */
/*   Updated: 2024/03/26 15:08:11 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line_bonus.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		file;
	int		file1;
	int		file2;
	int		fd[2];
	int		j;
	int		i;
	int		ac;
	int		**fdd;
	int		*arr;
	pid_t	p_child1;
}			t_pipe;

void		here_doc(char **av, t_pipe *pipex, char **env);
void		multiple_pipes(t_pipe *pipex, char **av, char **env, int i);
void		parent(t_pipe *pipex);
void		execute_cmd(char *av, char **env);
char		**ft_split(char const *s, char c);
void		check_outfile(char **av);
void		check_command(char **av);
char		**free_arr(char **arr);
char		*ft_strjoinn(char *s1, char *s2);
int			ft_strcmp(char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		ft_close(t_pipe *pipex);
void		check_heredoc(t_pipe *pipex, char **av, char **env);
void		redirect_output(t_pipe *pipex, char **av, char **env);
#endif
