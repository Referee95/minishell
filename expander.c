/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:25:03 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/12 13:27:03 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var_(char *exp_line, char *tok, t_env *envlist, int *i)
{
	char	*sub_line;

	if (ft_isalpha(tok[(*i) + 1]) || tok[(*i) + 1] == '_')
	{
		sub_line = ft_substr(tok, (*i) + 1, dolar_len_(tok, i));
		exp_line = expand_variable(exp_line, sub_line, envlist, 1);
		free(sub_line);
		(*i)--;
	}
	else if (tok[(*i) + 1] == '?')
	{
		(*i)++;
		exp_line = ft_strjoinfree(exp_line, ft_itoa(g_glo.exit_st), 3);
	}
	else
		(*i)++;
	return (exp_line);
}

char	*expand_var(char *exp_line, char *tok, t_env *envlist, int *i)
{
	char	*sub_line;

	if (ft_isalpha(tok[(*i) + 1]) || tok[(*i) + 1] == '_')
	{
		sub_line = ft_substr(tok, (*i) + 1, dolar_len_(tok, i));
		exp_line = expand_variable(exp_line, sub_line, envlist, 0);
		free(sub_line);
		(*i)--;
	}
	else if (tok[(*i) + 1] == '?')
	{
		(*i)++;
		exp_line = ft_strjoinfree(exp_line, ft_itoa(g_glo.exit_st), 3);
	}
	else
		(*i)++;
	return (exp_line);
}

char	*replace_quotes(char *exp_line, char *tok, int *i, char *quote)
{
	exp_line = join_character(exp_line, '\0');
	*quote = tok[*i];
	return (exp_line);
}

char	**expand(t_list *lst, t_env *envlist)
{
	char	*e_line;
	char	**res;
	char	q;
	int		i;

	i = -1;
	q = '\0';
	e_line = ft_strdup("");
	while (lst->data[++i])
	{
		if ((lst->data[i] == '\'' || lst->data[i] == '"') && !q)
			e_line = replace_quotes(e_line, lst->data, &i, &q);
		else if (lst->data[i] == q)
			q = '\0';
		else if (lst->data[i] == '$' && q == '\0' && lst->data[i + 1] != '\0')
			e_line = expand_var(e_line, lst->data, envlist, &i);
		else if (lst->data[i] == '$' && q == '"' && lst->data[i + 1] != '\0')
			e_line = expand_var_(e_line, lst->data, envlist, &i);
		else if (lst->data[i] == '$' && lst->data[i + 1] == '\0')
			e_line = join_character(e_line, lst->data[i]);
		else
			e_line = join_character(e_line, lst->data[i]);
	}
	res = ft_split(e_line, 12);
	return (free(e_line), res);
}

t_list	*expanded_list(t_list *lst, t_env *envlist)
{
	t_list	*curr;
	t_list	*result_list;
	char	**res;
	int		i;

	curr = lst;
	result_list = NULL;
	while (curr)
	{
		res = expand(curr, envlist);
		i = 0;
		while (res[i] != NULL)
		{
			ft_lstadd_back(&result_list, ft_lstnew(res[i]));
			i++;
		}
		ft_free(res);
		curr = curr->next;
	}
	return (result_list);
}
