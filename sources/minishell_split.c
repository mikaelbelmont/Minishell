/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:15:36 by francisco         #+#    #+#             */
/*   Updated: 2023/05/05 13:53:28 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**alloc_tokens_array(char *line)
{
	char	**tokens;
	t_ints	n;

	n.i = 0;
	n.j = 0;
	while (line[n.j])
	{
		if (check_command(&n, line))
			return (NULL);
		n.i++;
		if (line[n.j])
			n.j++;
	}
	tokens = ft_calloc(n.i + 1, sizeof(char *));
	return (tokens);
}

int	alloc_tokens_strings(char ***tokens, char *line)
{
	t_ints	n;

	n.i = 0;
	n.j = 0;
	while (line[n.j])
	{
		n.k = n.j;
		while (line[n.j] && line[n.j] != ' ')
		{
			if (line[n.j] == '\'')
				get_quote_len(&n, line, '\'');
			else if (line[n.j] == '"')
				get_quote_len(&n, line, '"');
			else
				n.j++;
		}
		(*tokens)[n.i] = ft_calloc((n.j - n.k) + 1, sizeof(char));
		while (line[n.j] && line[n.j + 1] == ' ')
			n.j++;
		n.i++;
		if (line[n.j])
			n.j++;
	}
	return (n.i);
}

void	fill_tokens(char ***tokens, char *line, int token_num)
{
	t_ints	n;

	n.i = 0;
	n.j = 0;
	while (line[n.j] && n.i < token_num)
	{
		n.k = n.j;
		while (line[n.j] && line[n.j] != ' ')
		{
			if (line[n.j] == '\'')
				get_quote(&n, tokens, line, '\'');
			else if (line[n.j] == '"')
				get_quote(&n, tokens, line, '"');
			else
			{
				(*tokens)[n.i][n.j - n.k] = line[n.j];
				n.j++;
			}
		}
		while (line[n.j] && line[n.j + 1] == ' ')
			n.j++;
		n.i++;
		if (line[n.j])
			n.j++;
	}
}

char	**ft_minishell_split(char *line)
{
	char	**tokens;
	int		token_num;

	tokens = alloc_tokens_array(line);
	if (!tokens)
	{
		printf("Bad quotes!\n");
		return (NULL);
	}
	token_num = alloc_tokens_strings(&tokens, line);
	fill_tokens(&tokens, line, token_num);
	return (tokens);
}
