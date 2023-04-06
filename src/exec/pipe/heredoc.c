/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:40 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/30 18:14:01 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*Need protect + check si avec un fork pour heredoc mieux*/
int	setup_heredoc(t_env_pipe *st, t_line *all_cmd)
{
	char	*outfile;
	int		temp_pipe[2];

	pipe(temp_pipe);
	st->infile = temp_pipe[0];
	if (st->output == 0)
		st->outfile = 1;
	else
	{
		outfile = setup_file(lst_last(all_cmd->outfile)->data);
		st->outfile = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (st->outfile == -1)
			quit_function(st, 0);
		free(outfile);
	}
	close(temp_pipe[1]);
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

static char	*heredoc_parsing(t_line *all_cmd)
{
	char	*delimiter;
	char	*get_str;

	delimiter = get_delimiter(lst_last(all_cmd->infile)->data);
	get_str = get_next_line(0);
	if (get_str == NULL)
	{
		ft_printf("End of file : the delimiter was %s\n", delimiter);
		return (NULL);
	}
	else if (ft_strcmp(delimiter, get_str) == 0)
	{
		free(delimiter);
		free(get_str);
		return (NULL);
	}
	return (get_str);
}

static char	*ft_strnjoin(char *old_dst, char *src, size_t len)
{
	char	*dst;
	size_t	index;
	size_t	j;

	if (src == NULL)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(old_dst) + ft_strlen(src) + 1));
	if (!dst)
		return (free(old_dst), NULL);
	index = 0;
	j = 0;
	while (old_dst && old_dst[index])
	{
		dst[index] = old_dst[index];
		index++;
	}
	while (src[j] && j < len)
	{
		dst[index] = src[j];
		j++;
		index++;
	}
	dst[index] = '\0';
	return (dst);
}

int	heredoc(t_env_pipe *st, t_line *all_cmd)
{
	char	*str_print;
	char	*tmp_str;

	str_print = NULL;
	if (!all_cmd->infile)
		return (0);
	if (ft_strnstr(lst_last(all_cmd->infile)->data, "<<", 2) == 0)
		return (0);
	st->nbr_cmd = 1;
	while (1)
	{
		ft_printf("heredoc> ");
		tmp_str = heredoc_parsing(all_cmd);
		if (!tmp_str)
			break ;
		else
		{
			str_print = ft_strnjoin(str_print, tmp_str, ft_strlen(tmp_str));
			free(tmp_str);
		}
	}
	write(st->infile, str_print, ft_strlen(str_print));
	free(str_print);
	return (1);
}
