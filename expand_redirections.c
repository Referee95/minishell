/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:10:56 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/11 21:32:42 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expand_redirections(t_redir *redir, t_env *envlist)
{
	char	*e_line;
	char	**res;
	char	q;
	int		i;

	i = -1;
	q = '\0';
	e_line = ft_strdup("");
	while (redir->f[++i])
	{
		if ((redir->f[i] == '\'' || redir->f[i] == '"') && !q)
			e_line = replace_quotes(e_line, redir->f, &i, &q);
		else if (redir->f[i] == q)
			q = '\0';
		else if (redir->f[i] == '$' && q == '\0' && redir->f[i + 1] != '\0')
			e_line = expand_var(e_line, redir->f, envlist, &i);
		else if (redir->f[i] == '$' && q == '"' && redir->f[i + 1] != '\0')
			e_line = expand_var_(e_line, redir->f, envlist, &i);
		else if (redir->f[i] == '$' && redir->f[i + 1] == '\0')
			e_line = join_character(e_line, redir->f[i]);
		else
			e_line = join_character(e_line, redir->f[i]);
	}
	res = ft_split(e_line, 12);
	return (free(e_line), res);
}

t_redir	*expanded_redir(t_redir *redir, t_env *envlist)
{
	t_redir	*curr;
	t_redir	*result_redir;
	char	**res;
	int		i;

	curr = redir;
	result_redir = NULL;
	while (curr)
	{
		res = expand_redirections(curr, envlist);
		i = 0;
		while (res[i] != NULL)
		{
			rediradd_back(&result_redir, ft_redirnew(res[i], curr->type));
			i++;
		}
		ft_free(res);
		curr = curr->next;
	}
	return (result_redir);
}
