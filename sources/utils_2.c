/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francsan <francsan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:11:37 by francsan          #+#    #+#             */
/*   Updated: 2023/06/27 20:00:24 by francsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_env	*env_func(void)
{
	static t_env	env;

	return (&env);
}

char	*shell_lvl(char *envp)
{
	char	*env;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_itoa(NULL, &i, 1, ft_atoi(envp) + 1);
	if (!tmp)
		return (NULL);
	env = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	return (env);
}

char	**env_create(char **envp)
{
	int		i;
	char	**env;

	i = -1;
	while (envp[++i])
		;
	env = ft_calloc((i + 1), sizeof(char *));
	if (!env)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
			env[i] = shell_lvl(envp[i] + 6);
		else
			env[i] = strdup(envp[i]);
		if (!env[i])
		{
			free(env);
			return (NULL);
		}
	}
	return (env);
}
