/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:35:29 by nel-mous          #+#    #+#             */
/*   Updated: 2023/06/20 21:15:11 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbofwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static int	len_word(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		n;
	int		x;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	n = nbofwords(s, c);
	arr = (char **)malloc(sizeof(char *) * (n + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (j < n)
	{
		while (s[i] == c)
			i++;
		x = len_word(s, c, i);
		arr[j] = ft_substr(s, i, x);
		i += x;
		j++;
	}
	arr[j] = 0;
	return (arr);
}
