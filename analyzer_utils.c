/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer__.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:02:12 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/08 21:36:27 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_last_node(t_list *tokens)
{
	t_list	*lastnode;
	t_list	*t;

	if (tokens == NULL)
		return (NULL);
	lastnode = ft_lstlast(tokens);
	t = tokens;
	while (t->next)
	{
		if (ft_strcmp(t->next->data, lastnode->data) == 0)
			return (t);
		t = t->next;
	}
	return (NULL);
}

void	remove_node(t_list **tokens, t_list *prev, t_list *node)
{
	if (prev == NULL)
		*tokens = node->next;
	else
		prev->next = node->next;
	ft_lstdelone(node, free);
}

int	remove_last_node(t_list **tokens, int *check)
{
	t_list	*lastnode;
	t_list	*prev;

	if (*tokens == NULL || tokens == NULL)
		return (0);
	lastnode = ft_lstlast(*tokens);
	prev = get_last_node(*tokens);
	if (ft_lstsize(*tokens) == 1 && ft_strchr(">|<", lastnode->data[0]))
	{
		ft_lstdelone(*tokens, free);
		*tokens = NULL;
		*check = 1;
		return (0);
	}
	if (prev != NULL && ft_strchr(">|<", lastnode->data[0]))
	{
		remove_node(tokens, prev, lastnode);
		*check = 1;
		return (1);
	}
	return (0);
}

int	check_last_node(t_list **tokens)
{
	int	check;

	check = 0;
	while (1)
	{
		if (remove_last_node(tokens, &check) == 0)
			break ;
	}
	return (check);
}
