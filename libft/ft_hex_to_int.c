/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:58:29 by mbouthai          #+#    #+#             */
/*   Updated: 2022/09/21 19:19:33 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hex_value(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

static int	ft_power(int n, int p)
{
	if (p < 0)
		return (0);
	else if (p == 0)
		return (1);
	else if (p == 1)
		return (n);
	return (n * ft_power(n, p - 1));
}

int	ft_hex_to_int(char *hex)
{
	int	result;
	int	index;
	int	length;
	int	count;

	if (!hex)
		return (0);
	result = 0;
	index = 0;
	length = ft_strlen(hex);
	count = length;
	while (hex[index++] <= ' ')
		count--;
	if (index + 2 < count && hex[index] == '0'
		&& (hex[index] == 'x' || hex[index + 1] == 'X'))
		count -= 2;
	index = 0;
	while (--count >= 0)
	{
		if (!(hex[--length] <= 32))
			result += ft_power(16, index++) * ft_hex_value(hex[length]);
	}
	return (result);
}
