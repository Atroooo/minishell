/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:12:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/08 11:48:28 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static t_env_var	*change_pwds_lst(t_env_var *list, \
	char *which_pwd, char *path)
{
	t_env_var	*save;

	save = list;
	while (list && ft_strcmp(list->name, which_pwd))
	{
		list = list->next;
	}
	if (list == NULL)
	{
		if (!ft_lst_addback_env(&list, ft_lstnew_env(which_pwd, path)))
			return (free(path), NULL);
		free(path);
	}
	else
	{
		free(list->value);
		list->value = path;
	}
	return (save);
}

static char	*get_final_pwd(char *oldpwd, char *pwd)
{
	char	*temp;
	char	*final_pwd;

	temp = ft_strjoin(oldpwd, "/");
	if (temp == NULL)
		return (NULL);
	final_pwd = ft_strjoin(temp, pwd);
	if (final_pwd == NULL)
		return (NULL);
	free(temp);
	return (final_pwd);
}

t_env_var	*change_pwd(char *pwd, char *oldpwd, t_env_var *env_list)
{
	char	*final_pwd;

	if (pwd[0] == '/')
	{
		final_pwd = ft_strdup(pwd);
		if (final_pwd == NULL)
			return (NULL);
	}
	else
	{
		final_pwd = get_final_pwd(oldpwd, pwd);
		if (final_pwd == NULL)
			return (NULL);
	}
	env_list = change_pwds_lst(env_list, "OLDPWD", oldpwd);
	env_list = change_pwds_lst(env_list, "PWD", final_pwd);
	free(pwd);
	return (env_list);
}
