/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:54:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/16 07:39:24 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/header/libft.h"


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
	int		nbr_cmd;
}t_line;

typedef enum t_boolean
{
	FALSE = 0,
	TRUE
}t_boolean;

void	parsing(char *line, t_line *all_cmd);
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

#endif