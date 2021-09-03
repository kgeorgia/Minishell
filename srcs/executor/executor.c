/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:57:04 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/09/03 18:21:07 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(t_list *list)
{
	int	count;

	count = 0;
	signal(SIGINT, check_c_in_child);
	signal(SIGQUIT, check_sl_in_child);
	while (list)
	{
		if (!ft_strncmp(list->content, "|", 2))
			count++;
		list = list->next;
	}
	return (count);
}

void	child_process(t_all *data)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error(data);
	pid = fork();
	if (pid == -1)
		error(data);
	if (pid == 0)
	{
		set_out(fd);
		if (!check_builtins(data))
			check_bin(data);
		exit(data->ret);
	}
	else
	{
		set_in(fd);
		waitpid(pid, &(data->ret), 0);
	}
}

void	exec_cmd(t_all *data)
{
	pid_t	pid;

	data->ret = 0;
	if (!check_builtins(data))
	{
		pid = fork();
		if (pid == -1)
			error(data);
		if (pid == 0)
		{
			check_bin(data);
			exit(data->ret);
		}
		else
			waitpid(pid, &(data->ret), 0);
	}
}

int	executor(t_all *data)
{
	int		count_pipe;
	char	*ret;
	int		i;

	i = -1;
	count_pipe = count_pipes(data->args);
	open_in_file(data);
	while (++i < count_pipe)
	{
		data->argv = copy_args(data);
		data->envp = copy_env(data);
		child_process(data);
		free_matrix((void **)data->argv);
		free_matrix((void **)data->envp);
	}
	open_out_file(data);
	data->argv = copy_args(data);
	data->envp = copy_env(data);
	exec_cmd(data);
	ret = ft_itoa(data->ret % 255);
	set_env(data, "?", ret);
	free(ret);
	free_matrix((void **)data->argv);
	free_matrix((void **)data->envp);
	return (0);
}
