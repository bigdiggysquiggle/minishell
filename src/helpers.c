/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:08:43 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/10 18:00:24 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*get_quotes(char *st)
{
	char	*n;

	n = NULL;
	ft_printf("dquote> ");
	get_next_line(0, &n);
	n = swap_n_free(ft_strjoin(st, n), &n);
	return (n);
}

int		find_end_quote(char *s, char c)
{
	int		i;

	i = 1;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int		count_quotes(char *st)
{
	int		i;

	i = -1;
	while (st[++i])
	{
		if (st[i] == '\'' || st[i] == '\"')
			i += find_end_quote(st + i, st[i]);
		if (!st[i])
			return (0);
	}
	return (1);
}

/*int		is_arg_dollar(char *s)
{
	int		i;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	return (s[i] ? 0 : 1);
}*/
