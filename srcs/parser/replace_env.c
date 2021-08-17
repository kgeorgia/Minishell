/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:03:31 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/17 20:00:30 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_dollar(char *cont, char **res, int *i, t_all *data)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = NULL;
	if (cont[*i] == '$')
	{
		key = find_key(cont + (*i) + 1);
		*i += ft_strlen(key);
		if (get_env(data, key, &value))
		{
			tmp = ft_strjoin(*res, value);
			free(*res);
			*res = tmp;
		}
		if (key)
			free(key);
		if (value)
			free(value);
		return (1);
	}
	return (0);
}

void	replace_env_in_quot(char *cont, char **res, int *i, t_all *data)
{
	*res = add_symbol(*res, cont[*i]);
	*i += 1;
	while (cont[*i] && cont[*i] != '"')
	{
		if (replace_dollar(cont, res, i, data))
		{
			*i += 1;
			continue ;
		}
		*res = add_symbol(*res, cont[*i]);
		*i += 1;
	}
	*res = add_symbol(*res, cont[*i]);
}

char	*skip_quotes(char *content)
{
	char	*res;
	int		i;

	i = -1;
	res = NULL;
	if (!content)
		return (ft_strdup(""));
	while (content[++i])
	{
		if (content[i] == 39)
			while (content[++i] && content[i] != 39)
				res = add_symbol(res, content[i]);
		else if (content[i] == '"')
			while (content[++i] && content[i] != '"')
				res = add_symbol(res, content[i]);
		else
			res = add_symbol(res, content[i]);
	}
	if (content)
		free(content);
	return (res);
}

char	*replace_env(char *cont, t_all *data)
{
	char	*res;
	int		i;

	i = -1;
	res = NULL;
	while (cont[++i])
	{
		if (cont[i] == 39)
		{
			res = add_symbol(res, cont[i]);
			while (cont[++i] && cont[i] != 39)
				res = add_symbol(res, cont[i]);
			res = add_symbol(res, cont[i]);
		}	
		else if (cont[i] == '"')
			replace_env_in_quot(cont, &res, &i, data);
		else if (replace_dollar(cont, &res, &i, data))
			continue ;
		else
			res = add_symbol(res, cont[i]);
	}
	res = skip_quotes(res);
	return (res);
}

void	parser_replace_env(t_all *data)
{
	t_list	*temp;

	temp = ft_lstmap_env(data->args, &replace_env, &free, data);
	ft_lstclear(&(data->args), &free);
	data->args = temp;
}
