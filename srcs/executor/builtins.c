#include "../minishell.h"

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
		{
			set_env(data, "OLDPWD", pwd);
			set_env(data, "PWD", home);
			free(home);
		}
	}
	else if (!chdir(data->argv[1]))
	{
		set_env(data, "OLDPWD", pwd);
		set_env(data, "PWD", getcwd(NULL, 0));
	}
	if (pwd)
		free(pwd);
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
	while (list)
	{
		ft_putendl_fd(list->content, 1);
		list = list->next;
	}
}

void	ft_export(t_all *data)
{
	int		i;
	char	**key_value;

	i = 0;
	while (data->argv[++i])
	{
		if (env_is_valid(data->argv[i]))
		{
			key_value = parse_env(data->argv[i]);
			set_env(data, key_value[0], key_value[1]);
			free_matrix((void **)key_value);
		}
		else
			ft_putendl_fd("Invalid arg!", 1);
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
			tmp = tmp->next;
		}
		if (str)
			free(str);
	}
}

// void	ft_cd(t_all *data)
// {
// 	char	*pwd;
// 	char	*home;

// 	home = NULL;
// 	ft_lstdelelem(&(data->args), data->args);
// 	get_env(data, "PWD", &pwd);
// 	if (!data->args || !ft_strncmp(data->args->content, "|", 2))
// 	{
// 		get_env(data, "HOME", &home);
// 		if (!chdir(home))
// 		{
// 			set_env(data, "OLDPWD", pwd);
// 			set_env(data, "PWD", home);
// 			free(home);
// 		}
// 	}
// 	else if (!chdir(data->args->content))
// 	{
// 		set_env(data, "OLDPWD", pwd);
// 		set_env(data, "PWD", getcwd(NULL, 0));
// 		ft_lstdelelem(&(data->args), data->args);
// 	}
// 	if (pwd)
// 		free(pwd);
// }

// void	ft_echo(t_all *data)
// {
// 	int		endl_flag;

// 	ft_lstdelelem(&(data->args), data->args);
// 	endl_flag = 0;
// 	while (data->args && ft_strncmp(data->args->content, "|", 2))
// 	{
// 		if (!endl_flag && !ft_strncmp(data->args->content, "-n", 3))
// 		{
// 			endl_flag = 1;
// 			ft_lstdelelem(&(data->args), data->args);
// 			continue ;
// 		}
// 		else if (!endl_flag)
// 			endl_flag = -1;
// 		ft_putstr_fd(data->args->content, 1);
// 		ft_putstr_fd(" ", 1);
// 		ft_lstdelelem(&(data->args), data->args);
// 	}
// 	if (endl_flag < 1)
// 		ft_putstr_fd("\n", 1);
// }

// void	ft_env(t_all *data)
// {
// 	t_list	*list;

// 	list = data->env;
// 	ft_lstdelelem(&(data->args), data->args);
// 	while (list)
// 	{
// 		ft_putendl_fd(list->content, 1);
// 		list = list->next;
// 	}
// }

// void	ft_export(t_all *data)
// {
// 	char	**key_value;

// 	ft_lstdelelem(&(data->args), data->args);
// 	while (data->args && ft_strncmp(data->args->content, "|", 2))
// 	{
// 		if (env_is_valid(data->args->content))
// 		{
// 			key_value = parse_env(data->args->content);
// 			set_env(data, key_value[0], key_value[1]);
// 			free_matrix((void **)key_value);
// 		}
// 		else
// 			ft_putendl_fd("Invalid arg!", 1);
// 		ft_lstdelelem(&(data->args), data->args);
// 	}
// }

// void	ft_unset(t_all *data)
// {
// 	t_list	*tmp;
// 	char	*str;

// 	ft_lstdelelem(&(data->args), data->args);
// 	while (data->args && ft_strncmp(data->args->content, "|", 2))
// 	{
// 		str = ft_strjoin(data->args->content, "=");
// 		tmp = data->env;
// 		while (tmp)
// 		{
// 			if (!ft_strncmp(tmp->content, str, ft_strlen(str)))
// 			{
// 				ft_lstdelelem(&(data->env), tmp);
// 				break ;
// 			}
// 			tmp = tmp->next;
// 		}
// 		if (str)
// 			free(str);
// 		ft_lstdelelem(&(data->args), data->args);
// 	}
// }
