/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:17:08 by francisco         #+#    #+#             */
/*   Updated: 2023/05/03 16:03:01 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_quote(t_ints *n, char *line, char quote)
{
	n->j++;
	if (!line[n->j])
		return (1);
	while (line[n->j] && line[n->j] != quote)
	{
		if (quote == '"' && line[n->j] == '\\')
			n->j += 2;
		else
			n->j++;
	}
	if (!line[n->j] && line[n->j - 1] != quote)
		return (1);
	n->j++;
	return (0);
}

int	check_command(t_ints *n, char *line)
{
	while (line[n->j] && line[n->j] != ' ')
	{
		if (line[n->j] == '\'')
		{
			if (check_quote(n, line, '\''))
				return (1);
		}
		else if (line[n->j] == '"')
		{
			if (check_quote(n, line, '"'))
				return (1);
		}
		else
			n->j++;
	}
	while (line[n->j] && line[n->j + 1] == ' ')
		n->j++;
	return (0);
}

void	get_quote_len(t_ints *n, char *line, char quote)
{
	n->j++;
	while (line[n->j] && line[n->j] != quote)
	{
		if (quote == '"' && line[n->j] == '\\')
				n->j += 2;
		else
			n->j++;
	}
	n->j++;
}

void	get_quote(t_ints *n, char ***tokens, char *line, char quote)
{
	(*tokens)[n->i][n->j - n->k] = line[n->j];
	n->j++;
	while (line[n->j] && line[n->j] != quote)
	{
		if (quote == '"' && line[n->j] == '\\')
		{
			(*tokens)[n->i][n->j - n->k] = line[n->j];
			n->j++;
			(*tokens)[n->i][n->j - n->k] = line[n->j];
			n->j++;
		}
		else
		{
			(*tokens)[n->i][n->j - n->k] = line[n->j];
			n->j++;
		}
	}
	if (line[n->j] == quote)
	{
		(*tokens)[n->i][n->j - n->k] = line[n->j];
		n->j++;
	}
}
