/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:48:43 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:26:36 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		index;
	char	*out;

	index = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	out = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!out)
		return (NULL);
	while (index < (int)ft_strlen(s1))
	{
		out[index] = s1[index];
		index++;
	}
	index = 0;
	while (index < (int)ft_strlen(s2))
	{
		out[index + ft_strlen(s1)] = s2[index];
		index++;
	}
	out[index + ft_strlen(s1)] = '\0';
	return (out);
}
