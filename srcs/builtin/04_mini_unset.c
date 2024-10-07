/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:55:21 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/27 15:24:28 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	shift_env_vars(char **env, int start)
// {
// 	int	j;

// 	j = start;
// 	while (env[j])
// 	{
// 		env[j] = env[j + 1];
// 		j++;
// 	}
// 	env[j] = NULL;
// }

// void	unset_variable(t_envp *envp, const char *var)
// {
// 	int	i;
// 	int	var_len;

// 	if (ft_strcmp(var, "_") == 0)
// 		return ;
// 	i = 0;
// 	var_len = ft_strlen(var);
// 	while (envp->env[i])
// 	{
// 		if (ft_strncmp(envp->env[i], var, var_len) == 0
// 			&& envp->env[i][var_len] == '=')
// 		{
// 			free(envp->env[i]);
// 			shift_env_vars(envp->env, i);
// 			break ;
// 		}
// 		i++;
// 	}
// }

// /**
//  * Fonction qui permet de supprimer un variable d'env
//  */
// void	exe_unset(t_envp *envp, char *args)
// {
// 	char	**variables;
// 	int		i;

// 	i = 0;
// 	variables = ft_split(args, ' ');
// 	while (variables[i])
// 	{
// 		unset_variable(envp, variables[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (variables[i])
// 	{
// 		free(variables[i]);
// 		i++;
// 	}
// 	free(variables);
// }

/*
char	**copy_env_without_var(char **env, const char *var)
{
	int		i, j, count, var_len;
	char	**new_env;

	// Compter le nombre de variables restantes
	count = 0;
	var_len = ft_strlen(var);
	for (i = 0; env[i]; i++)
	{
		if (!(ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '='))
			count++;
	}

	// Allouer le nouveau tableau
	new_env = malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);  // Gérer l'erreur d'allocation

	// Copier les variables restantes
	j = 0;
	for (i = 0; env[i]; i++)
	{
		if (!(ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '='))
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
	}
	new_env[j] = NULL;  // Terminer le nouveau tableau par NULL

	return (new_env);
}

void	exe_unset(t_envp *envp, char *args)
{
	char	**variables;
	char	**new_env;
	int		i;

	i = 0;
	variables = ft_split(args, ' ');
	while (variables[i])
	{
		new_env = copy_env_without_var(envp->env, variables[i]);
		if (new_env)
		{
			free_env(envp->env);  // Libérer l'ancien tableau
			envp->env = new_env;  // Remplacer par le nouveau tableau
		}
		i++;
	}

	// Libérer les arguments
	i = 0;
	while (variables[i])
	{
		free(variables[i]);
		i++;
	}
	free(variables);
}

void	free_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);  // Libérer chaque chaîne de caractères dans le tableau
		i++;
	}
	free(env);  // Libérer le tableau lui-même
}
*/

bool	should_copy_env_var(const char *env_var, const char *var, int var_len)
{
	return (!(ft_strncmp(env_var, var, var_len)
			== 0 && env_var[var_len] == '='));
}

void	fill_new_env(char **env, char **new_env,
	const char *var, int var_len)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (env[i])
	{
		if (should_copy_env_var(env[i], var, var_len))
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	new_env[j] = NULL;
}

char	**copy_env_without_var(char **env, const char *var)
{
	int		i;
	int		count;
	int		var_len;
	char	**new_env;

	var_len = ft_strlen(var);
	count = 0;
	i = 0;
	while (env[i])
	{
		if (should_copy_env_var(env[i], var, var_len))
			count++;
		i++;
	}
	new_env = safe_malloc((count + 1) * sizeof(char *));
	fill_new_env(env, new_env, var, var_len);
	return (new_env);
}

void	exe_unset(t_envp *envp, char *args)
{
	char	**vars;
	char	**new_env;
	int		i;

	vars = ft_split(args, ' ');
	i = 0;
	while (vars[i])
	{
		new_env = copy_env_without_var(envp->env, vars[i]);
		if (new_env)
		{
			free_env(envp->env);
			envp->env = new_env;
		}
		i++;
	}
	i = 0;
	while (vars[i])
		free(vars[i++]);
	free(vars);
	envp->status_cmd = 0;
}

void	free_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}
