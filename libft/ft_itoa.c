/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhalil- <ykhalil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:23:02 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/09 16:10:19 by ykhalil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbofdigits(long int n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*s;
	int			len;
	long int	nbr;

	nbr = (long int) n;
	len = nbofdigits(nbr);
	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (nbr == 0)
		s[0] = nbr + '0';
	if (nbr < 0)
	{
		s[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		s[len - 1] = nbr % 10 + '0';
		nbr /= 10;
		len --;
	}
	return (s);
}
