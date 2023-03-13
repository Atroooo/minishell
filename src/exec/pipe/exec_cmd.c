/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:33:14 by atro              #+#    #+#             */
/*   Updated: 2023/03/13 13:09:54 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	exec_cmd(int argc, char **argv, char *env[])
{
	t_env	*st;

	if (argc < 5)
		return (ft_printf("Error : not enough arguments\n"));
	st = malloc(sizeof(t_env));
	if (st == NULL)
		return (ft_printf("Error : %s\n", strerror(errno)));
	if (!open_files(argc, argv, st))
        return (0);
	if (!set_up_struct(st, argc, argv))
		return (0);
	execution(argv, env, st);
	return (0);
}
