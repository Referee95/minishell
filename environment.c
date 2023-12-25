/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:39:57 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/12 11:34:50 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *env)
{
	char	*delimiter;
	char	*name;
	int		l_env_var;

	delimiter = ft_strchr(env, '=');
	if (delimiter)
		l_env_var = delimiter - env;
	else
		l_env_var = ft_strlen(env);
	name = (char *)malloc((l_env_var + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_strncpy(name, env, l_env_var);
	name[l_env_var] = '\0';
	return (name);
}

char	*get_value(char *env)
{
	char	*delimiter;

	delimiter = ft_strchr(env, '=');
	if (delimiter == NULL)
		return (NULL);
	return (ft_strdup(delimiter + 1));
}

t_env	*ft_envnew(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_envadd_back(t_env **envlist, t_env *new)
{
	t_env	*ptr;

	ptr = *envlist;
	if (!*envlist)
		*envlist = new;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_env	*ft_get_env(char **env)
{
	int		i;
	t_env	*envlist;
	t_env	*node;
	char	*key;
	char	*value;

	i = 0;
	envlist = NULL;
	while (env[i])
	{
		key = get_key(env[i]);
		value = get_value(env[i]);
		node = ft_envnew(key, value);
		ft_envadd_back(&envlist, node);
		i++;
	}
	return (envlist);
}
