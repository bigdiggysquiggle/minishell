/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:08:43 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/09 19:00:05 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		count_quotes(char *st)
{
	int		s;
	int		d;
	int		i;

	s = 0;
	d = 0;
	i = -1;
	while (st[++i])
	{
		if (st[i] == '\'')
			s++;
		if (st[i] == '\"')
			d++;
	}
	return ((d % 2 || (!d && s % 2)) ? 0 : 1);
}

/*int		is_arg_dollar(char *s)
{
	int		i;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	return (s[i] ? 0 : 1);
}*/
