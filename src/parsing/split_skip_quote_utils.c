/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_skip_quote_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:26:15 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/04 15:30:25 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	skip_in_between(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
	}
	if (str[i] == c)
		i += 1;
	return (i);
}
