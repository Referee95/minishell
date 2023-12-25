/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:01:15 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/13 11:58:32 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content)
{
	if (content)
		free(content);
}

void	free_tokens(t_list *tokens)
{
	if (tokens)
		ft_lstclear(&tokens, free_token);
}

void	ft_lstdelone_(t_redir *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->f);
		free(lst);
	}
}

void	ft_lstclear_(t_redir **lst, void (*del)(void *))
{
	t_redir	*ptr;

	if (lst && del)
	{
		while (*lst)
		{
			ptr = (*lst)->next;
			ft_lstdelone_(*lst, del);
			*lst = ptr;
		}
		*lst = NULL;
	}
}

void	free_redir(t_redir *tokens)
{
	if (tokens)
		ft_lstclear_(&tokens, free_token);
}
