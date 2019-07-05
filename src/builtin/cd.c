/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:53:19 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 16:16:28 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "sys/param.h"

char	**update_oldpwd(char **env)
{
	char	**r;
	char	*path;

	r = (char **)malloc(sizeof(char *) * 4);
	r[0] = "setenv";
	r[1] = "$PWD";
	r[2] = 0;
	path = exp_from_env(r, 1, env);
	r[1] = "OLDPWD";
	r[2] = path;
	r[3] = 0;
	env = ft_setenv(r, env);
	free(path);
	free(r);
	return (env);
}

char	**update_pwd(char **env, char *path)
{
	char	**r;
	char	buf[MAXPATHLEN + 1];

	if (chdir(path) < 0)
	{
		if (!access(path, F_OK))
			ft_printf("cd: permission denied: %s\n", path);
		else
			ft_printf("cd: no such file or directory: %s\n", path);
		return (env);
	}
	r = (char **)malloc(sizeof(char *) * 4);
	r[0] = "setenv";
	env = update_oldpwd(env);
	r[1] = "PWD";
	r[2] = getcwd(buf, MAXPATHLEN);
	r[3] = 0;
	env = ft_setenv(r, env);
	free(r);
	return (env);
}

char	**cd_swap(char **args, char **env)
{
	char	*path;
	char	**exp;
	int		i;

	path = ft_strdup("$PWD");
	path = swap_n_free(exp_from_env(&path, 0, env), &path);
	exp = ft_strsplit(path, '/');
	free(path);
	i = 0;
	while (!ft_strequ(args[1], exp[i]))
		i++;
	if (exp[i])
	{
		free(exp[i]);
		exp[i] = ft_strdup(args[2]);
		path = contract_path(exp);
		path = swap_n_free(ft_strjoin("/", path), &path);
		env = update_pwd(env, path);
		free(path);
	}
	free_split(exp);
	return (env);
}

char	**ft_cd(char **args, char **env)
{
	char	**exp;
	char	*path;

	if (args[2])
		return (cd_swap(args, env));
	else
	{
		exp = ft_strsplit(args[1], '/');
		exp = expand_dollar(exp, env);
		path = contract_path(exp);
		free_split(exp);
		env = update_pwd(env, path);
	}
	return (env);
}
