/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 09:21:55 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/12 21:56:06 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list	*tokens;
	t_ccmd	*cmd;
	char	*input;
	t_env	*envlist;

	(void) ac;
	(void) av;
	g_glo.exit_st = 0;
	envlist = ft_get_env(env);
	tokens = NULL;
	cmd = NULL;
	ft_signals();
	g_glo.env = envlist;
	while (1)
	{
		input = readline("\x1b[32mMinishell-3.2$\x1b[0m ");
		if (input == NULL)
			exit(g_glo.exit_st);
		add_history(input);
		tokens = lexer(input);
		cmd = parse_ccmd(tokens, g_glo.env);
		executer(cmd, &g_glo.env);
		free_all(tokens, cmd, input);
	}
	return (0);
}
