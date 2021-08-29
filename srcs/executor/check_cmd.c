/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:29:11 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/29 18:57:46 by kgeorgia         ###   ########.fr       */
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
			if (!ft_strncmp(str, dir->d_name, ft_strlen(dir->d_name)))
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

	if (search_command(data, &cmd))
	{
		if (execve(cmd, data->argv, data->envp) == -1)
			error();
	}
	else
		if (execve(data->argv[0], data->argv, data->envp) == -1)
			error();
	return (1);
}

// int	check_command(t_all *data)
// {
// 	char	cwd[4097];
// 	char	*cmd;

// 	if (!ft_strncmp(data->argv[0], "exit", 5))
// 		exit(0);
// 	else if (!ft_strncmp(data->argv[0], "pwd", 4))
// 		ft_putendl_fd(getcwd(cwd, 4096), 1);
// 	else if (!ft_strncmp(data->argv[0], "env", 4))
// 		ft_env(data);
// 	else if (!ft_strncmp(data->argv[0], "echo", 5))
// 		ft_echo(data);
// 	else if (!ft_strncmp(data->argv[0], "export", 7))
// 		ft_export(data);
// 	else if (!ft_strncmp(data->argv[0], "unset", 6))
// 		ft_unset(data);
// 	else if (!ft_strncmp(data->argv[0], "cd", 3))
// 		ft_cd(data);
// 	else if (search_command(data, &cmd))
// 	{
// 		if (execve(cmd, data->argv, data->envp) == -1)
// 			error();
// 	}
// 	else
// 		if (execve(data->argv[0], data->argv, data->envp) == -1)
// 			error();
// 	return (1);
// }

// int	check_bin(t_all *data, int *fds)
// {
// 	pid_t	pid;
// 	int		fd[2];
// 	char	*cmd;
// 	char	**argv;
// 	char	**envp;

// 	(void)fds;
// 	if (pipe(fd) == -1)
// 		error();
// 	search_command(data, &cmd);
// 	argv = copy_args(data);
// 	envp = copy_env(data);
// 	pid = fork();
// 	if (pid == -1)
// 		error();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		execve(cmd, argv, envp);
// 	}
// 	else
// 	{
// 		free_matrix((void **)argv);
// 		free_matrix((void **)envp);
// 		free(cmd);
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		ft_lstdelelem(&(data->args), data->args);
// 		waitpid(pid, NULL, 0);
// 	}
// 	return (1);
// }

// int	check_bin_2(t_all *data, int *fds)
// {
// 	pid_t	pid;
// 	char	*cmd;
// 	char	**argv;
// 	char	**envp;

// 	(void)fds;
// 	search_command(data, &cmd);
// 	argv = copy_args(data);
// 	envp = copy_env(data);
// 	pid = fork();
// 	if (pid == -1)
// 		error();
// 	if (pid == 0)
// 	{
// 		execve(cmd, argv, envp);
// 	}
// 	else
// 	{
// 		free_matrix((void **)argv);
// 		free_matrix((void **)envp);
// 		free(cmd);
// 		waitpid(pid, NULL, 0);
// 	}
// 	return (1);
// }

// int	check_bin(t_all *data, int *fds)
// {
// 	char	*cmd;
// 	char	**argv;
// 	char	**envp;

// 	(void)fds;
// 	if (search_command(data, &cmd))
// 	{
// 		argv = copy_args(data);
// 		envp = copy_env(data);
// 		if (!fork())
// 		{
// 			if (execve(cmd, argv, envp))
// 			{
// 				ft_putendl_fd("Error!!", 1);
// 				exit(0);
// 			}
// 		}
// 		post_cmd(data);
// 		free_matrix((void **)argv);
// 		free_matrix((void **)envp);
// 		free(cmd);
// 	}
// 	return (0);
// }

// int	check_builtins(t_all *data, int *fds)
// {
// 	char	cwd[4097];

// 	(void)fds;
// 	if (!ft_strncmp(data->args->content, "exit", 5))
// 		exit(0);
// 	else if (!ft_strncmp(data->args->content, "pwd", 4))
// 	{
// 		ft_lstdelelem(&(data->args), data->args);
// 		ft_putendl_fd(getcwd(cwd, 4096), 1);
// 	}
// 	else if (!ft_strncmp(data->args->content, "env", 4))
// 		ft_env(data);
// 	else if (!ft_strncmp(data->args->content, "echo", 5))
// 		ft_echo(data);
// 	else if (!ft_strncmp(data->args->content, "export", 7))
// 		ft_export(data);
// 	else if (!ft_strncmp(data->args->content, "unset", 6))
// 		ft_unset(data);
// 	else if (!ft_strncmp(data->args->content, "cd", 3))
// 		ft_cd(data);
// 	else
// 		return (0);
// 	return (1);
// }
