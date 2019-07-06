/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 03:19:30 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 19:31:05 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	execute(char *cmd, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0 && execve(cmd, args, env) == -1)
		ft_printf("permission denied\n"); //might need program name on there
	else if (pid < 0)
		//ft_error(1, name, "failed to fork");
		ft_printf("failed to fork\n");
	else
		wait(&pid);
}

char	*make_path(char *cmd, char *path)
{
	char	*s;
	char	*d;

	d = ft_strjoin(path, "/");//make sure to check for ending '/'
	s = ft_strjoin(d, cmd);
	free(d);
	return (s);
}

int		execute_nonbuiltin(char **args, char **env)
{
	int		i;
	char	**path;
	char	*cmd;

	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	path = ft_strsplit(env[i] + 5, ':');
	i = 0;
	cmd = make_path(args[0], path[i++]);
	while (path[i] && access(cmd, F_OK) < 0)
	{
		free(cmd);
		cmd = make_path(args[0], path[i++]);
	}
	if (path[i])
		execute(cmd, args, env);
	else
		ft_printf("%s: command not found\n", args[0]);
	return (0);
}
	/* use strjoin and access to test each path. -1 means it's not there */
	/* access(joined, F_OK); */
