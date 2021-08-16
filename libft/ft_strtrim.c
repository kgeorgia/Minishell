/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:49:11 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:29:01 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	index;
	int	len;

	index = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[index] && ft_strchr(set, s1[index]))
		index++;
	while (len > index && ft_strchr(set, s1[len]))
		len--;
	len -= index - 1;
	return (ft_substr(s1, index, len));
}
