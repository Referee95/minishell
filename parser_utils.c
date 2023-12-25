/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:11:32 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/11 21:39:43 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_redirnew(char *content, enum e_type type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->f = ft_strdup(content);
	new->type = type;
	new->next = NULL;
	return (new);
}

void	rediradd_back(t_redir **lst, t_redir *new)
{
	t_redir	*ptr;

	ptr = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

int	num_scmds(t_list *tokens)
{
	int	count_cmds;

	count_cmds = 0;
	while (tokens)
	{
		if (ft_strcmp(tokens->data, "|") == 0)
			count_cmds++;
		tokens = tokens->next;
	}
	count_cmds++;
	return (count_cmds);
}

char	*remove_quotes(char *str)
{
	char	quote;
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = '\0';
	dst = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				dst[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			dst[j++] = str[i++];
	}
	dst[j] = '\0';
	return (dst);
}
