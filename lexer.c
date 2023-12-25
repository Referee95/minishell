/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:59:03 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/11 22:13:58 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_token(char *line)
{
	t_list	*node;
	char	*token;
	int		len;

	len = token_len(line);
	token = ft_substr(line, 0, len);
	node = ft_lstnew(token);
	free(token);
	return (node);
}

t_list	*fill_list(char *line, t_list *tokens, int *i, int *err)
{
	t_list	*token;

	while (line[*i] != '\0')
	{
		token = create_token(&line[*i]);
		if (analyzer(tokens, token->data))
		{
			free_tokens(token);
			*err = 1;
			printf("syntax error\n");
			free_tokens(tokens);
			return (NULL);
			break ;
		}
		ft_lstadd_back(&tokens, token);
		(*i) += ft_strlen(token->data);
		while (line[*i] == ' ' || line[*i] == '\t')
			(*i)++;
	}
	return (tokens);
}

int	syntax_err(t_list **tokens, int *err)
{
	if (tokens)
	{
		if (check_last_node(tokens))
		{
			if (*err == 0)
			{
				free_tokens(*tokens);
				printf("syntax error near token\n");
				return (0);
			}
		}
	}
	return (1);
}

t_list	*lexer(char *line)
{
	t_list	*tokens;
	int		i;
	int		err;

	i = 0;
	err = 0;
	tokens = NULL;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	tokens = fill_list(line, tokens, &i, &err);
	if (syntax_err(&tokens, &err) == 0)
		return (NULL);
	return (tokens);
}
