/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:01:20 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/12 12:55:23 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_case1(char *exp_line, char *tok, int *i, char *quote)
{
	exp_line = join_character(exp_line, tok[*i]);
	*quote = tok[*i];
	return (exp_line);
}

char	*heredoc_case2(char *exp_line, char *tok, int *i, char *quote)
{
	exp_line = join_character(exp_line, tok[*i]);
	*quote = '\0';
	return (exp_line);
}

char	*expand_v_(char *exp_line, char *tok, t_env *envlist, int *i)
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

char	*expand_heredoc(char *tok, t_env *envlist)
{
	char	*e_line;
	char	quote;
	int		i;

	i = -1;
	quote = '\0';
	e_line = ft_strdup("");
	while (tok[++i])
	{
		if ((tok[i] == '\'' || tok[i] == '"') && !quote)
			e_line = heredoc_case1(e_line, tok, &i, &quote);
		else if (tok[i] == quote)
			e_line = heredoc_case2(e_line, tok, &i, &quote);
		else if (tok[i] == '$' && tok[i + 1] != '\0')
			e_line = expand_v_(e_line, tok, envlist, &i);
		else if (tok[i] == '$' && tok[i + 1] == '\0')
			e_line = join_character(e_line, tok[i]);
		else
			e_line = join_character(e_line, tok[i]);
	}
	return (e_line);
}
