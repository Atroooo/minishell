/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:17:55 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/01 15:19:10 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static char	*setup_str_env(t_env_var *node)
{
	char		*str_name;
	char		*str;

	if (!node->name)
		return (NULL);
	str_name = ft_strjoin(node->name, "=");
	if (!str_name)
		return (0);
	if (node->value == NULL)
		return (str_name);
	else
		str = ft_strjoin(str_name, node->value);
	if (!str)
		return (0);
	free(str_name);
	return (str);
}

int	env_lst_to_char(t_env_main *main_env)
{
	t_env_var	*tmp;
	int			i;

	main_env->env = malloc(sizeof(char *) * \
		(ft_lstsize_env(main_env->env_list) + 1));
	if (main_env->env == NULL)
		return (0);
	tmp = main_env->env_list;
	i = 0;
	while (tmp)
	{
		main_env->env[i] = setup_str_env(tmp);
		if (!main_env->env[i])
			return (0);
		tmp = tmp->next;
		i++;
	}
	main_env->env[i] = NULL;
	free(tmp);
	return (1);
}