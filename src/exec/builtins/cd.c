/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:58:47 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/26 17:40:53 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static char	*get_path_cd(char **cmd, t_env_main *main_env)
{
	char	*path;

	if (cmd[1] == NULL)
		path = ft_strdup(getenv("HOME"));
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		path = ft_strdup(getenv("OLDPWD"));
	else if (cmd[2] != NULL)
	{
		ft_putendl_fd("minishell: cd: too many arguments\n", 2);
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
		ft_putendl_fd(": No such file or directory\n", 2);
		main_env->exit_status = 1;
		free(path);
		return ;
	}
	free(path);
	main_env->exit_status = 0;
}
