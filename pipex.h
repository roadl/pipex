/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:34:07 by yojin             #+#    #+#             */
/*   Updated: 2024/05/20 19:02:39 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

# include "ft_printf/ft_printf.h"

# define TRUE 1
# define FALSE 0

# define READ 0
# define WRITE 1

typedef struct s_arg
{
	t_list	*commands;
	char	**paths;
	char	**envp;
	int		command_num;
	int		here_doc;
	int		infile_fd;
	int		outfile_fd;
}	t_arg;

typedef struct s_info
{
	char	*command;
	char	**argv;
	int		read_fd;
	int		write_fd;
}	t_info;

int		add_node(t_arg *args, char *command, char *argv[]);
void	del_node(void *content);
void	error_exit(void);

int		init_arg(int argc, char **argv, char **envp, t_arg *arg);

void	print_status(t_arg *args);
void	f(void);

#endif