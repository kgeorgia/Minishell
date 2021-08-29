/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:47:10 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/29 19:29:35 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(t_all *data, t_list *tmp)
{
	pid_t	reader;
	int		fd[2];
	char	*line;
	char	*limiter;

	limiter = ft_strdup(tmp->next->content);
	ft_lstdelelem(&(data->args), tmp->next);
	ft_lstdelelem(&(data->args), tmp);
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line, 0))
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
				exit(EXIT_SUCCESS);
			// write(fd[1], line, ft_strlen(line));
			ft_putendl_fd(line, fd[1]);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(reader, NULL, 0);
	free(limiter);
}

void	open_in_file(t_all *data)
{
	int		fd;
	t_list	*tmp;

	fd = 0;
	tmp = data->args;
	while (tmp && ft_strncmp(tmp->content, "|", 2))
	{
		if (!ft_strncmp(tmp->content, "<", 2) && tmp->next)
		{
			fd = open(tmp->next->content, O_RDONLY, 0666);
			ft_lstdelelem(&(data->args), tmp->next);
			ft_lstdelelem(&(data->args), tmp);
			if (fd < 0)
			{
				ft_putendl_fd("Couldn't read from file.", 2);
				return ;
			}
			dup2(fd, 0);
			return ;
		}
		else if (!ft_strncmp(tmp->content, "<<", 2) && tmp->next)
			return (here_doc(data, tmp));
		tmp = tmp->next;
	}
}

void	open_out_file(t_all *data)
{
	int		fd;
	t_list	*tmp;

	fd = 0;
	tmp = data->args;
	while (tmp && ft_strncmp(tmp->content, "|", 2))
	{
		if (!ft_strncmp(tmp->content, ">", 2) && tmp->next)
			fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (!ft_strncmp(tmp->content, ">>", 3) && tmp->next)
			fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd > 0)
		{
			ft_lstdelelem(&(data->args), tmp->next);
			ft_lstdelelem(&(data->args), tmp);
			dup2(fd, 1);
			break ;
		}
		tmp = tmp->next;
	}
}

void	set_in(int	fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
}

void	set_out(int	fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
}
