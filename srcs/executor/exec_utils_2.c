/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:21:39 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/31 18:34:55 by kgeorgia         ###   ########.fr       */
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

void	error(t_all *data)
{
	ft_putstr_fd("\033[31mminishell: ", 2);
	perror(data->argv[0]);
	exit(errno);
}

char	*ret_first_or_last(t_list *lst, int first_last)
{
	char	*ret;

	ret = lst->content;
	if (!first_last)
	{
		while (lst)
		{
			if (ft_strncmp(ret, lst->content, ft_strlen(lst->content)) > 0)
				ret = lst->content;
			lst = lst->next;
		}
	}
	else
	{
		while (lst)
		{
			if (ft_strncmp(ret, lst->content, ft_strlen(lst->content)) < 0)
				ret = lst->content;
			lst = lst->next;
		}
	}
	return (ret);
}

void	show_sort_env(t_all *data)
{
	t_list	*lst;
	char	*prev;
	char	*current;

	prev = ret_first_or_last(data->env, 0);
	if (ft_strncmp(prev, "?=", 2))
		printf("declare -x %s\n", prev);
	current = ret_first_or_last(data->env, 1);
	while (ft_strncmp(prev, current, ft_strlen(current) + 1))
	{
		lst = data->env;
		while (lst)
		{
			if (ft_strncmp(current, lst->content, ft_strlen(lst->content)) > 0
				&& ft_strncmp(prev, lst->content, ft_strlen(lst->content)) < 0)
				current = lst->content;
			lst = lst->next;
		}
		if (ft_strncmp(current, "?=", 2))
			printf("declare -x %s\n", current);
		prev = current;
		current = ret_first_or_last(data->env, 1);
	}
}
