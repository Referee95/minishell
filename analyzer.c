/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:46:19 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/08 21:36:42 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	analyze_redir(t_list *tokens, char *tok)
{
	t_list	*lastnode;

	if (tokens == NULL)
		return (0);
	lastnode = ft_lstlast(tokens);
	if (tokens != NULL)
	{
		if (ft_strchr("|><", tok[0]))
			if (ft_strchr("><", lastnode->data[0]))
				return (1);
		if (ft_strchr("|", tok[0]))
			if (ft_strchr("|><", lastnode->data[0]))
				return (1);
	}
	return (0);
}

int	check_pipe_errors(t_list *tokens)
{
	if (tokens == NULL)
		return (1);
	return (0);
}

int	check_pipe(t_list *tokens, char *tok)
{
	int	err;

	err = 0;
	if (ft_strcmp(tok, "|") == 0)
		err = check_pipe_errors(tokens);
	if (err == 1)
		return (1);
	return (0);
}

int	check_quotes(char *token)
{
	int		quote_count;
	char	quote;
	char	*search;
	int		i;

	i = 0;
	quote_count = 0;
	while (token[i] != '\0' && token[i] != ' ' && token[i] != '\t')
	{
		if (token[i] == '"' || token[i] == '\'')
		{
			quote = token[i];
			i++;
			search = ft_strchr(&token[i], quote);
			if (!search)
				return (1);
			i += search - &token[i];
		}
		i++;
	}
	return (0);
}

int	analyzer(t_list *tokens, char *token)
{
	if (check_pipe(tokens, token))
		return (1);
	if (check_quotes(token))
		return (1);
	if (analyze_redir(tokens, token))
		return (1);
	return (0);
}
