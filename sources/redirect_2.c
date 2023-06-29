/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 23:39:39 by francisco         #+#    #+#             */
/*   Updated: 2023/06/28 23:39:55 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	redirect_input(t_data **d, t_ints *n, char *redir)
{
	if (redir[1] == '\0')
		(*d)->infile = open((*d)->tokens[n->i + 1].token, O_RDONLY);
	else if (redir[1] == '<')
	{
		if (redir[2] == '\0')
			handle_heredoc(d, (*d)->tokens[n->i + 1].token);
		else if (redir[2])
			handle_heredoc(d, &redir[2]);
	}
	else if (redir[1] != '<' && redir[1])
		(*d)->infile = open(&redir[1], O_RDONLY);
	dup2((*d)->infile, STDIN_FILENO);
	close((*d)->infile);
}

void	redirect_output(t_data **d, t_ints *n, char *redir)
{
	if (redir[1] == '\0')
		(*d)->outfile = open((*d)->tokens[n->i + 1].token, \
			O_CREAT | O_TRUNC | O_WRONLY, 0666);
	else if (redir[1] == '>')
	{
		if (redir[2] == '\0')
			(*d)->outfile = open((*d)->tokens[n->i + 1].token, \
			O_CREAT | O_APPEND | O_WRONLY, 0666);
		else if (redir[2])
			(*d)->outfile = open(&redir[2], \
			O_CREAT | O_APPEND | O_WRONLY, 0666);
	}
	else if (redir[1] != '>' && redir[1])
		(*d)->outfile = open(&redir[1], \
			O_CREAT | O_TRUNC | O_WRONLY, 0666);
	dup2((*d)->outfile, STDOUT_FILENO);
	close((*d)->outfile);
}
