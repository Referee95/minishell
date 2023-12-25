/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:52:44 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/07/13 12:06:46 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_redirs(t_redir *head)
{
	t_redir	*tmp;

	tmp = head;
	while (head)
	{
		free(head->f);
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

char	**lst_to_str(t_list *lst)
{
	t_list	*cur;
	int		i;
	char	**str;

	i = 0;
	cur = lst;
	str = malloc(sizeof(char *) * (ft_lstsize(cur) + 1));
	while (cur)
	{
		str[i] = ft_strdup(cur->data);
		i++;
		cur = cur->next;
	}
	str[i] = NULL;
	return (str);
}

int	b_setup_redirections(t_redir *head)
{
	int	fd;

	while (head)
	{
		if (head->type == OUT)
		{
			fd = open(head->f, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(fd, 1);
		}
		if (head->type == IN)
		{
			fd = open(head->f, O_RDONLY, 0644);
			if (fd == -1)
				return (perror("minishell"), 1);
			dup2(fd, 0);
		}
		if (head->type == APPEND)
		{
			fd = open(head->f, O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(fd, 1);
		}
		head = head->next;
	}
	return (0);
}

int	setup_redirections(t_redir *redir, t_env *env)
{
	t_redir	*head;
	int		ret;

	ret = 0;
	head = expanded_redir(redir, env);
	if (!redir)
		return (0);
	ret = b_setup_redirections(head);
	free_all_redirs(head);
	return (ret);
}

char	**setup_cmd_arguments(t_list *lst, t_env *cur)
{
	char	**str;
	t_list	*temp_list;

	temp_list = expanded_list(lst, cur);
	str = lst_to_str(temp_list);
	free_tokens(temp_list);
	return (str);
}
