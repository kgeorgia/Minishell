/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 17:00:22 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/08/22 17:46:07 by kgeorgia         ###   ########.fr       */
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

typedef struct s_all
{
	t_list			*env;
	t_list			*args;
	int				wr_rd_flag;
}					t_all;

/*
** Parser
*/

int		parser(char *input, t_all *data);
int		quot_marks(char *input, int *start, int *end);
int		check_redirect(char *input, int *start, int *end);

/*
** Parser utils
*/

char	*find_key(char *str);
t_list	*ft_lstmap_env(t_list *lst, char *(*f)(char *, t_all *data),
			void (*del)(void *), t_all *data);
int		get_env(t_all *data, char *key, char **value);
int		set_env(t_all *data, char *key, char *value);
char	*add_symbol(char *str, char c);

/*
** Replace_env
*/

int		replace_dollar(char *cont, char **res, int *i, t_all *data);
void	replace_env_in_quot(char *cont, char **res, int *i, t_all *data);
char	*skip_quotes(char *content);
char	*replace_env(char *cont, t_all *data);
void	parser_replace_env(t_all *data);

/*
** Executor
*/

int		count_pipes(t_list *list, int ***fds);
void	init_wr_rd_flag(t_all *data, int i, int count_pipe);
int		executor(t_all *data);

/*
** Check buitins
*/

int		find_redirect(t_all *data, int **fds);
int		check_builtins(t_all *data, int **fds);

/*
** Check bin
*/

char	**split_path(t_all *data);
char	*search_in_dir(DIR **d, char *str, char *path);
int		search_command(t_all *data, char **cmd);
char	**copy_args(t_all *data);
int		check_bin(t_all *data, int **fds);

/*
** Ft_builtins
*/

void	ft_cd(t_all *data);
void	ft_echo(t_all *data);
void	ft_env(t_all *data);
void	ft_export(t_all *data);
void	ft_unset(t_all *data);

/*
** Executor utils
*/

void	free_matrix(void **matrix);
char	**parse_env(char *str);
int		env_is_valid(char *str);
void	ft_lstdelelem(t_list **lst, t_list *del);
char	**copy_env(t_all *data);

#endif