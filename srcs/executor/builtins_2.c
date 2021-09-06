/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:49:18 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/09/04 17:31:55 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	blt_error(char *cmd, char *arg, char *err)
{
	ft_putstr_fd("\033[31mminishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}

void	ft_cd(t_all *data)
{
	char	*pwd;
	char	*home;

	home = NULL;
	get_env(data, "PWD", &pwd);
	if (data->argv[1] == NULL)
	{
		get_env(data, "HOME", &home);
		if (!chdir(home))
			if (set_env(data, "OLDPWD", pwd) && set_env(data, "PWD", home))
				free(home);
	}
	else if (!chdir(data->argv[1]))
	{
		set_env(data, "OLDPWD", pwd);
		set_env(data, "PWD", getcwd(NULL, 0));
	}
	else
	{
		blt_error(data->argv[0], data->argv[1], ": No such file or directory");
		data->ret = 1;
	}
	if (pwd)
		free(pwd);
}
