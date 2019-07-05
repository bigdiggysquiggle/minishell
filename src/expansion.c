/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:15:28 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 15:57:01 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/* $0 is name of shell or script */

char	*exp_from_args(char **args, int i, char **env)
{
	int		j;

	if ('0' <= args[i][1] && args[i][1] <= '9')
	{
		j = ft_atoi(args[i] + 1);
		return (ft_strdup(args[j]));
	}
	return (NULL);
}

char	*exp_from_env(char **arg, int i, char **env)
{
	size_t	len;

	len = ft_strlen(arg[i] + 1);
	while (*env && !ft_strnequ(arg[i] + 1, *env, len))
		env++;
	if (*env)
		return (ft_strdup(ft_strrchr(*env, '=') + 1));
	return (ft_strdup(""));
}

char	*contract_path(char **paths)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_strdup(paths[0]);
	while (paths[++i])
	{
		tmp = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(tmp, paths[i]);
		free(tmp);
	}
	return (path);
}

char	*exp_path(char **args, int i, char **env)
{
	char	**exp;

	exp = ft_strsplit(args[i], '/');
	if (ft_strequ(exp[0], "~"))
	{
		free(exp[0]);
		exp[0] = ft_strdup("$HOME");
	}
	return (contract_path(expand_dollar(exp, env)));
}

char	**expand_dollar(char **args, char **env)
{
	int		i;
	char	*t;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '$')
		{
			t = exp_from_env(args, i, env);
			if (t)
			{
				free(args[i]);
				args[i] = t;
			}
		}
		if (args[i][0] == '~')
			args[i] = exp_path(args, i, env);
	}
	return (args);
}
