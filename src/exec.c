/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 03:19:30 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 03:22:17 by dromansk         ###   ########.fr       */
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
	//either concatonate the command onto each string of path and find file that way
	//or find a way to search that path for an executable
