/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:49:03 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:28:39 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] != 0 && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i] != 0 && i < len && haystack[i] == needle[j])
			{
				i++;
				j++;
			}
			if (needle[j] == 0)
				return ((char *)&haystack[i - j]);
			i -= j;
		}
		i++;
	}
	return (NULL);
}
