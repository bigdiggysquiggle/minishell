/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:10:56 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/18 17:53:55 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
** writing to standard input does print to the terminal
*/

t_builtin	g_builtin[] =
{
	{"echo", &ft_echo},
	{"exit", &ft_exit},
	{"env", &ft_env},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"cd", &ft_cd},
	{NULL, NULL}
};

void	free_split(char **cmdsplit)
{
	int		i;

	i = 0;
	if (cmdsplit)
	{
		while (cmdsplit[i])
			free(cmdsplit[i++]);
		free(cmdsplit);
	}
}

char	**exec_cmds(char *cmd, char **env)
{
	char	**cmds;
	int		i;

	cmds = cmd_split(cmd, " \t\n\r\a");
	cmds = strip_quotes(cmds);
	cmds = expand_dollar(cmds, env);
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
	if (!env)
	{
		ft_printf("failed to set up environment\n");
		exit(1);
	}
	env[--i] = NULL;
	while (--i >= 0)
		env[i] = ft_strdup(en[i]);
	return (env);
}

/*
** consider new way of checking shell activity
*/

int		shell(char **env)
{
	char	*cmd;
	char	**cmdsplit;
	int		i;

	while (1)
	{
		ft_putstr("8==D~ ");
		get_next_line(0, &cmd);
		while (!count_quotes(cmd))
			cmd = get_quotes(cmd);
		cmdsplit = cmd_split(cmd, ";");
		i = 0;
		while (cmdsplit[i])
			env = exec_cmds(cmdsplit[i++], env);
		free(cmd);
		free_split(cmdsplit);
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	char	**env;

	env = clone_env(envp);
	return (shell(env));
	(void)argc;
	(void)argv;
}
