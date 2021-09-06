/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:45:32 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/09/04 17:29:03 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_all *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (data->argv)
	{
		ft_putendl_fd("exit", 1);
		if (data->argv[1])
		{
			while (ft_isdigit(data->argv[1][i]))
				i++;
			if (data->argv[1][i] == '\0')
				ret = ft_atoi(data->argv[1]);
			else
			{
				blt_error(data->argv[0], data->argv[1],
					"numeric argument required");
				ret = 255;
			}	
		}		
	}
	else
		ft_putendl_fd("\e[1A\e[11C" "exit", 1);
	exit(ret);
}

void	ft_echo(t_all *data)
{
	int		i;
	int		endl_flag;

	i = 0;
	endl_flag = 0;
	while (data->argv[++i])
	{
		if (!endl_flag && !ft_strncmp(data->argv[i], "-n", 3))
		{
			endl_flag = 1;
			continue ;
		}
		else if (!endl_flag)
			endl_flag = -1;
		ft_putstr_fd(data->argv[i], 1);
		ft_putstr_fd(" ", 1);
	}
	if (endl_flag < 1)
		ft_putstr_fd("\n", 1);
}

void	ft_env(t_all *data)
{
	t_list	*list;

	list = data->env;
	if (!data->argv[1])
	{
		while (list)
		{
			if (ft_strncmp(list->content, "?=", 2))
				ft_putendl_fd(list->content, 1);
			list = list->next;
		}
	}
	else
	{
		ft_putendl_fd("\033[31mminishell: env: Too many arguments", 2);
		data->ret = 1;
	}
}

void	ft_export(t_all *data)
{
	int		i;
	char	**key_value;

	i = 0;
	if (!data->argv[1])
		return (show_sort_env(data));
	while (data->argv[++i])
	{
		if (env_is_valid(data->argv[i]))
		{
			key_value = parse_env(data->argv[i]);
			set_env(data, key_value[0], key_value[1]);
			free_matrix((void **)key_value);
		}
		else
		{
			ft_putstr_fd("\033[31mminishell: export: ", 2);
			ft_putstr_fd(data->argv[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			data->ret = 1;
		}
	}
}

void	ft_unset(t_all *data)
{
	int		i;
	t_list	*tmp;
	char	*str;

	i = 0;
	while (data->argv[++i])
	{
		str = ft_strjoin(data->argv[i], "=");
		tmp = data->env;
		while (tmp)
		{
			if (!ft_strncmp(tmp->content, str, ft_strlen(str)))
			{
				ft_lstdelelem(&(data->env), tmp);
				break ;
			}
			else if (tmp->next == NULL)
				data->ret = 1;
			tmp = tmp->next;
		}
		if (str)
			free(str);
	}
}
