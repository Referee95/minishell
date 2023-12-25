/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:35:07 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/12 13:06:11 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dolar_len_(char *str, int *i)
{
	int	len;

	len = 0;
	(*i)++;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '\"'
		&& str[*i] != '$' && str[*i] != '-' && str[*i] != '@'
		&& str[*i] != '?' && str[*i] != '.')
	{
		(*i)++;
		len++;
	}
	return (len);
}

char	*join_character(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(ft_strlen(str) + 2);
	if (!new_str)
		return (free(str), NULL);
	if (str == NULL)
	{
		new_str[0] = c;
		new_str[1] = '\0';
	}
	if (c == '\0')
		return (free(new_str), str);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (free(str), new_str);
}

char	*rmv_space(char *value)
{
	char	*t_value;
	char	*new_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	t_value = ft_strtrim(value, " ");
	new_value = malloc(ft_strlen(t_value) + 1);
	if (!new_value)
		return (free(t_value), NULL);
	while (t_value[i] != '\0')
	{
		if (t_value[i] == ' ')
		{
			if (t_value[i - 1] != ' ')
				new_value[j++] = t_value[i];
		}
		else
			new_value[j++] = t_value[i];
		i++;
	}
	new_value[j] = '\0';
	return (free(value), free(t_value), new_value);
}

char	*replace_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = 12;
		i++;
	}
	return (str);
}

char	*expand_variable(char *exp_line, char *sub_line, t_env *envlist,
		int check)
{
	t_env	*curr;
	char	*new_value;

	new_value = NULL;
	curr = envlist;
	while (curr)
	{
		if (ft_strcmp(curr->key, sub_line) == 0)
		{
			if (curr->value == NULL)
				break ;
			new_value = malloc(ft_strlen(curr->value) + 1);
			if (!new_value)
				return (NULL);
			ft_strcpy(new_value, curr->value);
			if (check == 0)
				exp_line = ft_strjoinfree(exp_line,
						replace_space(rmv_space(new_value)), 3);
			else
				exp_line = ft_strjoinfree(exp_line, new_value, 3);
		}
		curr = curr->next;
	}
	return (exp_line);
}
