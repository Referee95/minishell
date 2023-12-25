/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:41:33 by nel-mous          #+#    #+#             */
/*   Updated: 2023/06/20 21:15:44 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *S1, const char *S2)
{
	size_t	i;

	i = 0;
	while ((S1[i] || S2[i]))
	{
		if (S1[i] != S2[i])
			return ((unsigned char)S1[i] - (unsigned char)S2[i]);
		else
			i++;
	}
	return (0);
}
