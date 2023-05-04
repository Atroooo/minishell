/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:58:47 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/04 13:16:19 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static char	*check_in_env(char *name, t_env_var *env_list)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(name, env_list->name) == 0)
		{
			if (env_list->value \
				&& env_list->value[0] == '\0')
			{
				printf("minishell: cd: %s not set\n", name);
				return (NULL);
			}
			return (ft_strdup(env_list->value));
		}
		env_list = env_list->next;
	}
	return (NULL);
}

static char	*get_path_cd(char **cmd, t_env_var *env_list)
{
	char	*path;

	if (cmd[1] == NULL || (cmd[1][0] == '~' && cmd[1][1] == '\0') \
	|| (cmd[1][0] == '-' && cmd[1][1] == '-' && cmd[1][2] == '\0'))
		path = check_in_env("HOME", env_list);
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		path = check_in_env("OLDPWD", env_list);
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
		g_status = 1;
		return (NULL);
	}
	return (path);
}

static char	*get_oldpwd(void)
{
	char		cwd[4096];
	char		*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	if (cwd[0] == '\0')
		return (NULL);
	oldpwd = ft_strdup(cwd);
	if (oldpwd == NULL)
		return (NULL);
	return (oldpwd);
}

static void	*manage_error(char *path, char *oldpwd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	g_status = 1;
	free(oldpwd);
	free(path);
	return (NULL);
}

t_env_var	*ft_cd(char **cmd, t_env_var *env_list)
{
	char	*path;
	char	*oldpwd;

	path = get_path_cd(cmd, env_list);
	if (path == NULL)
		return (env_list);
	oldpwd = NULL;
	oldpwd = get_oldpwd();
	if (oldpwd == NULL)
	{
		free (path);
		return (env_list);
	}
	if (chdir(path) == -1)
		return (manage_error(path, oldpwd));
	else
		env_list = change_pwd(path, oldpwd, env_list);
	g_status = 0;
	return (env_list);
}
