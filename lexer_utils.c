/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:59:05 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/11 12:35:13 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length_count(char *line, int *i)
{
	char	quote;
	int		len;

	len = 0;
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] != '\0' && line[*i] != quote)
		{
			(*i)++;
			len++;
		}
		if (line[*i] == quote)
			len++;
	}
	if (line[*i] != '\0')
	{
		(*i)++;
		len++;
	}
	return (len);
}

int	word_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '|' && line[i] != '>'
		&& line[i] != '<')
	{
		len += length_count(line, &i);
	}
	return (len);
}

int	inquotes_len(char *line)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '>' && line[i] != '<'
		&& line[i] != '|')
	{
		len += length_count(line, &i);
	}
	return (len);
}

int	redir_len(char *line)
{
	int	len;
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
	{
		if (ft_strncmp(line, ">", 1) == 0 || ft_strncmp(line, "<", 1) == 0)
			len = 1;
		if (ft_strncmp(line, ">>", 2) == 0 || ft_strncmp(line, "<<", 2) == 0)
			len = 2;
		i++;
	}
	return (len);
}

int	token_len(char *line)
{
	int	len;

	len = 0;
	if (*line == '"' || *line == '\'')
		len = inquotes_len(line);
	else if (*line == '|')
		len = 1;
	else if (*line == '<' || *line == '>')
		len = redir_len(line);
	else
		len = word_len(line);
	return (len);
}
