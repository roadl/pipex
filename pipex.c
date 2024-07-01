/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:42:58 by yojin             #+#    #+#             */
/*   Updated: 2024/07/01 18:43:39 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_arg *arg, t_info *info)
{
	if (dup2(info->read_fd, STDIN_FILENO) == -1 || \
		dup2(info->write_fd, STDOUT_FILENO) == -1)
		error_exit();
	if (access(info->argv[0], X_OK) != 0 || *(arg->envp) == NULL)
		error_exit();
	if (execve(info->argv[0], info->argv, arg->envp))
		error_exit();
	return ;
}

int	run_child_process(t_arg *arg, t_info *info, int *fd, int is_last)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_exit();
	if (pid == 0)
	{
		if (!is_last)
			close(fd[READ]);
		execute_command(arg, info);
	}
}

void	pipex(t_arg *arg)
{
	int		pid;
	int		fd[2];
	t_list	*node;
	t_info	*info;

	node = arg->commands->next;
	while (node)
	{
		info = node->content;
		if (node == arg->commands->next)
			info->read_fd = arg->infile_fd;
		else
		{
			info->read_fd = fd[READ];
			close(fd[WRITE]);
		}
		if (node->next && pipe(fd) == -1)
			error_exit();
		if (!node->next)
			info->write_fd = arg->outfile_fd;
		else
			info->write_fd = fd[WRITE];
		pid = run_child_process(arg, info, fd, !node->next);
		node = node->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;

	if (!init_arg(argc, argv, envp, &arg))
		exit(EXIT_FAILURE);
	pipex(&arg);
	exit(EXIT_SUCCESS);
}
