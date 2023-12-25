/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:24:44 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/13 12:01:11 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_ccmd *cmd, t_list *tokens)
{
	int	i;

	i = 0;
	if (num_scmds(tokens) == 1)
	{
		free_tokens(cmd->simple_command->words);
		free_redir(cmd->simple_command->redirs);
		free(cmd->simple_command);
	}
	else
	{
		while (i < num_scmds(tokens))
		{
			free_tokens(cmd->compound_command[i]->words);
			free_redir(cmd->compound_command[i]->redirs);
			free(cmd->compound_command[i]);
			i++;
		}
		free(cmd->compound_command);
	}
}

void	ft_free(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_free_env(t_env *cur)
{
	free(cur->key);
	free(cur->value);
	free(cur);
}

void	free_env(void)
{
	free(g_glo.env->key);
	free(g_glo.env->value);
	free(g_glo.env);
}

void	free_all(t_list *tokens, t_ccmd *cmd, char *input)
{
	free_cmd(cmd, tokens);
	free(input);
	free_tokens(tokens);
	free(cmd);
}
