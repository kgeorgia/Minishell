/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 17:00:22 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/15 18:24:41 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define NO_WR_RD 0
# define WRITE	1
# define WR_RD 2
# define READ 3

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_all
{
	t_list			*env;
	t_list			*args;
	int				wr_rd_flag;
}					t_all;

#endif