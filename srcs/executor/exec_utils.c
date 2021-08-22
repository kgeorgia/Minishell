/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:21:41 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/22 16:29:20 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_matrix(void **matrix)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (matrix[++i])
			free(matrix[i]);
		free(matrix);
	}
}

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

void	ft_lstdelelem(t_list **lst, t_list *del)
{
	t_list	*p;
	t_list	*tmp;

	tmp = NULL;
	p = *lst;
	if (*lst && del)
	{
		if (*lst == del)
		{
			*lst = (*lst)->next;
			free(p);
			return ;
		}
		while (p && p->next != del)
			p = p->next;
		if (p)
		{
			tmp = p->next;
			p->next = p->next->next;
			free(tmp);
		}
	}
}
