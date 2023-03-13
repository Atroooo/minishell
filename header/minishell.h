/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:54:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/13 13:21:27 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/header/libft.h"

typedef struct t_cmd
{
	char	*cmd;
	char	**flag;
	char	**content;
	char	separator;
}t_cmd;

typedef struct t_line
{
	t_cmd	*cmd;
	char	*infile;
	char	*outfile;
	int		nbr_cmd;
}t_line;

void	parsing(char *line, t_line *all_cmd);
void	split_line(char *line, t_line *all_cmd);
int		input_operator_check(char *cmd);
int		get_cmd(char *line, t_cmd *cmd);
int		get_flag(char *line, t_cmd *cmd);
int		get_content(char *line, t_cmd *cmd);
int		skip_space(char *line);
int		count_len(char *line);

#endif