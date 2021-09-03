/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:29:11 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/09/03 18:35:59 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_path(t_all *data)
{
	char	*path;
	char	**res;

	res = NULL;
	if (get_env(data, "PATH", &path))
	{
		res = ft_split(path, ':');
		free(path);
	}
	return (res);
}

char	*search_in_dir(DIR **d, char *str, char *path)
{
	char			*res;
	struct dirent	*dir;

	res = NULL;
	if (*d != NULL)
	{
		dir = readdir(*d);
		while (dir)
		{
			if (!ft_strncmp(str, dir->d_name, ft_strlen(str) + 1))
			{
				res = ft_strjoin(path, "/");
				return (res);
			}
			dir = readdir(*d);
		}
	}
	return (res);
}

int	search_command(t_all *data, char **cmd)
{
	int				i;
	DIR				*d;
	char			**paths_bin;
	char			*tmp;

	i = -1;
	tmp = NULL;
	paths_bin = split_path(data);
	while (paths_bin[++i])
	{
		d = opendir(paths_bin[i]);
		tmp = search_in_dir(&d, data->argv[0], paths_bin[i]);
		if (d)
			closedir(d);
		if (tmp)
			break ;
	}
	free_matrix((void **)paths_bin);
	if (tmp)
	{
		*cmd = ft_strjoin(tmp, data->argv[0]);
		free(tmp);
		return (1);
	}
	return (0);
}

int	check_builtins(t_all *data)
{
	char	cwd[4097];

	if (!ft_strncmp(data->argv[0], "exit", 5))
		exit(0);
	else if (!ft_strncmp(data->argv[0], "pwd", 4))
		ft_putendl_fd(getcwd(cwd, 4096), 1);
	else if (!ft_strncmp(data->argv[0], "env", 4))
		ft_env(data);
	else if (!ft_strncmp(data->argv[0], "echo", 5))
		ft_echo(data);
	else if (!ft_strncmp(data->argv[0], "export", 7))
		ft_export(data);
	else if (!ft_strncmp(data->argv[0], "unset", 6))
		ft_unset(data);
	else if (!ft_strncmp(data->argv[0], "cd", 3))
		ft_cd(data);
	else
		return (0);
	return (1);
}

int	check_bin(t_all *data)
{
	char	*cmd;
	char	*path;

	if (!ft_strncmp(data->argv[0], "./", 2))
	{
		get_env(data, "PWD", &path);
		cmd = ft_strjoin(path, data->argv[0] + 1);
		if (execve(cmd, data->argv, data->envp) == -1)
			error(data);
	}
	else if (search_command(data, &cmd))
	{
		if (execve(cmd, data->argv, data->envp) == -1)
			error(data);
	}
	else
	{
		ft_putstr_fd("\033[31mminishell: ", 2);
		ft_putstr_fd(data->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		data->ret = 127;
	}
	return (1);
}
