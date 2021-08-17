/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:21:04 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/17 16:10:52 by kgeorgia         ###   ########.fr       */
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

void	init_env(t_all *data, int argc, char **argv, char **env)
{
	int	i;

	(void)argc;
	(void)argv;
	i = -1;
	while (env[++i])
		ft_lstadd_back(&(data->env), ft_lstnew(ft_strdup(env[i])));
}

void	print_args(t_all data)
{
	t_list	*tmp;

	tmp = data.args;
	while (tmp)
	{
		ft_putendl_fd(tmp->content, 1);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_all	data;
	char	*input;

	ft_hello();
	init_env(&data, argc, argv, env);
	while (1)
	{
		input = readline("\033[34mminishell> \033[0m");
		add_history(input);
		if (parser(input, &data))
			return (1);
		//executor(&data);
		print_args(data);
		ft_lstclear(&(data.args), &free);
		free(input);
	}
	return (0);
}
