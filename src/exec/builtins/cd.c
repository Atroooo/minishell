/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:58:47 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/01 15:01:41 by vgonnot          ###   ########.fr       */
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

static char	*get_oldpwd(void)
{
	char		cwd[4096];
	char		*oldpwd;

	getcwd(cwd, sizeof(cwd));
	oldpwd = ft_strdup(cwd);
	if (oldpwd == NULL)
		return (NULL);
	return (oldpwd);
}

static t_env_var	*change_pwds(t_env_var *list, char *which_pwd, char *path)
{
	while (list && ft_strcmp(list->name, which_pwd))
	{
		list = list->next;
	}
	if (list == NULL)
	{
		ft_lst_addback_env(&list, ft_lstnew_env(which_pwd, path));
		free(path);
	}
	else
	{
		free(list->value);
		list->value = path;
	}
	return (list);
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

static t_env_var	*change_pwd(char *pwd, char *oldpwd, t_env_main *main_env)
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
	main_env->env_list = change_pwds(main_env->env_list, "OLDPWD", oldpwd);
	main_env->env_list = change_pwds(main_env->env_list, "PWD", final_pwd);
	return (main_env->env_list);
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

t_env_var	*ft_cd(char **cmd, t_env_main *main_env)
{
	char	*path;
	char	*oldpwd;

	path = get_path_cd(cmd, main_env);
	if (path == NULL)
		return (NULL);
	oldpwd = get_oldpwd();
	if (oldpwd == NULL)
	{
		free(path);
		return (NULL);
	}
	if (chdir(path) == -1)
		return (manage_error(path, oldpwd));
	else
		change_pwd(path, oldpwd, main_env);
	free(path);
	main_env->exit_status = 0;
	return (main_env->env_list);
}
