/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:03:27 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/17 20:00:28 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_key(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if (ft_isdigit(str[i]) || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (res);
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'
			|| ft_isdigit(str[i])))
	{
		res = add_symbol(res, str[i]);
		i++;
	}
	return (res);
}

t_list	*ft_lstmap_env(t_list *lst, char *(*f)(char *, t_all *data),
			void (*del)(void *), t_all *data)
{
	t_list	*p;
	t_list	*start;
	t_list	*l;

	if (!lst)
		return (NULL);
	l = lst;
	start = ft_lstnew(f(l->content, data));
	if (!start)
		return (NULL);
	l = l->next;
	while (l)
	{
		p = ft_lstnew(f(l->content, data));
		if (!p)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, p);
		l = l->next;
	}
	return (start);
}

int	get_env(t_all *data, char *key, char **value)
{
	t_list	*lst;
	char	*str;

	lst = data->env;
	str = ft_strjoin(key, "=");
	*value = NULL;
	while (lst)
	{
		if (!ft_strncmp(str, lst->content, ft_strlen(str)))
			*value = ft_strdup(lst->content + ft_strlen(str));
		lst = lst->next;
	}
	free(str);
	if (*value)
		return (1);
	return (0);
}

int	set_env(t_all *data, char *key, char *value)
{
	t_list	*lst;
	char	*str;

	lst = data->env;
	str = ft_strjoin(key, "=");
	while (lst)
	{
		if (!ft_strncmp(str, lst->content, ft_strlen(str)))
		{
			free(lst->content);
			lst->content = ft_strjoin(str, value);
			break ;
		}
		lst = lst->next;
	}
	if (!lst)
		ft_lstadd_back(&(data->env), ft_lstnew(ft_strjoin(str, value)));
	free(str);
	return (1);
}

char	*add_symbol(char *str, char c)
{
	char	*res;
	int		i;

	i = ft_strlen(str);
	res = malloc(i + 2);
	res[i + 1] = '\0';
	res[i] = c;
	while (--i >= 0)
		res[i] = str[i];
	if (str)
		free(str);
	return (res);
}
