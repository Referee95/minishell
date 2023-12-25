/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:11:14 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/08 21:40:23 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_list *tokens, t_scmd *scmd, t_env *envlist)
{
	if (ft_strcmp(tokens->data, ">") == 0)
	{
		tokens = tokens->next;
		rediradd_back(&scmd->redirs, ft_redirnew(tokens->data, OUT));
	}
	else if (ft_strcmp(tokens->data, "<") == 0)
	{
		tokens = tokens->next;
		rediradd_back(&scmd->redirs, ft_redirnew(tokens->data, IN));
	}
	else if (ft_strcmp(tokens->data, ">>") == 0)
	{
		tokens = tokens->next;
		rediradd_back(&scmd->redirs, ft_redirnew(tokens->data, APPEND));
	}
	if (ft_strcmp(tokens->data, "<<") == 0)
	{
		tokens = tokens->next;
		setup_heredoc(tokens->data, scmd, envlist);
	}
}

t_scmd	*parse(t_list *tokens, t_scmd *scmd, t_env *envlist)
{
	while (tokens)
	{
		if (ft_strchr("><", tokens->data[0]) || ft_strcmp(tokens->data,
				">>") == 0 || ft_strcmp(tokens->data, "<<") == 0)
		{
			parsing(tokens, scmd, envlist);
			tokens = tokens->next;
		}
		else if (ft_strcmp(tokens->data, "|") == 0)
			break ;
		else
			ft_lstadd_back(&scmd->words, ft_lstnew(tokens->data));
		tokens = tokens->next;
	}
	return (scmd);
}

t_scmd	*parse_scmd(t_list *tokens, t_env *envlist)
{
	t_scmd	*scmd;

	scmd = malloc(sizeof(t_scmd));
	scmd->fd = 0;
	scmd->redirs = NULL;
	scmd->words = NULL;
	scmd = parse(tokens, scmd, envlist);
	return (scmd);
}

t_scmd	**parse_compound_cmds(t_list *tokens, int num_cmds, t_env *envlist)
{
	int		i;
	t_scmd	**cmds;

	i = 0;
	cmds = malloc(sizeof(t_scmd *) * num_cmds);
	if (!cmds)
		return (NULL);
	while (i < num_cmds && tokens)
	{
		cmds[i] = parse_scmd(tokens, envlist);
		i++;
		while (tokens && ft_strcmp(tokens->data, "|") != 0)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	return (cmds);
}

t_ccmd	*parse_ccmd(t_list *tokens, t_env *envlist)
{
	t_ccmd	*ccmd;

	ccmd = malloc(sizeof(t_ccmd));
	if (!ccmd)
		return (NULL);
	ccmd->num_scmds = num_scmds(tokens);
	if (ccmd->num_scmds == 1)
	{
		ccmd->type = SIMPLE_CMD;
		ccmd->simple_command = parse_scmd(tokens, envlist);
	}
	else if (ccmd->num_scmds > 1)
	{
		ccmd->type = COMPOUND_CMD;
		ccmd->compound_command = parse_compound_cmds(tokens,
				ccmd->num_scmds, envlist);
	}
	return (ccmd);
}
