/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:29:42 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/15 14:26:53 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <unistd.h>
# include <sys/stat.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "../libft/header/libft.h"

typedef struct s_env_main
{
	char				**env;
	int					to_execute;
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
	int		input;
	int		output;
	int		infile;
	int		outfile;
	int		nbr_cmd;
	int		actual_pipe;
	int		hdoc;
	int		*pid;
	int		**fd;
	int		i;
	int		error_msg;
	char	*delimiter;
	char	*tmp_str;
}	t_env_pipe;

typedef struct t_lst
{
	char			*data;
	int				index;
	int				idx_line;
	struct t_lst	*next;
}	t_lst;

typedef struct t_cmd
{
	char	*cmd;
	t_lst	*flag;
	t_lst	*content;
	t_lst	*infile;
	t_lst	*outfile;
}	t_cmd;

typedef struct t_line
{
	t_cmd	*cmd;
	char	***all_cmd;
	int		nbr_cmd;
	t_lst	*infile;
	t_lst	*outfile;
}	t_line;

typedef enum t_boolean
{
	FALSE = 0,
	TRUE
}	t_boolean;

extern unsigned char	g_status;

/*Init*/
void		init_main_env(t_env_main *main_env, char **env);

/*Parsing*/
int			parsing(char *line, t_line *all_cmd, t_env_main *main_env);
int			split_line(char *line, t_line *all_cmd);
int			input_operator_check(char *cmd);
char		*check_if_pipe_error(char *line, t_env_main *main_env, int *error);
void		skip_gobal_variable(int *index, char *line);
char		*replace_global_variable(char *line, t_env_main *main_env);
char		**split_skip_quote(char *str);
int			check_if_not_special_case(char *line, int *i_line, \
			char *final_line);
void		incrementation(int *index, int *nbr_char, char c);
char		*copy_cmd(int size, char *src, char *dest);
int			get_element(int *i, \
			int (*get)(char *, t_cmd *), char *line, t_cmd *cmd);
int			get_gbl_var(char *line, char *final_line, \
						int *i_line, t_env_main *main_env);

/*Builtins Parsing*/
int			check_if_echo(char *line, t_cmd *cmd, int *error);

/*Get all cmd*/
int			get_cmd(char *line, t_cmd *cmd);
int			get_file(char *line, t_cmd *cmd, int index);
int			get_element_file(int *i, char *line, t_cmd *cmd, int index);
int			get_flag(char *line, t_cmd *cmd);
int			get_content(char *line, t_cmd *cmd);

/*Utils Parsing*/
int			skip_space(char *line);
int			count_len(char *line, char del, int *nbr_quote);
int			get_size(char *line, int *size);
void		print_cmd(int i, t_line all_cmd);
int			convert_in_3d_array(t_line *all_cmd);
void		free_cmd_struct(t_line *all_cmd);
int			count_nbr_char(char *line, t_env_var *env_list);
void		skip_simple_quote(int *index, int *nbr_char, char *line);
int			count_alpha(char *line);
int			skip_char(char *line, char c);
int			skip_in_between(char *str, char c);
void		free_single_cmd(t_cmd *cmd);
int			not_between_quote(char *line, int i_line);
int			check_if_need_to_skip_global_variable( \
			char *line, int *i_line);
int			copy_all_arg(char **arg, t_cmd *cmd);
int			list_copy(t_lst **dest, t_lst *src, int index, int idx_line);
int			simple_operator_error(char *line);
int			operator_with_pipe(char *line);
int			check_if_pipe(char *line, int *consecutive_pipe, int *quote);
int			check_char(char c, int *pipe, int *consecutive_pipe, \
					int *only_space);
int			first_error_case(int consecutive_pipe, int only_space, int quote);
int			var_init(int *quote, int *consecutive_pipe, int *only_space, \
						int *i);
int			check_if_quote_increment(char c, int *quote);
int			count_split(char **line);
int			get_element(int *i, \
			int (*get)(char *, t_cmd *), char *line, t_cmd *cmd);
int			initialize_variable( \
			t_cmd *cmd, int *error, int *no_command, int *is_echo);
int			check_if_get_cmd(char c, int *no_command, int error);
t_env_var	*ft_lst_addsort(t_env_var *env_list, t_env_var *new_var);
t_env_var	*delete_node(t_env_var *env_list, int i);
t_env_var	*get_prev(t_env_var *env_list, int i);

/*List utils*/
int			lst_add_back(t_lst **lst, t_lst *new);
t_lst		*lst_new(void *content);
t_lst		*lst_new_index(void *content, int index);
t_lst		*lst_new_double_index(void *content, int index, int idx_line);

/*Signal*/
void		signal_handler(void);
void		activate_sig(void);
void		desactivate_sig(void);
void		termios_init(t_env_main *main_env);
void		reset_terminal(t_env_main *main_env);

/*Manage files*/
int			open_files(t_env_pipe *st, t_line *all_cmd);
int			check_infile(t_line *all_cmd);
int			check_spe_infile(t_env_pipe *st, t_line *all_cmd);
int			setup_spe_infile(t_env_pipe *st, t_line *all_cmd);
int			setup_infile(t_env_pipe *st, char *file_raw);
int			check_file_status_redir(char *file_name);
int			check_file_status_exec(char *file_name, t_env_pipe *st, \
				t_line *all_cmd);
int			create_outfiles(t_line *all_cmd);
int			open_outfile(t_env_pipe *st, t_line *all_cmd);
int			check_spe_outfile(t_env_pipe *st, t_line *all_cmd);
int			setup_outfile(t_env_pipe *st, char *file_raw, t_line *all_cmd);
int			dup_manager(t_env_pipe *st, t_line *all_cmd);
int			get_dup_single_done(t_env_pipe *st);
void		close_function(t_env_pipe *st);

/*Execution*/
int			is_executable(char **cmd);
int			env_lst_to_char(t_env_main *main_env);
void		exec_hub(t_line *all_cmd, t_env_main *main_env);
int			setup_struct_cmd(t_env_pipe *st, t_line *all_cmd, \
				t_env_main *main_env);
int			find_path_index(char **env);
char		*return_path(char **env, char **cmd, t_env_pipe *st);
int			execution(t_line *all_cmd, t_env_pipe *st, t_env_main *main_env);
int			get_exec_done(t_line *all_cmd, char **cmd, \
				t_env_pipe *st, t_env_main *main_env);
int			error_execve(char **cmd, char *path, t_env_pipe *st);

/*Heredoc*/
int			check_hdoc(t_line *all_cmd);
int			heredoc(t_env_pipe *st, t_line *all_cmd, t_env_main *main_env);
char		*get_delimiter(char *str);
char		*get_delimiter_hdoc(t_line *all_cmd, int count);
int			get_nbr_hdoc(t_line *all_cmd);

/*Builtins*/
void		ft_echo(char **cmd, t_env_pipe *st);
t_env_var	*ft_cd(char **cmd, t_env_var *env_list);
t_env_var	*change_pwd(char *pwd, char *oldpwd, t_env_var *env_list);
void		ft_pwd(char **cmd, t_env_pipe *st);
t_env_var	*ft_export(char **cmd, t_env_main *main_env);
int			check_if_in_env(t_env_var *lst, char *str);
void		free_variable_name_and_value(char *name, char *value);
int			set_variables_name_and_value(char *str, char **name, char **value);
t_env_var	*ft_unset(char **cmd, t_env_var *env_list);
int			check_unset_error(char *cmd);
char		**ft_env(char **cmd, t_env_main *main_env);
void		ft_exit(char **cmd, t_env_main *main_env, t_line *all_cmd);
t_env_var	*remove_similar_variable(char *name, t_env_var *lst);

/*Utils*/
int			cmd_size(char **cmd);
int			get_total_cmd(t_line *all_cmd);
char		*setup_file(char *raw_file);
t_env_var	*ft_lstnew_env(char *name, char *value);
void		ft_lstadd_front_env(t_env_var **lst, t_env_var *new);
int			ft_lst_addback_env(t_env_var **lst, t_env_var *new);
int			ft_lstsize_env(t_env_var *lst);
t_lst		*lst_last(t_lst *lst);
int			ft_lstsize_file(t_lst *lst);
void		print_unset_error(char *cmd, int s);

/*Free utils*/
void		free_str(char **str);
void		free_cmd(t_line *all_cmd);
void		free_main_env(t_env_main *main_env);
void		free_inout_list(t_lst *lst);
void		free_env(t_env_pipe *st, int i);
void		free_pipe(t_env_pipe *st);
int			quit_function(t_env_pipe *st, int error_code);
void		free_cmd_exec(t_line *all_cmd, t_env_pipe *st, \
				t_env_main *main_env);

#endif