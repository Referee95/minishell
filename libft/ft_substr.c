/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:44:35 by nel-mous          #+#    #+#             */
/*   Updated: 2023/06/20 21:16:38 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	int				j;

	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		sub = (char *)malloc (ft_strlen(s) - start + 1);
	else
		sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	while (s[start] && len--)
		sub[j++] = s[start++];
	sub[j] = '\0';
	return (sub);
}
