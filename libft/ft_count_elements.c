/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:28:16 by mbouthai          #+#    #+#             */
/*   Updated: 2022/09/22 00:29:54 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_elements(int c, char *str)
{
	int	index;
	int	result;

	if (!str)
		return (0);
	index = 0;
	result = 0;
	while (str[index])
	{
		if (str[index] == c)
			result++;
		index++;
	}
	return (result);
}
