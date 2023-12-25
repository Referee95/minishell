/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:48:06 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/13 11:51:24 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_str(t_env *env)
{
	t_env	*cur;
	int		i;
	char	**str;
	int		len;

	i = 0;
	cur = env;
	len = 0;
	while (env != NULL)
	{
		len++;
		env = env->next;
	}
	str = malloc(sizeof(char *) * (len + 1));
	while (cur)
	{
		str[i] = ft_strdup(cur->key);
		str[i] = ft_strjoinfree(str[i], "=", 1);
		str[i] = ft_strjoinfree(str[i], cur->value, 1);
		i++;
		cur = cur->next;
	}
	str[i] = NULL;
	return (str);
}

int	set_exit_status(int n)
{
	unsigned char	*s;

	s = (unsigned char *)&n;
	if (s[0])
		return (s[0] + 128);
	return (s[1]);
}

void	executer(t_ccmd *cmd, t_env **envlist)
{
	t_env	*cur;
	int		exit_sts;
	int		j;
	int		i;

	j = -1;
	i = -1;
	cur = *envlist;
	if (cmd->type == SIMPLE_CMD)
		exit_sts = execute_simple(cmd->simple_command, cur);
	else
		exit_sts = execute_cmp(cmd, cur, j, i);
	g_glo.exit_st = set_exit_status(exit_sts);
}

int	execute_cmd(t_scmd *cmd, t_env *cur)
{
	char	**str;

	str = setup_cmd_arguments(cmd->words, cur);
	if (setup_redirections(cmd->redirs, cur))
		exit(1);
	if (*str && is_builtin(str))
	{
		execute_builtins(str, cur);
		exit(0);
	}
	if (execve(get_path(str, cur), str, NULL) == -1)
	{
		print_error("minishell: ", str[0], ": command not found\n ");
		ft_free(str);
		exit(127);
	}
	return (0);
}

int	ft_builtin(t_scmd *cmd, t_env *cur, char **str)
{
	int	stdout;
	int	stdin;

	stdout = dup(1);
	stdin = dup(0);
	if (setup_redirections(cmd->redirs, cur))
	{
		ft_free(str);
		return (1);
	}
	execute_builtins(str, cur);
	dup2(stdin, 0);
	dup2(stdout, 1);
	return (0);
}
