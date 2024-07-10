/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:42:58 by yojin             #+#    #+#             */
/*   Updated: 2024/07/10 17:13:23 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_arg *arg, t_info *info)
{
	if (dup2(info->read_fd, STDIN_FILENO) == -1 || \
		dup2(info->write_fd, STDOUT_FILENO) == -1)
		error_exit();
	close(info->read_fd);
	close(info->write_fd);
	if (access(info->argv[0], X_OK) != 0 || *(arg->envp) == NULL)
		error_exit();
	if (execve(info->argv[0], info->argv, arg->envp))
		error_exit();
	return ;
}

int	run_child_process(t_arg *arg, int *fd, t_list *node)
{
	t_info	*info;
	int		pid;

	info = node->content;
	pid = fork();
	if (pid == -1)
		error_exit();
	if (pid == 0)
	{
		if (node->next)
			close(fd[READ]);
		else
		{
			info->write_fd = open(arg->outfile, \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (info->write_fd < 0)
				error_exit();
		}
		if (node == arg->commands->next)
		{
			info->read_fd = open(arg->infile, O_RDONLY);
			if (info->read_fd < 0)
				error_exit();
		}
		execute_command(arg, info);
	}
	return (pid);
}

int	pipex(t_arg *arg)
{
	int		pid;
	int		fd[2];
	t_list	*node;
	t_info	*info;

	node = arg->commands->next;
	while (node)
	{
		info = node->content;
		if (node != arg->commands->next)
		{
			info->read_fd = fd[READ];
			close(fd[WRITE]);
		}
		if (node->next && pipe(fd) == -1)
			error_exit();
		if (node->next)
			info->write_fd = fd[WRITE];
		pid = run_child_process(arg, fd, node);
		node = node->next;
	}
	return (pid);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	int		pid;
	int		status;
	int		exit_code;

	if (!init_arg(argc, argv, envp, &arg))
		exit(EXIT_FAILURE);
	pid = pipex(&arg);
	exit(EXIT_SUCCESS);
}
