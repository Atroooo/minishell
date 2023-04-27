/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:58:47 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/27 15:49:43 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static char	*check_in_env(char *name, t_env_main *main_env)
{
	while (main_env->env_list != NULL)
	{
		if (ft_strcmp(name, main_env->env_list->name) == 0)
		{
			if (main_env->env_list->value \
				&& main_env->env_list->value[0] == '\0')
			{
				printf("minishell: cd: %s not set\n", name);
				return (NULL);
			}
			return (ft_strdup(main_env->env_list->value));
		}
		main_env->env_list = main_env->env_list->next;
	}
	return (NULL);
}

static char	*get_path_cd(char **cmd, t_env_main *main_env)
{
	char	*path;

	if (cmd[1] == NULL || (cmd[1][0] == '~' && cmd[1][1] == '\0') \
	|| (cmd[1][0] == '-' && cmd[1][1] == '-' && cmd[1][2] == '\0'))
		path = check_in_env("HOME", main_env);
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		path = check_in_env("OLDPWD", main_env);
	else if (cmd[1][0] == '-')
	{
		printf("minishell: cd: %s invalid option\n", &cmd[1][1]);
		return (NULL);
	}
	else if (cmd[2] != NULL)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (NULL);
	}
	else
		path = ft_strdup(cmd[1]);
	if (path == NULL)
	{
		main_env->exit_status = 1;
		return (NULL);
	}
	return (path);
}

void	ft_cd(char **cmd, t_env_main *main_env)
{
	char	*path;

	path = get_path_cd(cmd, main_env);
	if (path == NULL)
		return ;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		main_env->exit_status = 1;
		free(path);
		return ;
	}
	free(path);
	main_env->exit_status = 0;
}
