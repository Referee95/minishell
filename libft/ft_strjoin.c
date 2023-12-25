/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:41:56 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/08 20:09:05 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2)+1);
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[++j])
		new[i++] = s2[j];
	new[i] = '\0';
	return (new);
}

char	*ft_strjoinfree(char *s1, char *s2, int flag)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (flag == 1)
		free(s1);
	if (flag == 2)
		free(s2);
	if (flag == 3)
	{
		free(s1);
		free(s2);
	}
	return (ret);
}
