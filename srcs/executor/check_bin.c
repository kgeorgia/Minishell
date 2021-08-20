/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:29:11 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/18 19:17:05 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static char	*search_bin(char *str, DIR **dir, struct dirent **d, t_data *param)
// {
// 	char		**paths;
// 	char		*path;
// 	int			i;

// 	if (!(paths = split_path(param, str)))
// 		return (NULL);
// 	i = -1;
// 	while (paths[++i])
// 	{
// 		*dir = opendir(paths[i]);
// 		while ((*dir) && errno != EACCES && (*d = readdir(*dir)))
// 		{
// 			if (!ft_memcmp(str, (*d)->d_name, ft_strlen(str) + 1))
// 			{
// 				path = ft_strjoin(paths[i], "/");
// 				free_matrix(paths);
// 				return (path);
// 			}
// 		}
// 		closedir(*dir);
// 	}
// 	free_matrix(paths);
// 	return (NULL);
// }

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

	find_redirect(data, fds);
	if (search_command(data, &cmd))
	{
		ft_lstdelelem(&(data->args), data->args);
		printf("%s\n", cmd);
	}
	return (0);
}