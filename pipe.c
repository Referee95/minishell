/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:09:45 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/07/08 20:10:18 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_cmd(int *p1, int *p2)
{
	dup2(p1[1], 1);
	close(p1[0]);
	close(p2[0]);
	close(p2[1]);
}

void	in_two_pipe(int *p1, int *p2)
{
	dup2(p1[0], 0);
	dup2(p2[1], 1);
	close(p2[0]);
	close(p1[1]);
}

void	in_two_pipe2(int *p1, int *p2)
{
	dup2(p2[0], 0);
	dup2(p1[1], 1);
	close(p2[1]);
	close(p1[0]);
}

void	last_pipe(int *p1, int *p2)
{
	dup2(p2[0], 0);
	close(p2[1]);
	close(p1[0]);
	close(p1[1]);
}

void	last_pipe2(int *p1, int *p2)
{
	dup2(p1[0], 0);
	close(p2[1]);
	close(p2[0]);
	close(p1[1]);
}
