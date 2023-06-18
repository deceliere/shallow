/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdecelie <rdecelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:32:50 by rdecelie          #+#    #+#             */
/*   Updated: 2022/12/08 14:42:04 by rdecelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	if (!n)
	{
		len = 1;
		return (len);
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	int			len;
	char		*str;

	nbr = n;
	len = ft_nbrlen(nbr);
	if (nbr < 0)
	{
		len ++;
		nbr *= -1;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	while (len)
	{
		str[len-- - 1] = (nbr % 10) + 48;
		nbr /= 10;
	}
	if (n < 0)
		str[len] = 45;
	return (str);
}
