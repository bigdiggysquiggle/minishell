#ifndef SHELLSTRUCT_H
# define SHELLSTRUCT_H

typedef struct s_com	t_com;

struct s_com
{
	char *cmd;
	char **args;
};

#endif
