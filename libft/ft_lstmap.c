/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:47:41 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 17:21:20 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*start;
	t_list	*l;

	if (!lst)
		return (NULL);
	l = lst;
	start = ft_lstnew(f(l->content));
	if (!start)
		return (NULL);
	l = l->next;
	while (l)
	{
		p = ft_lstnew(f(l->content));
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
