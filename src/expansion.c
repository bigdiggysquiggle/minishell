/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:15:28 by dromansk          #+#    #+#             */
/*   Updated: 2019/08/19 22:24:58 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
**leaving this here in case dollar expansion needs to handle arguments too
**char	*exp_from_args(char **args, int i)
**{
**	int		j;
**
**	j = ft_atoi(args[i] + 1);
**	free(args[i]);
**	return (ft_strdup(args[j]));
**}
*/

char	*exp_from_env(char **arg, int i, char **env)
{
	while (*env && !ft_strnequ(arg[i] + 1, *env, chr_index(*env, '=')))
		env++;
	if (*env)
		return (ft_strdup(ft_strrchr(*env, '=') + 1));
	return (ft_strdup(""));
}

char	*exp_path(char **args, int i, char **env)
{
	char	**exp;
	char	*path;

	exp = ft_strsplit(args[i], '/');
	if (ft_strequ(exp[0], "~"))
	{
		free(exp[0]);
		exp[0] = ft_strdup("$HOME");
	}
	path = contract_path(expand_dollar(exp, env), "/");
	free_split(exp);
	return (path);
}

int		dollar_len(char *arg)
{
	int		i;

	i = 1;
	while (arg[i] && ('_' == arg[i] ||
				ft_isalpha(arg[i]) || ft_isdigit(arg[i])))
		i++;
	return (i);
}

char	*exp_dollars(char *arg, char **env)
{
	char	**exp;
	int		i;
	char	*tmp;

	exp = (char **)malloc(sizeof(char *));
	exp[0] = NULL;
	while (*arg)
	{
		i = 0;
		while (arg[i] && arg[i] != '$')
			i++;
		exp = handle_expansion_tmp(exp, ft_strndup(arg, i), env, 0);
		arg += i;
		i = (arg[0] == '$') ? dollar_len(arg) : 0;
		exp = i != 1 ? handle_expansion_tmp(exp, ft_strndup(arg, i), env, 1) :
			handle_expansion_tmp(exp, ft_strdup("$"), env, 0);
		arg += i;
	}
	tmp = contract_path(exp, "");
	free_split(exp);
	return (tmp);
}

char	**expand_dollar(char **args, char **env)
{
	int		i;
	char	*t;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '~')
		{
			t = exp_path(args, i, env);
			free(args[i]);
			args[i] = t;
		}
		if (ft_strchr(args[i], '$'))
		{
			t = exp_dollars(args[i], env);
			free(args[i]);
			args[i] = t;
		}
	}
	return (args);
}
