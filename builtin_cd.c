/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhcelik <muhcelik@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:23:09 by muhcelik          #+#    #+#             */
/*   Updated: 2023/12/14 14:27:50 by muhcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env_util.h"
#include "error.h"
#include "libft/libft.h"

#define PATH_MAX 1024

int	chg_dir(char *path)
{
	char	*ret;
	char	pwd[PATH_MAX];
	char	*oldpwd;

	oldpwd = getcwd(pwd, PATH_MAX);
	if (chdir(path) != 0)
		return (errorer("cd", path, "change directory failure", EXIT_FAILURE));
	ret = getcwd(pwd, PATH_MAX);
	if (!ret)
	{
		return (errorer("cd", path,
				"getcwd : error retrieving current directory", EXIT_FAILURE));
		ret = ft_strdup(path);
	}
	else
		ret = ft_strdup(pwd);
	ret = ft_strjoin("PWD=", ret);
	oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	env_remove("PWD");
	env_add(ret);
	env_remove("OLDPWD");
	env_add(oldpwd);
	free(ret);
	free(oldpwd);
	return (0);
}

int	ft_cd(char *arg)
{
	char	*path;

	if (!arg || arg[0] == ' '
		|| arg[0] == '\0' || ft_strncmp(arg, "--", 3) == 0)
	{
		path = (char *)ft_getenv("HOME");
		if (!path || *path == '\0' || *path == ' ')
			return (errorer("cd", 0, "HOME not set", EXIT_FAILURE));
		if (chg_dir(path) != 0)
			return (1);
		return (0);
	}
	if (ft_strncmp(arg, "-", 2) == 0)
	{
		path = (char *)ft_getenv("OLDPWD");
		if (!path)
			return (errorer("cd", 0, "OLDPWD not set", EXIT_FAILURE));
		if (chg_dir(path) != 0)
			return (1);
		return (0);
	}
	if (chg_dir(arg) != 0)
		return (1);
	return (0);
}
