/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:15:28 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/09 18:59:53 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/* $0 is name of shell or script */

/*char	*exp_from_args(char **args, int i)
{
	int		j;

	j = ft_atoi(args[i] + 1);
	free(args[i]);
	return (ft_strdup(args[j]));
}*/

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

char	*exp_path(char **args, int i, char **env)
{
	char	**exp;

	exp = ft_strsplit(args[i], '/');
	if (ft_strequ(exp[0], "~"))
	{
		free(exp[0]);
		exp[0] = ft_strdup("$HOME");
	}
	return (contract_path(expand_dollar(exp, env), "/"));
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
		tmp = ft_strndup(arg, i);
		if (ft_strlen(tmp))
			exp = array_join(exp, tmp);
		arg += i;
		i = 0;
		if (arg[i] == '$')
		{
			printf("expanding\n");
			i++;
			while (arg[i] && ('_' == arg[i] ||
					ft_isupper(arg[i]) || ft_isdigit(arg[i])))
				i++;
		}
		tmp = ft_strndup(arg, i);
		if (ft_strlen(tmp))
			exp = array_join(exp, ft_strequ(tmp, "$0") ?
					ft_strdup("-minishell") : exp_from_env(&tmp, 0, env));
		arg += i;
	}
	tmp = contract_path(exp, "");
	free_split(exp);
	return (tmp);
}

	char	c;

char	**expand_dollar(char **args, char **env)
{
	int		i;
	char	*t;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '~')
			args[i] = exp_path(args, i, env);
		if (ft_strchr(args[i], '$'))
		{
			t = exp_dollars(args[i], env);
			free(args[i]);
			args[i] = t;
		}
	}
	return (args);
}
