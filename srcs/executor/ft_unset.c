/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:17:21 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/22 14:53:33 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_all *data)
{
	t_list	*tmp;
	char	*str;

	ft_lstdelelem(&(data->args), data->args);
	while (data->args && ft_strncmp(data->args->content, "|", 2))
	{
		str = data->args->content;
		tmp = data->env;
		while (tmp)
		{
			if (!ft_strncmp(tmp->content, str, ft_strlen(str) + 1))
			{
				ft_lstdelelem(&(data->env), tmp);
				break ;
			}
			tmp = tmp->next;
		}
		ft_lstdelelem(&(data->args), data->args);
	}
}
