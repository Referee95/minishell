/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:04:53 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/07/13 09:04:48 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_newline(char *str)
{
	int	i;
	int	count;

	count = 0;
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			count++;
		else
			count = -1;
		i++;
	}
	if (count >= 1)
		return (1);
	return (0);
}

void	print_space(char **str, int i)
{
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

void	c_echo(char **str)
{
	int	i;

	i = 0;
	if (!ft_strcmp("echo", str[0]) && str[i + 1] == NULL)
		printf("\n");
	else if (!ft_strcmp("echo", str[0]) && check_newline(str[1]) == 1)
	{
		i = 2;
		while (str[i] && check_newline(str[i]) == 1)
			i++;
		print_space(str, i);
	}
	else if (!ft_strcmp("echo", str[0]) && check_newline(str[1]) == 0)
	{
		i = 1;
		print_space(str, i);
		printf("\n");
	}
}
