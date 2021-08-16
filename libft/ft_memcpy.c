/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:48:02 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:22:58 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*out;

	out = dst;
	if (dst == 0 && src == 0)
		return (0);
	while (n > 0)
	{
		*(char *)dst = *(char *)src;
		n--;
		dst++;
		src++;
	}
	return (out);
}
