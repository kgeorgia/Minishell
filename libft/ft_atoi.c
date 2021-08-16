/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:46:35 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:16:56 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_space_num(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
	{
		i++;
	}
	return (i);
}

static int	ft_znak(const char *str, int *znak, int i)
{
	int	j;

	j = i;
	if (str[j] == '+' || str[j] == '-')
	{
		if (str[j] == '-')
			*znak *= -1;
		j++;
	}
	return (j);
}

int	ft_atoi(const char *str)
{
	unsigned long long	out;
	int					znak;
	int					i;

	znak = 1;
	out = 0;
	i = ft_space_num(str);
	i = ft_znak(str, &znak, i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		out *= 10;
		out += str[i] - '0';
		i++;
	}
	if (out > 9223372036854775807)
	{
		if (znak > 0)
			return (-1);
		return (0);
	}
	return (out * znak);
}
