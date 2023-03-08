/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:49:51 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 08:01:32 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char **argv, char *env[])
{
	t_env	*st;

	if (argc < 5)
		return (ft_printf("Error : not enough arguments\n"));
	st = malloc(sizeof(t_env));
	if (st == NULL)
		return (ft_printf("Error : %s\n", strerror(errno)));
	open_files(argc, argv, st);
	set_up_struct(st, argc, argv);
	execution(argv, env, st);
	return (0);
}
