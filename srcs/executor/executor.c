/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:57:04 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/29 19:08:14 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	find_redirect(t_all *data)
// {
// 	t_list	*tmp;

// 	tmp = data->args;
// 	data->in_out[0] = 0;
// 	data->in_out[1] = 0;
// 	while (tmp && ft_strncmp(tmp->content, "|", 2))
// 	{
// 		if (!ft_strncmp(tmp->content, ">", 2) && tmp->next)
// 			data->in_out[1] = open(tmp->next->content,
// 					O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 		else if (!ft_strncmp(tmp->content, ">>", 3) && tmp->next)
// 			data->in_out[1] = open(tmp->next->content,
// 					O_WRONLY | O_CREAT | O_APPEND, 0666);
// 		else if (!ft_strncmp(tmp->content, "<", 2) && tmp->next)
// 			data->in_out[0] = open(tmp->next->content, O_RDONLY, 0666);
// 		if (data->in_out[0] > 0 || data->in_out[1] > 0)
// 		{
// 			ft_lstdelelem(&(data->args), tmp->next);
// 			ft_lstdelelem(&(data->args), tmp);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

int	count_pipes(t_list *list)
{
	int	count;

	count = 0;
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
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		set_out(fd);
		if (!check_builtins(data))
			check_bin(data);
	}
	else
	{
		set_in(fd);
		waitpid(pid, NULL, 0);
	}
}

void	exec_cmd(t_all *data)
{
	pid_t	pid;

	if (!check_builtins(data))
	{
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			check_bin(data);
		else
			waitpid(pid, NULL, 0);
	}
}

int	executor(t_all *data)
{
	int	count_pipe;
	int	i;

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
	free_matrix((void **)data->argv);
	free_matrix((void **)data->envp);
	return (0);
}

// void	find_redirect(t_all *data)
// {
// 	t_list	*tmp;

// 	tmp = data->args;
// 	while (tmp && ft_strncmp(tmp->content, "|", 2))
// 	{
// 		if (!ft_strncmp(tmp->content, ">", 2) && tmp->next)
// 			data->in_out[1] = open(tmp->next->content,
// 					O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 		else if (!ft_strncmp(tmp->content, ">>", 3) && tmp->next)
// 			data->in_out[1] = open(tmp->next->content,
// 					O_WRONLY | O_CREAT | O_APPEND, 0666);
// 		else if (!ft_strncmp(tmp->content, "<", 2) && tmp->next)
// 			data->in_out[0] = open(tmp->next->content, O_RDONLY, 0666);
// 		if (data->in_out[0] > 0 || data->in_out[1] > 0)
// 		{
// 			ft_lstdelelem(&(data->args), tmp->next);
// 			ft_lstdelelem(&(data->args), tmp);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// int	count_pipes(t_list *list)
// {
// 	int	count;

// 	count = 0;
// 	while (list)
// 	{
// 		if (!ft_strncmp(list->content, "|", 2))
// 			count++;
// 		list = list->next;
// 	}
// 	return (count);
// }

// // void	init_wr_rd_flag(t_all *data, int i, int count_pipe)
// // {
// // 	if (i == 0 && count_pipe == 0)
// // 		data->wr_rd_flag = NO_WR_RD;
// // 	else if (i == 0)
// // 		data->wr_rd_flag = WRITE;
// // 	else if (count_pipe > i)
// // 		data->wr_rd_flag = WR_RD;
// // 	else if (count_pipe == i)
// // 		data->wr_rd_flag = READ;
// // 	data->in_out[0] = 0;
// // 	data->in_out[1] = 0;
// // }

// int	executor(t_all *data)
// {
// 	int	count_pipe;
// 	int	i;

// 	i = -1;
// 	count_pipe = count_pipes(data->args);
// 	while (++i < count_pipe)
// 	{
// 		// init_wr_rd_flag(data, i, count_pipe);
// 		// if (data->wr_rd_flag == WRITE || data->wr_rd_flag == WR_RD)
// 		// 	pipe(fds + (i * 2));
// 		find_redirect(data);
// 		if (check_builtins(data, fds))
// 			ft_lstdelelem(&(data->args), data->args);
// 		else if (check_bin(data, fds))
// 			ft_lstdelelem(&(data->args), data->args);
// 	}
// 	//printf("\n%s\n", data->args->content);
// 	check_bin_2(data, fds);
// 	dup2(data->fd_std[0], 0);
// 	return (0);
// }
