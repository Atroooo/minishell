/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:54:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/09 10:57:07 by vgonnot          ###   ########.fr       */
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
	char	*flag;
	char	**content;
	char	separator;
}t_cmd;

typedef struct t_line
{
	t_cmd	*cmd;
	char	*infile;
	char	*outfile;
}t_line;

void	parsing(char *line, t_line *all_cmd);
void	split_line(char *line, t_line *all_cmd);
int		input_operator_check(char *cmd);

#endif