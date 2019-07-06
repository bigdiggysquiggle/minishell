/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:55:16 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 21:23:57 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/* quote getting is hateful */

char	*get_quotes(char *st)
{
	char	*n;

	n = NULL;
	ft_printf("dquote> ");
	get_next_line(0, &n);
	st = swap_n_free(ft_strjoin(st, n), &st);
	return (st);
}

char	*contract_path(char **paths, char *d)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_strdup(paths[0]);
	while (paths[++i])
	{
		tmp = ft_strjoin(path, d);
		free(path);
		path = ft_strjoin(tmp, paths[i]);
		free(tmp);
	}
	return (path);
}

char		*cmd_split_dupe(char const *s, size_t len)
{
	char 	*d;
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	d = NULL;
	s = ft_strdup(s);
	if (s[i] == '\"' | s[i] == '\'')
	{
		if (!count_quotes((char *)s))
			s = get_quotes((char *)s);
		c = s[i];
		while (s[i] == c)
			i++;
		while (s[i + j] && s[i + j] != c)
			j++;
		d = ft_strsub(s, i, j);
	}
	else
		d = ft_strndup(s, len);
	free((char *)s);
	return (d);
}

static int		wordlen(char const *str, char *de)
{
	int		i;
	int		j;
	char	d;

	i = 0;
	if (str[i] == '\"' | str[i] == '\'')
	{
		d = str[i++];
		while (str[i] && str[i] != d)
			i++;
		return (++i);
	}
	while (str[i])
	{
		j = 0;
		while (de[j] && de[j] != str[i])
			j++;
		if (de[j])
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
