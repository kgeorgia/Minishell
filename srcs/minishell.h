/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:45:11 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/09/06 13:50:31 by kgeorgia         ###   ########.fr       */
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
# include "../libft/libft.h"
# include "../readline/history.h"
# include "../readline/readline.h"

typedef struct s_all
{
	t_list			*env;
	t_list			*args;
	char			**argv;
	char			**envp;
	int				ret;
	int				fd_std[2];
}					t_all;

void	print_args(t_all data);

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

int		count_pipes(t_list *list);
void	child_process(t_all *data);
void	exec_cmd(t_all *data);
int		executor(t_all *data);

/*
** Check command
*/

char	**split_path(t_all *data);
char	*search_in_dir(DIR **d, char *str, char *path);
int		search_command(t_all *data, char **cmd);
int		check_builtins(t_all *data);
int		check_bin(t_all *data);

/*
** Ft_builtins
*/

void	ft_cd(t_all *data);
void	ft_echo(t_all *data);
void	ft_env(t_all *data);
void	ft_export(t_all *data);
void	ft_unset(t_all *data);
void	ft_exit(t_all *data);
void	blt_error(char *cmd, char *arg, char *err);

/*
** Executor utils
*/

void	free_matrix(void **matrix);
char	**parse_env(char *str);
int		env_is_valid(char *str);
void	ft_lstdelelem(t_list **lst, t_list *del);
void	ft_shlvl(t_all *data);

/*
** Executor utils 2
*/

void	error(t_all *data);
char	**copy_env(t_all *data);
char	**copy_args(t_all *data);
char	*ret_first_or_last(t_list *lst, int first_last);
void	show_sort_env(t_all *data);

/*
** Redirect
*/

void	here_doc(t_all *data, t_list *tmp);
void	open_in_file(t_all *data);
void	open_out_file(t_all *data);
void	set_in(int	fd[2]);
void	set_out(int	fd[2]);

/*
** Signals
*/

void	check_c(int sig);
void	check_c_in_child(int sig);
void	check_sl_in_child(int sig);

#endif