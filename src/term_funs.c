/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_funs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:25:21 by dromansk          #+#    #+#             */
/*   Updated: 2019/06/26 16:37:16 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

echo, cd, setenv, unsetenv, env, exit
#include "ft_minishell.h"

int		builtins(t_com *com)
{
	if (/*cd && */chdir(/*path arg*/) < 0)
		ft_printf("cd: no such file or directory: %s\n", /*path*/);
	if (/*echo*/)
		ft_putendl(/*arg*/);
	if (/*env*/)
		/*env handling functions*/
	/* figure out exit */
}
