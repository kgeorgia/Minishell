/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:31:27 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/22 14:53:16 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_all *data)
{
	char	*pwd;
	char	*home;

	home = NULL;
	ft_lstdelelem(&(data->args), data->args);
	get_env(data, "PWD", &pwd);
	if (!data->args || !ft_strncmp(data->args->content, "|", 2))
	{
		get_env(data, "HOME", &home);
		if (!chdir(home))
		{
			set_env(data, "OLDPWD", pwd);
			set_env(data, "PWD", home);
			free(home);
		}
	}
	else if (!chdir(data->args->content))
	{
		set_env(data, "OLDPWD", pwd);
		set_env(data, "PWD", getcwd(NULL, 0));
		ft_lstdelelem(&(data->args), data->args);
	}
	if (pwd)
		free(pwd);
}
