/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:55:16 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 14:14:32 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*strip parentheseseses here unless escaped */

char			*cmd_split_dupe(char const *s, size_t len)
{
	char 	*d;
	int		i;
	int		j;

	i = 0;
	j = 0;
	d = NULL;
	if (s[i] == '"')
	{
		while (s[i] == '"')
			i++;
		while (s[i + j] && s[i + j] != '"')
			j++;
		d = ft_strsub(s, i, j);
	}
	else
		d = ft_strndup(s, len);
	return (d);
}

static int		wordlen(char const *str, char *d)
{
	int		i;
	int		j;

	i = 0;
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
		return (++i);
	}
	while (str[i])
	{
		j = 0;
		while (d[j] && d[j] != str[i])
			j++;
		if (d[j])
			return (i);
		i++;
	}
	return (i);
}

char			**cmd_split(char const *s, char *c)
{
	char	**n;
	int		len;
	int		i;

	if (s == NULL || !(n = (char **)malloc(sizeof(char *))))
		return (NULL);
	*n = NULL;
	while (*s)
	{
		i = 0;
		while (c[i] && c[i] != *s)
			i++;
		if (!c[i])
		{
			len = wordlen(s, c);
			n = array_join(n, cmd_split_dupe(s, (size_t)len));
			s += len;
		}
		else
			s++;
	}
	return (n);
}
