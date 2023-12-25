/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:40:45 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/13 15:33:45 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_utils(char *str, t_env *cur, t_env *prev)
{
	while (cur != NULL)
	{
		if (!ft_strcmp(str, cur->key))
		{
			if (prev == NULL)
			{
				cur = g_glo.env->next;
				free_env();
				g_glo.env = cur;
				return ;
			}
			else
			{
				prev->next = cur->next;
				ft_free_env(cur);
				cur = prev->next;
			}
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	ft_remove(char *str)
{
	t_env	*cur;
	t_env	*prev;

	cur = g_glo.env;
	prev = NULL;
	remove_utils(str, cur, prev);
}

int	ft_handler_unset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	print_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}

int	len_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
