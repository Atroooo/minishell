/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:57:11 by marvin            #+#    #+#             */
/*   Updated: 2023/03/21 09:57:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	buildin_exec(t_line *all_cmd, t_env_main *main_env)
{
	if (!all_cmd->all_cmd[0])
		return (0);
	if (ft_strcmp("exit", all_cmd->all_cmd[0][0]) == 0)
		ft_exit(all_cmd->all_cmd[0], main_env, all_cmd);
	else if (all_cmd->outfile == NULL && \
	ft_strcmp("export", all_cmd->all_cmd[0][0]) == 0)
		main_env->env_list = ft_export(all_cmd->all_cmd[0], main_env);
	else if (ft_strcmp("unset", all_cmd->all_cmd[0][0]) == 0)
		main_env->env_list = ft_unset(all_cmd->all_cmd[0], \
			main_env->env_list, main_env);
	else if (ft_strcmp("cd", all_cmd->all_cmd[0][0]) == 0)
		ft_cd(all_cmd->all_cmd[0], main_env);
	else
		return (0);
	if (main_env->env_list == NULL)
		return (-1);
	return (1);
}

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

static int	env_lst_to_char(t_env_main *main_env)
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
	return (1);
}

static int	exec_cmd(t_env_main *main_env, t_line *all_cmd)
{
	t_env_pipe	*st;

	if (!env_lst_to_char(main_env))
		return (0);
	if (all_cmd->nbr_cmd == 1)
		if (buildin_exec(all_cmd, main_env))
			return (1);
	st = malloc(sizeof(t_env_pipe));
	if (st == NULL)
	{
		ft_putstr_fd("Error : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	check_inout(st, all_cmd);
	if (!open_files(st, all_cmd))
		return (0);
	if (!setup_struct_cmd(st, all_cmd, main_env))
		return (0);
	if (!execution(all_cmd, st, main_env))
	{
		free_cmd_exec(all_cmd, st, main_env);
		return (0);
	}
	return (1);
}

void	exec_hub(t_line *all_cmd, t_env_main *main_env)
{
	if (exec_cmd(main_env, all_cmd))
		main_env->exit_status = 0;
	else
		main_env->exit_status = 1;
	free_cmd(all_cmd);
	free_inout_list(all_cmd->infile);
	free_inout_list(all_cmd->outfile);
	free_str(main_env->env);
}
