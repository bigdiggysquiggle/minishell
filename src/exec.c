/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 03:19:30 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/16 16:18:27 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "sys/wait.h"

void	execute(char *cmd, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0 && execve(cmd, args, env) == -1)
		ft_printf("permission denied\n"); //might need program name on there
	else if (pid < 0)
		ft_printf("%s: failed to fork\n", args[0]);
	else
		wait(&pid);
}

char	*make_path(char *cmd, char *path)
{
	char	*s;
	char	*d;

	d = ft_strjoin(path, "/");
	s = ft_strjoin(d, cmd);
	free(d);
	return (s);
}

int		execute_localfile(char **args, char **env)
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
	free(cmd);
	free_split(path);
	return (0);
}
/* logic can be redone, also needs to work on local files */
int		execute_nonbuiltin(char **args, char **env)
{
	int		i;
	char	**path;
	char	*cmd;

	i = 0;
	if (args[0][0] != '.')
		return (execute_localfile(args, eng));
	else
	{
		cmd = ft_strdup(args[0]);
		if (access(cmd, F_OK))
			ft_printf("-minishell: no such file or directory: %s\n", cmd);
		else
			execute(cmd, args, env);
		free(cmd);
	}
	return (0);
}
