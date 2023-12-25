/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:41:52 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/07/13 12:37:30 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_v_p(t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (!ft_strcmp(head->key, "PATH"))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

char	**valid_path(char *str, t_env *env, char **path)
{
	if (ft_strchr(str, '/'))
	{
		if (access(str, R_OK) != 0)
		{
			print_error("minishell: ", str, ": No such file or directory\n");
			exit(127);
		}
	}
	path = ft_split(get_v_p(env), ':');
	if (path == NULL)
	{
		print_error("minishell: ", str, ": command not found\n");
		exit(127);
	}
	return (path);
}

char	*get_path(char **str, t_env *env)
{
	int			i;
	char		**path;
	struct stat	file_info;
	char		*new_path;

	new_path = NULL;
	path = NULL;
	path = valid_path(str[0], env, path);
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i] && !ft_strchr(str[0], '/'))
	{
		new_path = ft_strjoinfree(ft_strjoin(path[i], "/"), str[0], 1);
		if (stat(new_path, &file_info) == 0)
			return (new_path);
		free(new_path);
		new_path = NULL;
		i++;
	}
	free(new_path);
	ft_free(path);
	return (str[0]);
}
