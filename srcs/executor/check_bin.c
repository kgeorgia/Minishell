/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:29:11 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/22 19:23:46 by kgeorgia         ###   ########.fr       */
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

char	**copy_args(t_all *data)
{
	char	**res;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = data->args;
	while (tmp && ft_strncmp(tmp->content, "|", 2))
	{
		i++;
		tmp = tmp->next;
	}
	if (!i)
		return (NULL);
	res = ft_calloc(i + 1, sizeof(char *));
	tmp = data->args;
	i = -1;
	while (tmp && ft_strncmp(tmp->content, "|", 2))
	{
		res[++i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (res);
}

int	check_bin(t_all *data, int **fds)
{
	char	*cmd;
	char	**argv;
	char	**envp;
	int		ret;

	find_redirect(data, fds);
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
		wait(&ret);
		free_matrix((void **)argv);
		free_matrix((void **)envp);
		free(cmd);
	}
	return (0);
}
