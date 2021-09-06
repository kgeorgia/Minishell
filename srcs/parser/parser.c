/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:43:24 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/09/06 14:09:30 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quot_marks(char *input, int *start, int *end)
{
	if (input[*start + *end] == '"')
	{
		*end += 1;
		while (input[*start + *end] && input[*start + *end] != '"')
			*end += 1;
		if (!input[*start + *end])
			return (1);
	}
	if (input[*start + *end] == 39)
	{
		*end += 1;
		while (input[*start + *end] && input[*start + *end] != 39)
			*end += 1;
		if (!input[*start + *end])
			return (1);
	}
	return (0);
}

int	check_redirect(char *input, int *start, int *end)
{
	char	*str;

	str = input + (*start + *end);
	if (*end == 0)
	{
		if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		{
			*end = 1;
			if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
				*end = 2;
			return (1);
		}
	}
	else if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		return (1);
	return (0);
}

int	parser(char *input, t_all *data)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (1)
	{
		while (input[start] == ' ')
			start++;
		while (input[start + end] && input[start + end] != ' ')
		{
			if (check_redirect(input, &start, &end))
				break ;
			if (input[start + end] == ';' || quot_marks(input, &start, &end))
				return (1);
			end++;
		}
		ft_lstadd_back(&(data->args), ft_lstnew(ft_substr(input, start, end)));
		if (!input[start + end])
			break ;
		start += end;
		end = 0;
	}
	parser_replace_env(data);
	return (0);
}
