/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:10:56 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/05 04:09:02 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*You must implement a series of builtins: echo, cd, setenv, unsetenv, env, exit.*/
/* $PATH and other such environment variables should be easy to implement */

extern char	**environ;

typedef struct s_builtin	t_builtin;

struct	s_builtin
{
	char	*name;
	char	**(*builtin)(char **, char **);
};

t_builtin	g_builtin[] =
{
	{"echo", &ft_echo},
	{"exit", &ft_exit},
	{"env", &ft_env},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{NULL, NULL}
};

void	free_split(char **cmdsplit)
{
	int		i;

	i = 0;
	while (cmdsplit[i])
		free(cmdsplit[i++]);
	free(cmdsplit);
}

char	**exec_cmds(char *cmd, char **env)
{
	char	**cmds;
	int		i;

	cmds = cmd_split(cmd, " \t\n\r\a");
	i = 0;
	while (g_builtin[i].name && !ft_strequ(g_builtin[i].name, cmds[0]))
		i++;
	if (g_builtin[i].name)
		env = g_builtin[i].builtin(cmds, env);
	else
		execute_nonbuiltin(cmds, env);
	free_split(cmds);
	return (env);
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
			env = exec_cmds(cmdsplit[i++], env);
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
