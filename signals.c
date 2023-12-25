/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:19:51 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/11 22:24:19 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int sig_num)
{
	(void)sig_num;
	write(2, "\n", 1);
	rl_clear_history();
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	signal(SIGINT, handle_ctrl_c);
}

void	ft_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_ctrl_c);
}
