/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:57:04 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/18 15:58:01 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelelem(t_list **lst, t_list *del)
{
	t_list	*p;
	t_list	*tmp;

	tmp = NULL;
	p = *lst;
	if (*lst && del)
	{
		if (*lst == del)
		{
			*lst = (*lst)->next;
			free(p);
			return ;
		}
		while (p && p->next != del)
			p = p->next;
		if (p)
		{
			tmp = p->next;
			p->next = p->next->next;
			free(tmp);
		}
	}
}

int	count_pipes(t_list *list, int ***fds)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	*fds = NULL;
	while (list)
	{
		if (!ft_strncmp(list->content, "|", 2))
			count++;
		list = list->next;
	}
	if (count)
	{
		*fds = malloc(count * sizeof(int *));
		while (++i < count)
			*fds[i] = malloc(2 * sizeof(int));
	}
	return (count);
}

void	init_wr_rd_flag(t_all *data, int i, int count_pipe)
{
	if (i == 0 && count_pipe == 0)
		data->wr_rd_flag = NO_WR_RD;
	else if (i == 0)
		data->wr_rd_flag = WRITE;
	else if (count_pipe > i)
		data->wr_rd_flag = WR_RD;
	else if (count_pipe == i)
		data->wr_rd_flag = READ;
}

int	executor(t_all *data)
{
	int	**fds;
	int	count_pipe;
	int	i;

	i = -1;
	count_pipe = count_pipes(data->args, &fds);
	while (++i <= count_pipe)
	{
		init_wr_rd_flag(data, i, count_pipe);
		if (data->wr_rd_flag == WRITE || data->wr_rd_flag == WR_RD)
			pipe(*fds);
		if (!check_builtins(data, fds))
			ft_lstdelelem(&(data->args), data->args);
		else if (!check_bin(data, fds))
			ft_lstdelelem(&(data->args), data->args);
	}
	return (0);
}
