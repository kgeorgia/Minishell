/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 16:29:42 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/20 20:20:01 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parse_env(char *str)
{
	int		i;
	char	**res;

	i = -1;
	res = ft_calloc(3, sizeof(char *));
	while (str[++i] && str[i] != '=')
		res[0] = add_symbol(res[0], str[i]);
	if (str[i] == '=')
		while (str[++i])
			res[1] = add_symbol(res[1], str[i]);
	return (res);
}

int	env_is_valid(char *str)
{
	char	*key_tmp;
	char	*key;
	int		res;

	res = 0;
	key_tmp = find_key(str);
	key = ft_strjoin(key_tmp, "=");
	if (!ft_strncmp(key, str, ft_strlen(key)))
		res = 1;
	if (key)
		free(key);
	if (key_tmp)
		free(key_tmp);
	return (res);
}

void	ft_export(t_all *data)
{
	char	**key_value;
	t_list	*list;

	ft_lstdelelem(&(data->args), data->args);
	while (data->args && ft_strncmp(data->args->content, "|", 2))
	{
		if (env_is_valid(data->args->content))
		{
			key_value = parse_env(data->args->content);
			set_env(data, key_value[0], key_value[1]);
			free_matrix(key_value);
		}
		else
			ft_putendl_fd("Invalid arg!", 1);
		ft_lstdelelem(&(data->args), data->args);
	}
}
