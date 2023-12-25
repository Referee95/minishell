/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:10:20 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/13 14:50:01 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_helper(char *line, t_env *envlist)
{
	char	*tmp;

	tmp = line;
	line = expand_heredoc(line, envlist);
	free(tmp);
	return (line);
}

int	read_heredoc(char *delimiter, t_env *envlist, int expand)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit(1);
	delimiter = remove_quotes(delimiter);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
			break ;
		if (expand == TRUE)
			line = heredoc_helper(line, envlist);
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	signal(SIGINT, handle_ctrl_c);
	free(delimiter);
	close(pipefd[1]);
	return (free(line), pipefd[0]);
}

void	setup_heredoc(char *delimiter, t_scmd *scmd, t_env *envlist)
{
	int		expand;
	pid_t	child;

	if (scmd->fd)
		close(scmd->fd);
	expand = TRUE;
	if (ft_strchr(delimiter, '\"') || ft_strchr(delimiter, '\''))
		expand = FALSE;
	child = fork();
	if (child == 0)
	{
		scmd->fd = read_heredoc(delimiter, envlist, expand);
	}
	else
	{
		waitpid(child, &g_glo.exit_st, 0);
		if (!WIFSIGNALED(g_glo.exit_st))
			exit(0);
	}
}
