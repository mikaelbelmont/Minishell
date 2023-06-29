/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:52:28 by francsan          #+#    #+#             */
/*   Updated: 2023/06/28 23:28:43 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_valid(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
	{
		if (i == 0 && !((str[i] >= 'a' && str[i] <= 'z') || \
		(str[i] >= 'A' && str[i] <= 'Z')))
			return (0);
		if (i && !ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

int	strrlen(char *str, char c)
{
	int	len;

	len = -1;
	if (!str)
		return (0);
	while (str[++len] && str[len] != c)
		;
	return (len + (str[len] == c));
}

int	env_set(char **tokens, t_env *env, int i)
{
	char	**tmp;
	int		len;
	int		j;
	int		k;

	tmp = env->env;
	len = -1;
	while (env->env[++len])
		;
	env->env = ft_calloc(len, sizeof(char *));
	if (!env->env)
		return (1);
	j = -1;
	k = 0;
	while (tmp[++j])
	{
		if (!ft_strncmp(tokens[i], tmp[j], strrlen(tokens[i], -1)))
			free(tmp[j]);
		else
			env->env[k++] = tmp[j];
	}
	free(tmp);
	return (0);
}

char	*get_var(char **env, char *envid)
{
	int		i;
	char	*val;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(envid, env[i], strrlen(envid, -1)))
		{
			val = ft_strdup(env[i] + strrlen(env[i], '='));
			return (val);
		}
	}
	return (NULL);
}

int	var_set(char **tokens)
{
	char	**tmp;
	char	*val;

	val = get_var(env_func()->env, "HOME=");
	if (!val)
		return (0);/*return(*print_error(cmd, HOME not set))*/
	tmp = tokens;
	tokens = ft_calloc(3, sizeof(char *));
	if (!tokens)
		return (2);
	tokens[0] = tmp[0];
	tokens[1] = val;
	free(tmp);
	return (0);
}
