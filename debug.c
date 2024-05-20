/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:49:52 by yojin             #+#    #+#             */
/*   Updated: 2024/05/20 19:18:25 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_status(t_arg *args)
{
	int		i;
	int		j;
	t_list	*node;
	t_info	*info;

	i = 0;
	node = args->commands->next;
	while (node)
	{
		ft_printf("[%d]:", i);
		j = 0;
		info = node->content;
		ft_printf("command: %s\n", info->command);
		while (info->argv[j])
			ft_printf("\t%s\n", info->argv[j++]);
		node = node->next;
		i++;
	}
}

void	f(void)
{
	system("leaks pipex");
}
