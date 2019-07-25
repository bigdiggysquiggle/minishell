/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:21:40 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/24 16:38:05 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include "libft.h"
# include "signal.h"
# define PROMPT "()==[:::::::::::::> "

char	**cmd_split(char const *s, char *c);
void	free_split(char **cmdsplit);
char	**expand_dollar(char **args, char **env);
/*
** leaving this declaration here just in case I need it
** int		is_arg_dollar(char *s);
*/
char	*exp_from_env(char **arg, int i, char **env);
char	**handle_expansion_tmp(char **exp, char *tmp, char **env, int mode);
char	*contract_path(char **paths, char *d);
int		count_quotes(char *st);
char	*get_quotes(char *st);
char	**strip_quotes(char **args);
int		cd_check(char *path, char **env);

char	**ft_echo(char **args, char **env);
char	**ft_env(char **args, char **env);
char	**ft_setenv(char **args, char **env);
char	**ft_unsetenv(char **args, char **env);
char	**ft_cd(char **args, char **env);
char	**squirrel(char **args, char **env);
int		execute_nonbuiltin(char **args, char **env);

void	sig_process(int sig);
void	sig_main(int sig);

typedef struct s_builtin	t_builtin;

struct	s_builtin
{
	char	*name;
	char	**(*builtin)(char **, char **);
};

#endif
