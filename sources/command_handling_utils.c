/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:18:41 by francsan          #+#    #+#             */
/*   Updated: 2023/06/29 00:20:52 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*remove_quotes(t_data **d, t_ints *n, char quotes)
{
	t_ints	m;

	m.l = 0;
	while (m.l < 2)
	{
		m.i = 0;
		m.j = 0;
		m.k = 0;
		while ((*d)->tokens[n->i].token[m.i] && m.j != 2)
			remove_quotes_2(d, n, &m, quotes);
		if (m.l == 0)
			m.tmp = ft_calloc(m.k + 1, sizeof(char));
		m.l++;
	}
	return (m.tmp);
}

void	skip_redir(t_data **d, t_ints *n)
{
	t_ints	m;
	char	redir;

	m.i = 0;
	while ((*d)->tokens[n->i].token[m.i] != '<' \
		&& (*d)->tokens[n->i].token[m.i] != '>')
		m.i++;
	redir = (*d)->tokens[n->i].token[m.i];
	m.i++;
	if ((*d)->tokens[n->i].token[m.i] == '\0')
		n->i += 2;
	else if ((*d)->tokens[n->i].token[m.i] == redir)
	{
		if ((*d)->tokens[n->i].token[m.i + 1] == '\0')
			n->i += 2;
		else if ((*d)->tokens[n->i].token[m.i + 1] \
			&& (*d)->tokens[n->i].token[m.i + 1] != redir)
			n->i++;
	}
	else if ((*d)->tokens[n->i].token[m.i] \
		&& (*d)->tokens[n->i].token[m.i] != redir)
		n->i++;
}

char	**get_cmd(t_data **d, t_ints *n)
{
	t_ints	m;
	char	**cmd;

	m.i = n->i;
	while ((*d)->tokens[m.i].token && (*d)->tokens[m.i].f_pipe == 0)
		m.i++;
	cmd = ft_calloc(m.i - n->i + 1, sizeof(char *));
	m.j = 0;
	while ((*d)->tokens[n->i].token && (*d)->tokens[n->i].f_pipe == 0)
		get_cmd_2(d, n, &m, &cmd);
	return (cmd);
}

int	get_pwd(t_data **d, char **pwd)
{
	int		i;

	i = -1;
	while ((*d)->env[++i])
	{
		if (ft_strncmp((*d)->env[i], "PWD=", 4) == 0)
		{
			*pwd = ft_strdup((*d)->env[i]);
			return (i);
		}
	}
	return (0);
}
