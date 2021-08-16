/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:48:46 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:26:54 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *scr, size_t dstsize)
{
	size_t	a;
	size_t	b;
	size_t	c;

	a = 0;
	while (dst[a] != 0)
		a++;
	b = 0;
	while (scr[b] != 0)
		b++;
	if (dstsize <= a)
		b += dstsize;
	else
		b += a;
	c = 0;
	while (scr[c] != 0 && a + 1 < dstsize)
		dst[a++] = scr[c++];
	dst[a] = 0;
	return (b);
}
