/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:32 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/26 13:26:55 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

#include "../../../header/minishell.h"

static long long	return_number(double long nb, int sign)
{
	if ((nb * sign) > LLONG_MIN && (nb * sign) < LLONG_MAX)
		return (nb * sign);
	if ((nb * sign) < LLONG_MIN)
		return (-1);
	if ((nb * sign) > LLONG_MAX)
		return (-1);
	return (nb * sign);
}

static long long	ft_atoll(const char *str)
{
	int			sign;
	double long	nb;
	int			i;

	sign = 1;
	nb = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (48 <= str[i] && str[i] <= 57)
	{
		nb = (nb * 10) + str[i] - '0';
		if (!(48 <= str[i + 1] && str[i + 1] <= 57))
			return (return_number(nb, sign));
		i++;
	}
	return (0);
}

static void	free_exit_builtin(t_env_main *main_env, t_line *all_cmd)
{
	free_cmd(all_cmd);
	free_inout_list(all_cmd->infile);
	free_inout_list(all_cmd->outfile);
	free_main_env(main_env);
}

void	ft_exit(char **cmd, t_env_main *main_env, t_line *all_cmd)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "exit") != 0)
		return ;
	if (cmd_size(cmd) > 1)
	{
		if ((cmd[1][0] != '-' && cmd[1][0] != '+' && !ft_isdigit(cmd[1][0])) \
			|| ft_atoll(cmd[1]) == -1)
		{
			ft_printf("exit: %s: numeric argument required\n", cmd[1]);
			main_env->exit_status = 2;
			return ;
		}
	}
	if (cmd_size(cmd) > 2)
	{
		ft_printf("exit: too many arguments\n");
		main_env->exit_status = 1;
		return ;
	}
	else if (cmd[1])
		main_env->exit_status = (unsigned char)ft_atoll(cmd[1]);
	else
		main_env->exit_status = 0;
	free_exit_builtin(main_env, all_cmd);
}

//WEXITSTATUS(status) returns the exit status of the child. This consists of the