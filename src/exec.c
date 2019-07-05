/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 03:19:30 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 03:31:19 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		execute_nonbuiltin(char **args, char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	path = ft_strsplit(env[i] + 5, ':');
	/* use strjoin and access to test each path. -1 means it's not there */
	/* access(joined, F_OK); */
