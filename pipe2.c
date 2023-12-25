/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:16:06 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/07/12 09:36:48 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(int i, int *p1, int *p2, int num)
{
	if (i == 0)
		first_cmd(p1, p2);
	else if (i % 2 && i != num - 1)
		in_two_pipe(p1, p2);
	else if (i % 2 == 0 && i != num - 1)
		in_two_pipe2(p1, p2);
	else if (i % 2 == 0 && i == num - 1)
		last_pipe(p1, p2);
	else if (i % 2 && i == num - 1)
		last_pipe2(p1, p2);
}

void	create_pipe(int i, int *p1, int *p2)
{
	if (i % 2)
	{
		close(p1[1]);
		close(p1[0]);
		pipe(p1);
	}
	else if (i % 2 == 0)
	{
		close(p2[1]);
		close(p2[0]);
		pipe(p2);
	}
}

void	c_pipe(int p1[2], int p2[2])
{
	pipe(p1);
	pipe(p2);
}

void	close_p(int *p1, int *p2)
{
	close(p1[1]);
	close(p1[0]);
	close(p2[0]);
	close(p2[1]);
}
