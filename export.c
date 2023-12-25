/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:43:20 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/07/13 15:34:18 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_env *envlist, t_env *node, char *key, char *value)
{
	t_env	*head;

	head = envlist;
	while (head)
	{
		if (!ft_strcmp(head->key, key))
		{
			free(key);
			break ;
		}
		head = head->next;
		if (!head)
		{
			node = ft_envnew(key, value);
			ft_envadd_back(&envlist, node);
		}
	}
}

void	ft_export2(t_env *envlist, t_env *node, char *key, char *value)
{
	t_env	*head;

	head = envlist;
	while (head && ft_strcmp(key, head->key) != 0)
		head = head->next;
	if (head && !ft_strcmp(key, head->key))
	{
		free(key);
		free(head->value);
		head->value = value;
	}
	else if (!head)
	{
		node = ft_envnew(key, value);
		ft_envadd_back(&envlist, node);
	}
}

int	check_key(char *str)
{
	int	i;

	i = 0;
	str = get_key(str);
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		free(str);
		return (1);
	}
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			free(str);
			return (1);
		}
	}
	free(str);
	return (0);
}

void	key_no_valid(char **str, int *i)
{
	while (str[*i] && check_key(str[*i]))
	{
		printf("minishell: %s : `%s': not a valid identifier\n", str[0],
			str[*i]);
		(*i)++;
	}
}

void	c_export(t_env *envlist, char **str)
{
	char	*key;
	char	*value;
	t_env	*node;
	t_env	*head;
	int		i;

	i = 0;
	head = envlist;
	node = NULL;
	command_export(envlist, str);
	if (len_arr(str) > 1)
	{
		while (str[++i])
		{
			key_no_valid(str, &i);
			if (str[i] == '\0')
				break ;
			key = get_key(str[i]);
			value = get_value(str[i]);
			if (str[i] && value == NULL)
				ft_export(envlist, node, key, value);
			else if (str[i] && value != NULL)
				ft_export2(envlist, node, key, value);
		}
	}
}
