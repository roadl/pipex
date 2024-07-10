/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:16:47 by yojin             #+#    #+#             */
/*   Updated: 2024/07/10 17:33:30 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "errno.h"

#define COMMAND_OFFSET	2

char	**parse_paths(char *envp[])
{
	char	**paths;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			paths = ft_split((*envp) + 5, ':');
			if (!paths)
			{
				perror("pipex");
				exit(EXIT_FAILURE);
			}
			return (paths);
		}
		envp++;
	}
	exit(EXIT_FAILURE);
}

char	*join_path(char *path, char *command)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (!temp)
		error_exit();
	result = ft_strjoin(temp, command);
	if (!result)
		error_exit();
	free(temp);
	return (result);
}

void	check_arg(int argc)
{
	if (argc <= 5)
	{
		ft_putstr_fd("pipex: argument count less than 5\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	check_command(char *command, t_arg *arg)
{
	char	**strs;
	char	*str;
	int		i;

	i = 0;
	strs = ft_split(command, ' ');
	if (!strs || !(*strs))
		error_exit();
	if (access(strs[0], X_OK) == 0)
	{
		add_node(arg, strs[0], strs);
		return ;
	}
	while (arg->paths[i])
	{
		str = join_path(arg->paths[i], strs[0]);
		if (access(str, X_OK) == 0)
		{
			add_node(arg, str, strs);
			return ;
		}
		free(str);
		i++;
	}
	add_node(arg, command, strs);
}

int	init_arg(int argc, char **argv, char **envp, t_arg *arg)
{
	int		i;

	check_arg(argc);
	arg->infile = argv[1];
	arg->outfile = argv[argc - 1];
	arg->command_num = argc - 3;
	arg->paths = parse_paths(envp);
	arg->here_doc = 0;
	arg->envp = envp;
	arg->commands = ft_lstnew(NULL);
	i = 0;
	while (i < arg->command_num)
		check_command(argv[(i++) + COMMAND_OFFSET], arg);
	return (1);
}
