/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:29:25 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 02:15:46 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/* segfaults on env after set, doesn't seem to be updated env outside this shit */
/* consider making all functions return env so updates stay consistent */

char	**ft_env_set(char *new, char **env)
{
	int		i;

	i = 0;
	/*n compare to find variable names already used*/
	/*or stringsplit using '='*/
	while (env[i] && ft_strcmp(env[i], new))
		i++;
	if (env[i])
	{
		free(env[i]);
		env[i] = new;
	}
	else
		env = array_join(env, new);
	return (env);
}

char	**ft_setenv(char **args, char **env)
{
	env = ft_env_set(ft_strdup(args[1]), env);
	return (env);
}

char	**ft_env(char **args, char **env)
{
	int		i;

	i = 0;
	if (args && env)
		while (env[i])
			ft_printf("%s\n", env[i++]);
	return (env);
}

/*int		execute_nonbuiltin(char *com, char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	path = ft_strsplit(env[i] + 5, ':');
	//either concatonate the command onto each string of path and find file that way
	//or find a way to search that path for an executable 
}*/
