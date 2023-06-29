/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:02:10 by francisco         #+#    #+#             */
/*   Updated: 2023/06/28 23:43:00 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*skip_quotes(t_data **d, t_ints *n)
{
	char	*redir;

	n->j = 0;
	while ((*d)->tokens[n->i].token[n->j] != '"' \
		&& (*d)->tokens[n->i].token[n->j] != '\'')
		n->j++;
	if ((*d)->tokens[n->i].token[n->j] == '"')
	{
		n->j++;
		while ((*d)->tokens[n->i].token[n->j] != '"')
			n->j++;
		n->j++;
	}
	else if ((*d)->tokens[n->i].token[n->j] == '\'')
	{
		n->j++;
		while ((*d)->tokens[n->i].token[n->j] != '\'')
			n->j++;
		n->j++;
	}
	redir = ft_strdup(&(*d)->tokens[n->i].token[n->j]);
	return (redir);
}

void	handle_heredoc(t_data **d, char *delimiter)
{
	char	*buffer;
	int		temp_fd;

	temp_fd = open("../.tmp", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	write(STDIN_FILENO, "> ", 2);
	buffer = get_next_line(STDIN_FILENO);
	while (1)
	{
		if (ft_strncmp(buffer, delimiter, ft_strlen(buffer) - 1) == 0 \
			&& ft_strlen(buffer) > 1)
			break ;
		write(temp_fd, buffer, ft_strlen(buffer));
		free(buffer);
		write(STDIN_FILENO, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
	}
	free(buffer);
	(*d)->infile = open("../.tmp", O_RDONLY);
}

void	handle_redirections(t_data **d, t_ints *n, char *redir)
{
	if (redir[0] == '<')
	{
		redirect_input(d, n, redir);
	}
	else if (redir[0] == '>')
	{
		redirect_output(d, n, redir);
	}
}

void	check_redir(t_data **d, int cmd_num)
{
	t_ints	n;
	char	*redir;

	n.i = cmd_num;
	while ((*d)->tokens[n.i].token && (*d)->tokens[n.i].f_pipe == 0)
	{
		if ((*d)->tokens[n.i].f_r_in == 1 || (*d)->tokens[n.i].f_r_out == 1)
		{
			if ((*d)->tokens[n.i].f_singlequotes == 1 \
				|| (*d)->tokens[n.i].f_doublequotes == 1)
			{
				redir = skip_quotes(d, &n);
				handle_redirections(d, &n, redir);
				free(redir);
			}
			else
				handle_redirections(d, &n, (*d)->tokens[n.i].token);
		}
		if ((*d)->infile < 0)
		{
			g_exitvalue = errno;
			exit(g_exitvalue);
		}
		n.i++;
	}
}
