/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:35:15 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/07/12 10:35:57 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env *head)
{
	char	c;
	int		i;

	c = '"';
	head = g_glo.env;
	while (head != NULL)
	{
		i = 0;
		printf("declare -x ");
		printf("%s", head->key);
		if (head->value)
		{
			printf("=");
			printf("%c%s%c\n", c, head->value, c);
		}
		else
			printf("\n");
		head = head->next;
	}
}

void	command_export(t_env *envlist, char **str)
{
	if (len_arr(str) == 1)
		print_export(envlist);
}

int	is_builtin(char **str)
{
	if (!ft_strcmp(str[0], "echo") || !ft_strcmp(str[0], "clear")
		|| !ft_strcmp(str[0], "cd") || !ft_strcmp(str[0], "pwd")
		|| !ft_strcmp(str[0], "export") || !ft_strcmp(str[0], "unset")
		|| !ft_strcmp(str[0], "exit") || !ft_strcmp(str[0], "env"))
		return (1);
	return (0);
}

int	arg_is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}
