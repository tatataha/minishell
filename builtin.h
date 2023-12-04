#ifndef	BUILTIN_H
# define BUILTIN_H

#define NULL 0

#include "libft/libft.h"
#include "typeft.h"

int	ft_cd(char **env, char **arg);
int	ft_echo(char **arg);
int	ft_exit(char **arg);
void ft_export(char **arg, char **env);
int	ft_pwd(char **env, char **arg);
int	ft_unset(char **env, char **arg);

#endif