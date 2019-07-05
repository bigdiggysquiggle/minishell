/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:29:25 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/03 23:10:05 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/* might need to clone environ so I can work with it within this terminal */
/* did clone environ to work with within this terminal */
/* path exists as part of environ so that's easy enough */
/* might not need to clone environment */

char	**ft_env_set(char *new, char **env)
{
	int		i;

	i = 0;
	while (ft_strcmp(env[i], new))
		i++;
	if (env[i])
	{
		free(env[i]);
		env[i] = new;
	}
	else
		array_join(env, new);
	return (env);
}

int		execute_com(char *com, char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	path = ft_strsplit(env[i] + 5, ':');
	//either concatonate the command onto each string of path and find file that way
	//or find a way to search that path for an executable 
}
