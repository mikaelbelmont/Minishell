/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:19:19 by francisco         #+#    #+#             */
/*   Updated: 2023/06/28 23:42:56 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// JUST FOR TESTING
void	print_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("%s%s%s\n", YELLOW, arr[i], DEFAULT);
}

void	print_tokens(t_data **d, char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		printf("%s%s%s\n", BLUE, (*d)->tokens[i].token, DEFAULT);
		printf("Pipe: %i\n", (*d)->tokens[i].f_pipe);
		printf("Input Redirection: %i\n", (*d)->tokens[i].f_r_in);
		printf("Output Redirection: %i\n", (*d)->tokens[i].f_r_out);
		printf("File: %i\n", (*d)->tokens[i].f_file);
		printf("Single Quotes: %i\n", (*d)->tokens[i].f_singlequotes);
		printf("Double Quotes: %i\n", (*d)->tokens[i].f_doublequotes);
		printf("Command: %i\n", (*d)->tokens[i].f_command);
		printf("Flag: %i\n", (*d)->tokens[i].f_flag);
		printf("Builtin: %i\n", (*d)->tokens[i].f_builtin);
		int	j = -1;
		while (++j < 7)
			printf("Builtins[%i] = %i\n", j, (*d)->tokens->f_builtins[j]);
		printf("\n");
		printf("Dollar Variable: %i\n", (*d)->tokens[i].f_dollarsign);
	}
}
// JUST FOR TESTING

int	g_exitvalue;

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;
	char	*buffer;
	char	*line;
	int		i;

	(void) argc;
	(void) argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	d = ft_calloc(1, sizeof(t_data));
	d->env = ft_strarr_copy(envp);
	env_func()->env = env_create(envp);
	get_paths(&d);
	while (1)
	{
		buffer = readline(PROMPT);
		line = sort_line(buffer);
		if_ctrl_d(&d, buffer, line);
		if (buffer && ft_strlen(buffer) > 0)
			add_history(buffer);
		if (parse_command(d, line))
			break ;
		if (d->num_commands != 0 || d->flag_builtin != 0)
		{
			i = -1;
			while (d->tokens[++i].token)
				free(d->tokens[i].token);
		}
		free(d->tokens);
		free(line);
		free(buffer);
	}
	free_all(&d);
	free(line);
	free(buffer);
	return (g_exitvalue);
}
