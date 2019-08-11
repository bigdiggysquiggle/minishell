/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 03:19:30 by dromansk          #+#    #+#             */
/*   Updated: 2019/08/10 19:43:12 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "sys/wait.h"

char	**squirrel(char **args, char **env)
{
	if (args)
	{
		ft_printf("          )\" .\n");
		ft_printf("         /    \\      (\\-./\n");
		ft_printf("        /     |    _/ o. \\\n");
		ft_printf("       |      | .-\"      y)-\n");
		ft_printf("       |      |/       _/ \\\n");
		ft_printf("       \\     /j   _\".\\(@)\n");
		ft_printf("        \\   ( |    `.''  )\n");
		ft_printf("         \\  _`-     |   /\n");
		ft_printf("           \"  `-._  <_ (\n");
		ft_printf("                  `-.,),)\n");
	}
	return (env);
}

void	execute(char *cmd, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, sig_process);
	if (pid == 0 && execve(cmd, args, env) == -1)
	{
		ft_printf("%s: permission denied\n", args[0]);
		exit(0);
	}
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

int		execute_builtin(char **args, char **env)
{
	int		i;
	char	**path;
	char	*cmd;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	path = env[i] ? ft_strsplit(env[i] + 5, ':') : 0;
	i = 0;
	cmd = path ? make_path(args[0], path[i++]) : ft_strdup(args[0]);
	while (path && path[i] && access(cmd, F_OK) < 0)
	{
		free(cmd);
		cmd = make_path(args[0], path[i++]);
	}
	if (path && path[i])
		execute(cmd, args, env);
	else
		ft_printf("%s: command not found\n", args[0]);
	free(cmd);
	free_split(path);
	return (0);
}

int		execute_nonbuiltin(char **args, char **env)
{
	char	*cmd;

	if (args[0][0] != '.' && args[0][0] != '/')
		return (execute_builtin(args, env));
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
