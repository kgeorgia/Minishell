/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:48:30 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:35:14 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_amount_str(const char *s, const char c)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			i = 1;
			while (*s != '\0' && *s != c)
				s++;
			s--;
			n++;
		}
		s++;
	}
	if (i)
		if (!n)
			n = 1;
	return (n);
}

static int	get_len_str(const char *s, const char c, int i)
{
	int	n;

	n = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		n++;
	}
	return (n + 1);
}

static void	push_str(char *str, const char *s, int *i, char c)
{
	int	n;

	n = 0;
	while (s[*i] != '\0' && s[*i] == c)
		*i += 1;
	while (s[*i] != '\0' && s[*i] != c)
	{
		str[n] = s[*i];
		n++;
		*i += 1;
	}
	*i -= 1;
	str[n] = '\0';
}

static char	**ft_split_add(char **res, const char *s, char c)
{
	int	x;
	int	n;
	int	i;

	x = 0;
	i = 0;
	while (s[x] != '\0')
	{
		n = get_len_str(s, c, x);
		if (n == 1)
			break ;
		res[i] = (char *)malloc(sizeof(char) * n);
		if (!res[i])
		{
			while (i)
				free(res[i -= 1]);
			free(res);
			return (NULL);
		}
		push_str(res[i], s, &x, c);
		x += 1;
		i += 1;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		n;

	if (!s)
		return (NULL);
	n = get_amount_str(s, c) + 1;
	res = (char **)malloc(sizeof(char *) * n);
	if (res == NULL)
		return (NULL);
	res[n - 1] = NULL;
	if (n == 1)
		return (res);
	res = ft_split_add(res, s, c);
	return (res);
}
