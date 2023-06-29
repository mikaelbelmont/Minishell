/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:47:34 by francsan          #+#    #+#             */
/*   Updated: 2023/06/15 18:47:38 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_itoa(char *str, int *maxdig, int count, int n)
{
	*maxdig = count;
	if (n > 9 || n < -9)
		str = ft_itoa(str, maxdig, (count + 1), (n / 10));
	if (!str)
	{
		str = ft_calloc(count + 1 + (n < 0), 1);
		if (!str)
			return (NULL);
		if (n < 0)
			str[0] = '-';
		str[count + (n < 0)] = 0;
	}
	str[*maxdig - count + (n < 0)] = (n % 10) * ((n > 0) - (n < 0)) + 48;
	return (str);
}
