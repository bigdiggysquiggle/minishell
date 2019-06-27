/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:29:25 by dromansk          #+#    #+#             */
/*   Updated: 2019/06/26 18:02:42 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

extern char **environ;
/* might need to clone environ so I can work with it within this terminal */

int		ft_env_set(char *new)
{
	int		i;

	i = 0;
	while (ft_strcmp(environ[i], new))
		i++;
	if (environ[i])
	{
		free(environ[i]);
		environ[i] = new;
	}
	else
		array_join(environ, new);
}
