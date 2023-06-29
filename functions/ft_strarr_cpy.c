/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:55:56 by francisco         #+#    #+#             */
/*   Updated: 2023/04/26 09:58:10 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**ft_strarr_copy(char **arr)
{
	char	**dst;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	dst = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (arr[++i])
		dst[i] = ft_strdup(arr[i]);
	return (dst);
}
