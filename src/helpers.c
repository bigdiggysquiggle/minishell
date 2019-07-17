/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:08:43 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/17 16:03:32 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*get_quotes(char *st)
{
	char	*n;

	n = NULL;
	ft_printf("dquote> ");
	get_next_line(0, &n);
	st = swap_n_free(ft_strjoin(st, n), &st);
	free(n);
	return (st);
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

char	**handle_expansion_tmp(char **exp, char *tmp, char **env, int mode)
{
	if (mode)
	{
		if (ft_strlen(tmp))
				exp = array_join(exp, ft_strequ(tmp, "$0") ?
					ft_strdup("-minishell") : exp_from_env(&tmp, 0, env));
		free(tmp);
	}
	else
	{
		if (ft_strlen(tmp))
			exp = array_join(exp, tmp);
		else
			free(tmp);
	}
	return (exp);
}

/*
** not sure if needed. not sure if dollar expansion is supposed to
** also do argument numbers in minishell
*/

int		is_arg_dollar(char *s)
{
	int		i;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	return (s[i] ? 0 : 1);
}
