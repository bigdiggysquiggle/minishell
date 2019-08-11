/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 23:13:35 by dromansk          #+#    #+#             */
/*   Updated: 2019/08/10 18:59:27 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**ft_echo(char **args, char **env)
{
	int		i;
	int		flag;
	int		n;

	flag = 0;
	n = ft_strequ(args[1], "-n");
	i = n ? 1 : 0;
	while (args[++i])
	{
		ft_printf(flag ? " %s" : "%s", args[i]);
		flag = 1;
	}
	if (!n)
		ft_printf("\n");
	return (env);
}
