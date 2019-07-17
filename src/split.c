/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:55:16 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/17 13:49:32 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char			*contract_path(char **paths, char *d)
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

static int		wordlen(char const *str, char *de)
{
	int		i;
	int		j;
	char	d;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == '\"' || str[i] == '\'')
		{
			d = str[i++];
			while (str[i] && str[i] != d)
				i++;
		}
		while (de[j] && de[j] != str[i])
			j++;
		if (de[j])
			break ;
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
			n = array_join(n, ft_strndup(s, (size_t)len));
			s += len;
		}
		else
			s++;
	}
	return (n);
}

char			**strip_quotes(char **args)
{
	int		i;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '\'' || args[i][0] == '\"')
		{
			tmp = ft_strndup(args[i] + 1, ft_strlen(args[i]) - 2);
			free(args[i]);
			args[i] = tmp;
		}
	}
	return (args);
}
