/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:47:15 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:18:52 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_null_str(void)
{
	char	*res;

	res = malloc(2);
	if (!res)
		return (NULL);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

static int	ft_lennum(int n, int *znak)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		*znak = -1;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		znak;

	len = 0;
	znak = 1;
	if (n == 0)
		return (result = ft_null_str());
	len += ft_lennum(n, &znak);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	len--;
	if (znak)
		result[0] = '-';
	while (n)
	{
		result[len] = ((n % 10) * znak) + '0';
		n /= 10;
		len--;
	}
	return (result);
}
