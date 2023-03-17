/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/17 14:22:58 by atro             ###   ########.fr       */
=======
/*   By: neoff <neoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/16 10:41:33 by neoff            ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

<<<<<<< HEAD
static int	buildin_exec(char **cmd, t_env_main *main_env)
{
	if (!cmd)
		return (0);
	if (ft_strcmp("cd", cmd[0]) == 0)
		ft_cd(cmd, main_env);
	else if (ft_strcmp("echo", cmd[0]) == 0)
		ft_echo(cmd, main_env->env_list, main_env);
	else if (ft_strcmp("env", cmd[0]) == 0)
		ft_env(cmd, main_env->env_list, main_env);
	else if (ft_strcmp("exit", cmd[0]) == 0)
		ft_exit(cmd);
	else if (ft_strcmp("export", cmd[0]) == 0)
		main_env->env_list = ft_export(cmd, main_env->env_list, main_env);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
		ft_pwd(cmd, main_env);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		main_env->env_list = ft_unset(cmd, main_env->env_list, main_env);
	else
		return (0);
	return (1);
}

void	parsing(char *line, char *env[], t_env_main *main_env)
{
	char		**cmd_line;
	char		**strr;

	if (!line || line[0] == '\0')
		return ;
	cmd_line = ft_split(line, ' ');
	if (!cmd_line)
		return ;
	buildin_exec(cmd_line, main_env);
	redirect_input(cmd_line);
	redirect_output(cmd_line);
	redirect_output_append(cmd_line);
	if (ft_strcmp(cmd_line[0], "here_doc"))
		exec_cmd(6, strr, env, main_env);
	if (ft_strcmp(cmd_line[0], "exec") == 0)
	{
		strr = malloc(sizeof(char *) * 6);
		strr[0] = " ";
		strr[1] = "here_doc";
		strr[2] = "cat";
		strr[3] = "<<";
		strr[4] = "TEST";
		strr[5] = "ceci est un test";
		strr[6] = "j'espère qu'il sera";
		strr[7] = "concluant";
		strr[8] = "TEST";
		exec_cmd(9, strr, env, main_env);
	}
=======
int	check_error(char *line, t_line *all_cmd)
{
	if (input_operator_check(line))
		return (1);
	return (0);
}

void	parsing(char *line, t_line *all_cmd)
{
	if (check_error(line, all_cmd))
		return ;
	split_line(line, all_cmd);
	convert_in_3d_array(all_cmd);
>>>>>>> master
}
