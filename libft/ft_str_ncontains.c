/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_contains.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:23:31 by mbouthai          #+#    #+#             */
/*   Updated: 2022/09/21 19:25:47 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_ncontains(int c, int times, char *str)
{
	int	index;
	int	result;

	if (!str)
		return (0);
	index = -1;
	result = 0;
	while (str[++index])
	{
		if (str[index] == c)
			result++;
		if (result >= times)
			return (1);
	}
	return (0);
}
