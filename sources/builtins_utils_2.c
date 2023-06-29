/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarreto <mbarreto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:36:59 by francsan          #+#    #+#             */
/*   Updated: 2023/06/29 18:32:02 by mbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < '0' && str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	sort_env(char **env, int i, int j)
{
	char	*tmp;

	if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) < 0)
	{
		tmp = env[i];
		env[i] = env[j];
		env[j] = tmp;
	}
}

void	export_print(char **env, int out)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[++j])
			sort_env(env, i, j);
	}
	i = -1;
	while (env[++i])
	{
		len = strrlen(env[i], '=');
		write(out, "declare -x ", 11);
		write(out, env[i], len);
		if (env[i][len - 1] == '=')
		{
			write(out, "\"", 1);
			if (env[i][len])
				write(out, env[i] + len, strrlen(env[i] + len, -1));
			write(out, "\"\n", 2);	
		}
		else
			write(out, "\n", 1);
	}
}
