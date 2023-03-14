/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:54:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/14 22:07:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/header/libft.h"

typedef struct s_env_main
{
	char				*line;
	char				**cmd_line;
	char				**env;
	int					last_cmd_status;
	struct s_env_var	*env_list;
}	t_env_main;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_env_pipe
{
	int	infile;
	int	outfile;
	int	nbr_cmd;
	int	actual_pipe;
	int	hdoc;
	int	*pid;
	int	**fd;
}	t_env_pipe;

/*Init*/
void		init_main_env(t_env_main *main_env);

/*Parsing*/
void		parsing(char *line, char *env[], t_env_main *main_env);

/*Signal*/
void		signal_handler(void);

/*Redirect*/
void		redirect_input(char **cmd);
void		redirect_output(char **cmd);
void		redirect_output_append(char **cmd);

/*Pipe*/
int			exec_cmd(int argc, char **argv, char *env[], t_env_main *main_env);
int			open_files(int argc, char **argv, t_env_pipe *st);
int			dup_manager(t_env_pipe *st);
int			set_up_struct(t_env_pipe *st, int argc, char **argv);
char		*get_path(char *cmd, char *paths, t_env_pipe *st);
void		no_path(t_env_pipe *st, char **arg_vec);
void		path_is_null(t_env_pipe *st, char **arg_vec, char **argv);
int			heredoc(t_env_pipe *st, char **argv);
void		get_exec_done(char **argv, char **env, t_env_pipe *st);
void		execution(char **argv, char *env[], t_env_pipe *st);
int			error_execve(char **arg_vec, char *path, t_env_pipe *st);
void		free_env_exit(t_env_pipe *st, int i);
void		free_pipe(t_env_pipe *st);
void		close_function(t_env_pipe *st);
int			quit_function(t_env_pipe *st, int error_code);

/*Builtins*/
void		ft_echo(char **cmd, t_env_var *env_list, t_env_main *main_env);
void		ft_cd(char **cmd, t_env_main *main_env);
void		ft_pwd(char **cmd, t_env_main *main_env);
t_env_var	*ft_export(char **cmd, t_env_var *env_list, t_env_main *main_env);
t_env_var	*ft_unset(char **cmd, t_env_var *env_list, t_env_main *main_env);
void		ft_env(char **cmd, t_env_var *env_list, t_env_main *main_env);
void		ft_exit(char **cmd);

/*Utils lst*/
t_env_var	*ft_lstnew_env(char *name, char *value);
void		ft_lstadd_front_env(t_env_var **lst, t_env_var *new);
void		ft_lst_addback_env(t_env_var **lst, t_env_var *new);
int			ft_lstsize_env(t_env_var *lst);
t_env_var	*add_env_value(char *str, t_env_var *env_list);

#endif