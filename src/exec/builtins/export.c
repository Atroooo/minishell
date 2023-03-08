/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:32:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/08 16:35:19 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void print_list(t_environ *env_list)
{
    if (!env_list)
        return ;
    while (env_list)
    {
        if (env_list->name && env_list->value)
            printf("%s=%s\n", env_list->name, env_list->value);
        else if (env_list->name && !env_list->value)
            printf("%s=\n", env_list->name);
        env_list = env_list->next;
    }
}

static int	ft_intchr(char *str, char c)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

t_environ	*add_env_value(char *str, t_environ *env_list)
{
    char    *name;
    char    *value;

    name = ft_substr(str, 0, ft_intchr(str, '='));
    value = ft_substr(str, ft_intchr(str, '=') + 1, ft_strlen(str));
    ft_lst_addback_env(&env_list, ft_lstnew_env(name, value));
	free(name);
	free(value);
	return (env_list);
}

t_environ   *ft_export(char **cmd, t_environ *env_list)
{
    int         i;

    if (!cmd)
        return (NULL);
    if (ft_strcmp(cmd[0], "export") != 0)
        return (NULL);
    i = 1;
	if (!cmd[i])
	{
		print_list(env_list);
		return (env_list);
	}
    while (cmd[i])
    {
        if (ft_strchr(cmd[i], '='))
            env_list = add_env_value(cmd[i], env_list);
        else
            setenv(cmd[i], "", 1);
        i++;
    }
    return (env_list);
}