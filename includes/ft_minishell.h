#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include "libft.h"

char	**cmd_split(char const *s, char *c);
void	free_split(char **cmdsplit);
char	**expand_dollar(char **args, char **env);
/*int		is_arg_dollar(char *s);*/
char	*exp_from_env(char **arg, int i, char **env);
char	*contract_path(char **paths, char *d);
int		count_quotes(char *st);
char	*get_quotes(char *st);
char	**strip_quotes(char **args);

char	**ft_echo(char **args, char **env);
char	**ft_exit(char **args, char **env);
char	**ft_env(char **args, char **env);
char	**ft_setenv(char **args, char **env);
char	**ft_unsetenv(char **args, char **env);
char	**ft_cd(char **args, char **env);
int		execute_nonbuiltin(char **args, char **env);

#endif
