/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:29:11 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/23 16:42:04 by kgeorgia         ###   ########.fr       */
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
	if (!*d)
		return (res);
	dir = readdir(*d);
	while (dir)
	{
		if (!ft_strncmp(str, dir->d_name, ft_strlen(dir->d_name)))
		{
			res = ft_strjoin(path, "/");
			return (res);
		}
		dir = readdir(*d);
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
		tmp = search_in_dir(&d, data->args->content, paths_bin[i]);
		closedir(d);
		if (tmp)
			break ;
	}
	free_matrix((void **)paths_bin);
	if (tmp)
	{
		*cmd = ft_strjoin(tmp, data->args->content);
		free(tmp);
		return (1);
	}
	return (0);
}

int	check_bin(t_all *data, int **fds)
{
	char	*cmd;
	char	**argv;
	char	**envp;

	(void)fds;
	find_redirect(data);
	if (search_command(data, &cmd))
	{
		argv = copy_args(data);
		envp = copy_env(data);
		if (!fork())
		{
			if (execve(cmd, argv, envp))
			{
				ft_putendl_fd("Error!!", 1);
				exit(0);
			}
		}
		post_cmd(data);
		free_matrix((void **)argv);
		free_matrix((void **)envp);
		free(cmd);
	}
	return (0);
}

int	check_builtins(t_all *data, int **fds)
{
	char	cwd[4097];

	(void)fds;
	find_redirect(data);
	if (!ft_strncmp(data->args->content, "exit", 5))
		exit(0);
	else if (!ft_strncmp(data->args->content, "pwd", 4))
	{
		ft_lstdelelem(&(data->args), data->args);
		ft_putendl_fd(getcwd(cwd, 4096), 1);
	}
	else if (!ft_strncmp(data->args->content, "env", 4))
		ft_env(data);
	else if (!ft_strncmp(data->args->content, "echo", 5))
		ft_echo(data);
	else if (!ft_strncmp(data->args->content, "export", 7))
		ft_export(data);
	else if (!ft_strncmp(data->args->content, "unset", 6))
		ft_unset(data);
	else if (!ft_strncmp(data->args->content, "cd", 3))
		ft_cd(data);
	else
		return (0);
	return (1);
}
