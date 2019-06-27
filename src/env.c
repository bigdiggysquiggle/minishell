/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:29:25 by dromansk          #+#    #+#             */
/*   Updated: 2019/06/26 20:54:03 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/* might need to clone environ so I can work with it within this terminal */

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
