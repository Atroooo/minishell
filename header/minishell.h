/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:54:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/10 15:50:53 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/header/libft.h"

typedef struct s_environ{
	char				*name;
    char            	*value;
	struct s_environ	*next;
}	t_environ;

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

/*Parsing*/
void		parsing(char *line, char *env[], t_environ **env_list);

/*Signal*/
void    	signal_handler(void);

/*Redirect*/
void		redirect_input(char **cmd);
void		redirect_output(char **cmd);
void		redirect_output_append(char **cmd);

/*Pipe*/
int		exec_cmd(int argc, char **argv, char *env[]);
int		open_files(int argc, char **argv, t_env *st);
void	dup_manager(t_env *st);
void	set_up_struct(t_env *st, int argc, char **argv);
char	*get_path(char *cmd, char *paths, t_env *st);
void	no_path(t_env *st, char **arg_vec);
void	path_is_null(t_env *st, char **arg_vec, char **argv);
int		heredoc(t_env *st, char **argv);
void	get_exec_done(char **argv, char **env, t_env *st);
void	execution(char **argv, char *env[], t_env *st);
void	error_execve(char **arg_vec, char *path, t_env *st);
void	free_env_exit(t_env *st, int i);
void	free_pipe(t_env *st);
void	close_function(t_env *st);
void	quit_function(t_env *st, int error_code);

/*Builtins*/
void		ft_echo(char **cmd);
void		ft_cd(char **cmd);
void		ft_pwd(char **cmd);
t_environ	*ft_export(char **cmd, t_environ *env_list);
void		ft_unset(char **cmd, t_environ *env_list);
void		ft_env(char **cmd, t_environ *env_list);
void		ft_exit(char **cmd);

/*Utils*/
t_environ	*ft_lstnew_env(char *name, char *value);
void		ft_lstadd_front_env(t_environ **lst, t_environ *new);
void		ft_lst_addback_env(t_environ **lst, t_environ *new);
int			ft_lstsize_env(t_environ *lst);
t_environ	*add_env_value(char *str, t_environ *env_list);

#endif