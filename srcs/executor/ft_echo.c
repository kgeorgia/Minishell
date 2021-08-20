/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:29:38 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/20 16:26:06 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_all *data)
{
	int		endl_flag;

	ft_lstdelelem(&(data->args), data->args);
	endl_flag = 0;
	while (data->args && ft_strncmp(data->args->content, "|", 2))
	{
		if (!endl_flag && !ft_strncmp(data->args->content, "-n", 3))
		{
			endl_flag = 1;
			ft_lstdelelem(&(data->args), data->args);
			continue ;
		}
		else if (!endl_flag)
			endl_flag = -1;
		ft_putstr_fd(data->args->content, 1);
		ft_putstr_fd(" ", 1);
		ft_lstdelelem(&(data->args), data->args);
	}
	if (endl_flag < 1)
		ft_putstr_fd("\n", 1);
}
