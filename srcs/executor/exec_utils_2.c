/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:21:39 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/29 19:37:24 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_args(t_all *data)
{
	char	**res;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = data->args;
	while (tmp && ft_strncmp(tmp->content, "|", 2))
	{
		i++;
		tmp = tmp->next;
	}
	if (!i)
		return (NULL);
	res = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (data->args && ft_strncmp(data->args->content, "|", 2))
	{
		res[++i] = ft_strdup(data->args->content);
		ft_lstdelelem(&(data->args), data->args);
	}
	if (data->args)
		ft_lstdelelem(&(data->args), data->args);
	return (res);
}

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	post_cmd(t_all *data)
{
	int	ret;

	(void)data;
	wait(&ret);
	close(0);
	close(1);
	dup2(data->fd_std[0], 0);
	dup2(data->fd_std[1], 1);
}
