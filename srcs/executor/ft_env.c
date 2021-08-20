/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 16:26:58 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/20 16:29:19 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_all *data)
{
	t_list	*list;

	list = data->env;
	ft_lstdelelem(&(data->args), data->args);
	while (list)
	{
		ft_putendl_fd(list->content, 1);
		list = list->next;
	}
}
