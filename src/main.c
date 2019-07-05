/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:10:56 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 01:12:11 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*You must deal correctly with the PATH and the environment (copy of system char
**environ).
You must implement a series of builtins: echo, cd, setenv, unsetenv, env, exit.*/

/* consider a jump table with functions and their names as strings */

extern char	**environ;

void	free_split(char **cmdsplit)
{
	int		i;

	i = 0;
	while (cmdsplit[i])
		free(cmdsplit[i++]);
	free(cmdsplit);
}

int		exec_cmds(char *cmd, char **env)
{
	char	**cmds;

	cmds = cmd_split(cmd, " \t\n\r\a");
	if (ft_strequ(cmds[0], "env"))
	{
		int i = 0;
		while (env[i])
			printf("%s\n", env[i++]);
	}
	else
		printf("received test cmd\n");
	free_split(cmds);
	return (0);
}

char	**clone_env(char **en)
{
	char	**env;
	int		i;

	i = 0;
	while (en[i])
		i++;
	env = (char **)malloc(sizeof(char *) * ++i);
	env[--i] = NULL;
	while (--i >= 0)
		env[i] = ft_strdup(en[i]);
	return (env);
}

int		shell(char **env)
{
	char	*cmd;
	char	**cmdsplit;
	int		i;

	while (1/*figure out way to know shell is alive*/)
	{
		ft_putstr("8==D~ ");
		get_next_line(0, &cmd);
		cmdsplit = ft_strsplit(cmd, ';');
		i = 0;
		while (cmdsplit[i])
			exec_cmds(cmdsplit[i++], env);
		free(cmd);
		free_split(cmdsplit);
	}
	return (0);
}

int		main(void)
{
	char	**env;

	env = clone_env(environ);
	return (shell(env));
}
