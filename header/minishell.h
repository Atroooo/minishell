/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:54:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 11:21:55 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/header/libft.h"

void	parsing(char *line);

/*Signal*/
void    signal_handler(void);

/*Redirect*/
void	redirect_input(char **cmd);
void	redirect_output(char **cmd);
void	redirect_output_append(char **cmd);

/*Builtins*/
void	ft_echo(char **cmd);
void	ft_cd(char **cmd);
void	ft_pwd(char **cmd);

#endif