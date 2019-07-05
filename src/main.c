/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:10:56 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/04 20:43:04 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

extern char	**environ;

int		exec_cmds(char *cmd, char **env)
{
	char	**cmds;

	cmds = ft_strsplit(cmd, ' ');//need to make cut all white space
	if (ft_strequ(cmds[0], "env"))
	{
		int i = 0;
		while (env[i])
			printf("%s\n", env[i++]);
	}
	else
		printf("received test cmd\n");
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

void	free_split(char **cmdsplit)
{
	int		i;

	i = 0;
	while (cmdsplit[i])
		free(cmdsplit[i++]);
	free(cmdsplit);
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
