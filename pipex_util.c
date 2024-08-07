/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:42:24 by yojin             #+#    #+#             */
/*   Updated: 2024/07/17 16:57:08 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*trim_quotes(char *str)
{
	char	*result;

	result = ft_substr(str, 1, ft_strlen(str) - 3);
	if (!result)
		return (0);
	free(str);
	return (result);
}

int	add_node(t_arg *args, char *command, char *argv[])
{
	t_list	*node;
	t_info	*content;

	content = (t_info *)malloc(sizeof(t_info));
	if (!content)
		return (0);
	content->argv = argv;
	free(content->argv[0]);
	content->argv[0] = command;
	content->read_fd = 0;
	content->write_fd = 0;
	node = ft_lstnew(content);
	if (!node)
		error_exit();
	ft_lstadd_back(&(args->commands), node);
	return (1);
}

void	del_node(void *content)
{
	t_info	*info;

	info = (t_info *)content;
	free_strs(info->argv);
	free(content);
}

void	error_exit(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}
