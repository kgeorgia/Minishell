/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:48:08 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:23:16 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*out;
	size_t	count;

	out = b;
	count = 0;
	while (count < len)
	{
		*(unsigned char *)b = (unsigned char)c;
		b++;
		count++;
	}
	return (out);
}
