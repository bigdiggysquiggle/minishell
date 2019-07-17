/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:53:19 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/17 16:25:24 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "sys/param.h"
#include "sys/stat.h"

/*
** need to figure out symlink behaviour
*/

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
	char		**r;
	char		buf[MAXPATHLEN + 1];
	struct stat	d;

	if (chdir(path) < 0)
	{
		lstat(path, &d);
		if (!access(path, F_OK))
			ft_printf(!S_ISDIR(d.st_mode) ? "cd: not a directory: %s\n" :
					"cd: permission denied: %s\n", path);
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
		path = contract_path(exp, "/");
		path = swap_n_free(ft_strjoin("/", path), &path);
		env = update_pwd(env, path);
		ft_printf("%s\n", path);
		free(path);
	}
	free_split(exp);
	return (env);
}

char	*get_home(char *home, char **env)
{
	return (exp_from_env(&home, 0, env));
}

char	**ft_cd(char **args, char **env)
{
	char	**exp;
	char	*path;

	exp = NULL;
	path = NULL;
	if (args[1] && args[2])
		return (cd_swap(args, env));
	else
	{
		if (args[1])
			exp = ft_strsplit(args[1], '/');
		if (!exp || !*exp)
			path = args[1] ? ft_strdup(args[1]) : get_home("$HOME", env);
		else
		{
			exp = expand_dollar(exp, env);
			path = contract_path(exp, "/");
		}
		free_split(exp);
		env = update_pwd(env, path);
		if (path)
			free(path);
	}
	return (env);
}
