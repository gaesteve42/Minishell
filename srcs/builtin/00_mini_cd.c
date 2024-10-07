/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_mini_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:31:46 by yonieva           #+#    #+#             */
/*   Updated: 2024/08/12 22:31:46 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction built-in qui permet de naviger dans les repertoires.
 */
/*
int	exe_cd(char *input, t_envp *envp)
{
	char	*old_pwd;
	char	*new_pwd;
	char	cwd[BUFFER_SIZE];
	char	*path;
	char	*home_path = NULL;

	if (ft_strncmp(input, "cd", 2) != 0)
		return (-1);
	path = input + 2;
	while (*path == ' ')
		path++;
	if (*path == '\0' || ft_strcmp(path, "~") == 0)
	{
		home_path = get_env_value("HOME", envp->env);
		if (!home_path)
			return (printf("cd: HOME not set\n"), 1);
		path = home_path;
	}
	old_pwd = getcwd(cwd, sizeof(cwd));
	if (!old_pwd)
		return (error_flag(), 1);
	if (chdir(path) != 0)
	{
		if (home_path)
			free(home_path);
		return (printf("cd: no such file or directory: %s\n", path), 1);
	}
	new_pwd = getcwd(cwd, sizeof(cwd));
	if (!new_pwd)
	{
		if (home_path)
			free(home_path);
		return (error_flag(), 1);
	}
	set_env_value(envp->env, "OLDPWD", old_pwd);
	set_env_value(envp->env, "PWD", new_pwd);
	if (home_path)
		free(home_path);
	return (0);
}
*/

char	*parse_cd_path(char *input)
{
	char	*path;

	if (ft_strncmp(input, "cd", 2) != 0)
		return (NULL);
	path = input + 2;
	while (*path == ' ')
		path++;
	return (path);
}

char	*handle_home_path(char *path, t_envp *envp, char **home_path)
{
	if (*path == '\0' || ft_strcmp(path, "~") == 0)
	{
		*home_path = get_env_value("HOME", envp->env);
		if (!*home_path)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
		return (*home_path);
	}
	return (path);
}

int	check_directory(char *path, char *home_path)
{
	if (chdir(path) != 0)
	{
		if (home_path)
			free(home_path);
		printf("cd: no such file or directory: %s\n", path);
		return (1);
	}
	return (0);
}

int	update_pwd_env(t_envp *envp, char *old_pwd, char *new_pwd, char *home_path)
{
	set_env_value(envp->env, "OLDPWD", old_pwd);
	set_env_value(envp->env, "PWD", new_pwd);
	if (home_path)
		free(home_path);
	return (0);
}

int	exe_cd(char *input, t_envp *envp)
{
	char	*old_pwd;
	char	*new_pwd;
	char	cwd[BUFFER_SIZE];
	char	*path;
	char	*home_path;

	home_path = NULL;
	path = parse_cd_path(input);
	if (!path)
		return ((error_flag(envp), -1));
	path = handle_home_path(path, envp, &home_path);
	if (!path)
		return (error_flag(envp), 1);
	old_pwd = getcwd(cwd, sizeof(cwd));
	if (!old_pwd)
		return (error_flag(envp), 1);
	if (check_directory(path, home_path) != 0)
		return (error_flag(envp), 1);
	new_pwd = getcwd(cwd, sizeof(cwd));
	if (!new_pwd)
		return ((handle_new_pwd_error(home_path, envp)));
	envp->status_cmd = 0;
	return (update_pwd_env(envp, old_pwd, new_pwd, home_path));
}
