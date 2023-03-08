/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:04:01 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 11:01:28 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/header/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct t_env
{
	int	infile;
	int	outfile;
	int	nbr_cmd;
	int	actual_pipe;
	int	hdoc;
	int	*pid;
	int	**fd;
}	t_env;

void	get_exec_done(char **argv, char **env, t_env *st);
void	quit_function(t_env *st, int error_code);
void	set_up_struct(t_env *st, int argc, char **argv);
void	free_pipe(t_env *st);
void	close_function(t_env *st);
int		heredoc(t_env *st, char **argv);
void	set_up_struct(t_env *st, int argc, char **argv);
void	error_execve(char **arg_vec, char *path, t_env *st);
void	free_env_exit(t_env *st, int i);
void	path_is_null(t_env *st, char **arg_vec, char **argv);
void	no_path(t_env *st, char **arg_vec);
void	open_files(int argc, char **argv, t_env *st);
void	close_function(t_env *st);
void	execution(char **argv, char *env[], t_env *st);
void	dup_manager(t_env *st);
char	*get_path(char *cmd, char *paths, t_env *st);

#endif