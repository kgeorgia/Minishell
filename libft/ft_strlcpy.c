/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:48:49 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:27:04 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *scr, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!scr)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(scr));
	while (i < dstsize - 1 && scr[i] != '\0')
	{
		dst[i] = scr[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(scr));
}
