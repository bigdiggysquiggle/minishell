#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include "libft.h"

char	**cmd_split(char const *s, char *c);
void	free_split(char **cmdsplit);

char	**ft_echo(char **args, char **env);
char	**ft_exit(char **args, char **env);
char	**ft_env(char **args, char **env);
char	**ft_setenv(char **args, char **env);
char	**ft_unsetenv(char **args, char **env);

#endif
