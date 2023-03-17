/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:54:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/17 14:43:36 by atro             ###   ########.fr       */
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
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/header/libft.h"

typedef struct s_env_main
{
	char				*line;
	char				**cmd_line;
	char				**env;
	int					last_cmd_status;
	struct s_env_var	*env_list;
	struct termios		*tty;
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
void		init_main_env(t_env_main *main_env, char **env);

/*Parsing*/
void		parsing(char *line, char *env[], t_env_main *main_env);

/*Signal*/
void		signal_handler(t_env_main *env_main);
void		termios_init(t_env_main *main_env);

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

typedef struct t_lst
{
	char			*data;
	struct t_lst	*next;
}	t_lst;

typedef struct t_cmd
{
	char	*cmd;
	t_lst	*flag;
	t_lst	*content;
	t_lst	*infile;
	t_lst	*outfile;
}t_cmd;

typedef struct t_line
{
	t_cmd	*cmd;
	char	***all_cmd;
	int		nbr_cmd;
}t_line;

typedef enum t_boolean
{
	FALSE = 0,
	TRUE
}t_boolean;

void	split_line(char *line, t_line *all_cmd);
int		input_operator_check(char *cmd);
int		get_cmd(char *line, int *command, t_cmd *cmd);
int		get_file(char *line, t_cmd *cmd);
int		get_flag(char *line, t_cmd *cmd);
int		get_content(char *line, t_cmd *cmd);
char	*copy_cmd(int size, char *src, char *dest);
int		skip_space(char *line);
int		count_len(char *line, char del, int *nbr_quote);
int		get_size(char *line, int *size);
void	lst_add_back(t_lst **lst, t_lst *new);
t_lst	*lst_new(void *content);
void	print_cmd(int i, t_line all_cmd);
void	convert_in_3d_array(t_line *all_cmd);

#endif