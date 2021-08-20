/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:04:23 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/20 16:24:15 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_redirect(t_all *data, int **fds)
{
	(void)data;
	(void)fds;
	return (0);
}

int	check_builtins(t_all *data, int **fds)
{
	char	cwd[4097];

	find_redirect(data, fds);
	if (!ft_strncmp(data->args->content, "exit", 5))
		exit(0);
	else if (!ft_strncmp(data->args->content, "pwd", 4))
	{
		ft_lstdelelem(&(data->args), data->args);
		ft_putendl_fd(getcwd(cwd, 4096), 1);
	}
	// else if (!ft_strncmp(data->args->content, "env", 4))
	// 	ft_env(data);
	// else if (!ft_strncmp(data->args->content, "echo", 5))
	// 	ft_echo(data);
	// else if (!ft_strncmp(data->args->content, "export", 7))
	// 	ft_export(data);
	// else if (!ft_strncmp(data->args->content, "unset", 6))
	// 	ft_unset(data);
	// else if (!ft_strncmp(data->args->content, "cd", 3))
	// 	ft_cd(data);
	else
		return (1);
	return (0);
}
