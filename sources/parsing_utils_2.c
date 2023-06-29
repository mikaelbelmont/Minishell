/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:03:53 by francisco         #+#    #+#             */
/*   Updated: 2023/06/28 16:37:40 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_char(char c)
{
	if (c >= 65 && c <= 90)
		return (0);
	if (c >= 97 && c <= 122)
		return (0);
	if (c >= 48 && c <= 57)
		return (0);
	if (c == 95)
		return (0);
	return (1);
}

char	**get_variable(t_data **d, t_ints *n)
{
	t_ints	m;
	char	*token;
	char	**vars;

	token = ft_strdup((*d)->tokens[n->i].token);
	m.i = -1;
	m.l = 0;
	while (token[++m.i])
		if (token[m.i] == '$')
			m.l++;
	vars = ft_calloc(m.l + 1, sizeof(char *));
	m.i = 0;
	m.l = 0;
	while (token[m.i])
	{
		if (token[m.i] == '$')
		{
			m.i++;
			m.j = 0;
			m.k = m.i;
			while (token[m.i] && check_char(token[m.i]) == 0)
			{
				m.i++;
				m.j++;
			}
			vars[m.l] = ft_calloc(m.j + 1, sizeof(char));
			m.j = 0;
			while (token[m.k] && check_char(token[m.k]) == 0)
				vars[m.l][m.j++] = token[m.k++];
			m.l++;
		}
		else
			m.i++;
	}
	free(token);
	return (vars);
}

char	**get_values(char **vars)
{
	char	**env;
	char	**vars_values;
	t_ints	m;

	env = ft_strarr_copy(env_func()->env);
	m.k = 0;
	while (vars[m.k])
		m.k++;
	vars_values = ft_calloc(m.k + 1, sizeof(char *));
	m.j = 0;
	while (vars[m.j])
	{
		m.i = -1;
		while (env[++m.i])
		{
			if (ft_strncmp(env[m.i], vars[m.j], ft_strlen(vars[m.j])) == 0)
			{
				vars_values[m.j] = \
				ft_strdup(&env[m.i][ft_strlen(vars[m.j]) + 1]);
				m.j++;
				break ;
			}
		}
	}
	ft_strarr_free(env);
	return (vars_values);
}

int	get_calloc_size(t_data **d, t_ints *n, char **vars, char **vars_values)
{
	t_ints	m;

	m.i = 0;
	m.j = 0;
	while (vars_values[m.i])
	{
		m.j += ft_strlen(vars_values[m.i]);
		m.i++;
	}
	m.i = 0;
	m.k = 0;
	while (vars[m.i])
	{
		m.k += ft_strlen(vars[m.i]);
		m.i++;
	}
	m.l = ft_strlen((*d)->tokens[n->i].token);
	return (m.l - m.k + m.j + 1);
}

void	expand_variable(t_data **d, t_ints *n)
{
	t_ints	m;
	char	**vars;
	char	**vars_values;
	char	*token;

	if (ft_strncmp((*d)->tokens[n->i].token, "$?", 2) == 0)
	{
		free((*d)->tokens[n->i].token);
		(*d)->tokens[n->i].token = ft_itoa_2(g_exitvalue);
		return ;
	}
	vars = get_variable(d, n);
	vars_values = get_values(vars);
	token = ft_calloc(get_calloc_size(d, n, vars, vars_values), sizeof(char));
	m.i = 0;
	m.j = 0;
	m.k = 0;
	while ((*d)->tokens[n->i].token[m.i])
	{
		if ((*d)->tokens[n->i].token[m.i] != '$')
		{
			token[m.j] = (*d)->tokens[n->i].token[m.i];
			m.i++;
			m.j++;
		}
		else
		{
			m.i += ft_strlen(vars[m.k]) + 1;
			m.l = 0;
			while (vars_values[m.k][m.l])
			{
				token[m.j] = vars_values[m.k][m.l];
				m.j++;
				m.l++;
			}
			m.k++;
		}
	}
	free((*d)->tokens[n->i].token);
	(*d)->tokens[n->i].token = ft_strdup(token);
	free(token);
	ft_strarr_free(vars_values);
	ft_strarr_free(vars);
}
