/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:21:04 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/09/06 17:06:33 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hello(void)
{
	printf("\033[34m");
	printf(
		"\n███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n");
	printf(
		"████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n");
	printf(
		"██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n");
	printf(
		"██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n");
	printf(
		"██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\n");
	printf(
		"╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n\n");
	printf("\033[0m");
}

void	init_all(t_all *data, int argc, char **argv, char **env)
{
	int	i;

	(void)argc;
	(void)argv;
	i = -1;
	data->env = NULL;
	data->args = NULL;
	data->argv = NULL;
	data->envp = NULL;
	while (env[++i])
		ft_lstadd_back(&(data->env), ft_lstnew(ft_strdup(env[i])));
	ft_lstadd_back(&(data->env), ft_lstnew(ft_strdup("?=0")));
	data->ret = 0;
	ft_shlvl(data);
}

// void	print_args(t_all data)
// {
// 	t_list	*tmp;

// 	tmp = data.args;
// 	while (tmp)
// 	{
// 		printf("flag %s\n", tmp->content);
// 		// ft_putendl_fd(tmp->content, 1);
// 		tmp = tmp->next;
// 	}
// }

void	del_null_args(t_all *data)
{
	t_list	*tmp;

	tmp = data->args;
	while (tmp)
	{
		if (tmp->content == NULL)
		{
			ft_lstdelelem(&(data->args), tmp);
			tmp = data->args;
			continue ;
		}
		tmp = tmp->next;
	}
}

void	clear_all(t_all *data, char *input, char *trim)
{
	dup2(data->fd_std[0], 0);
	dup2(data->fd_std[1], 1);
	ft_lstclear(&(data->args), &free);
	if (input)
		free(input);
	if (trim)
		free(trim);
}

int	main(int argc, char **argv, char **env)
{
	t_all	data;
	char	*input;
	char	*trim_input;

	ft_hello();
	init_all(&data, argc, argv, env);
	while (42)
	{
		signal(SIGINT, check_c);
		signal(SIGQUIT, SIG_IGN);
		data.fd_std[0] = dup(0);
		data.fd_std[1] = dup(1);
		input = readline("\001\033[34m\002minishell> \001\033[37m\002");
		if (!input)
			ft_exit(&data);
		add_history(input);
		trim_input = ft_strtrim(input, " ");
		if (parser(trim_input, &data))
			return (1);
		del_null_args(&data);
		if (data.args)
			executor(&data);
		clear_all(&data, input, trim_input);
	}
	return (0);
}
