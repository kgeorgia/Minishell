/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:09:48 by kgeorgia          #+#    #+#             */
/*   Updated: 2021/09/03 17:28:56 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_c_in_child(int sig)
{
	(void)sig;
	printf("\n");
}

void	check_sl_in_child(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
}
