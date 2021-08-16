/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:49:15 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:30:56 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		index;
	int		max_v;
	char	*out;

	index = start;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) > len)
		max_v = len;
	else
		max_v = ft_strlen(s + start);
	out = malloc(max_v + 1);
	if (!out)
		return (NULL);
	max_v += start;
	while (index < max_v)
	{
		out[index - start] = s[index];
		index++;
	}
	out[index - start] = '\0';
	return (out);
}
