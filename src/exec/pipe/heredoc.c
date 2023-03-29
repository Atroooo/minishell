/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:40 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/29 16:53:15 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*Need protect*/
/*Utiliser des pipes et dup2 pour rediriger l'entrée et 
la sortie standard et ensuite afficher en un seul bloque la cmd*/
int	setup_heredoc(char **argv, t_env_pipe *st)
{
	st->infile = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (st->infile == -1)
	{
		ft_printf("Cannot open file : %s\n", argv[1]);
		free(st);
		return (0);
	}
	if (st->output == 0)
		st->outfile = 1;
	else
	{
		st->outfile = open("outfile", O_RDWR | O_CREAT | O_APPEND, 0644);
		if (st->outfile == -1)
			quit_function(st, 0);
	}
	return (1);
}

static char	*get_delimiter(char *str)
{
	char	*delimiter;

	delimiter = ft_strtrim(str, "< ");
	if (!delimiter)
		return (NULL);
	return (delimiter);
}

static int	heredoc_parsing(char **argv, t_env_pipe *st)
{
	char	*delimiter;
	char	*get_str;

	delimiter = get_delimiter(argv[0]);
	get_str = get_next_line(0);
	if (get_str == NULL)
	{
		ft_printf("End of file : the delimiter was %s\n", delimiter);
		return (1);
	}
	else if (ft_strcmp(delimiter, get_str) == 0)
	{
		free(get_str);
		return (1);
	}
	write(st->infile, get_str, ft_strlen(get_str));
	free(get_str);
	return (0);
}

int	heredoc(t_env_pipe *st, char **argv)
{
	if (ft_strnstr(argv[0], "<<", 2) == 0)
		return (0);
	st->nbr_cmd = 1;
	while (1)
	{
		ft_printf("heredoc> ");
		if (heredoc_parsing(argv, st) == 1)
			break ;
	}
	close(st->infile);
	st->infile = open("heredoc", O_RDWR);
	return (1);
}
