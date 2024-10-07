/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/30 11:10:47 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Ici ce sont les fonctions qui permettent d'envoyer le programme dans
 * les bonnes parties du code pour les builtins
 */
int	builtin_check(t_token *token)
{
	return (token->is_builtin);
}

void	builtin_selector(t_token *token, t_envp *envp)
{
	if (!ft_strcmp("cd", token->builtin_info))
		exe_cd(token->value, envp);
	if (!ft_strcmp("echo", token->builtin_info))
		exe_echo(token->value, envp);
	else if (!ft_strcmp("env", token->builtin_info))
		mini_env(envp);
	else if (!ft_strcmp("export", token->builtin_info))
		exe_export(envp, token->value);
	else if (!ft_strcmp("unset", token->builtin_info))
		exe_unset(envp, token->value);
	else if (!ft_strcmp("pwd", token->builtin_info))
		exe_pwd(envp);
	else if (!ft_strcmp("exit", token->builtin_info))
		exe_exit(token->value, envp, token);
}

void	builtin_selector_chevron(t_token *token, t_envp *envp)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (token->file_in_out)
		handle_redirections(token->file_in_out);
	if (!ft_strcmp("cd", token->builtin_info))
		exe_cd(token->file_in_out->value, envp);
	else if (!ft_strcmp("echo", token->builtin_info))
		exe_echo(token->file_in_out->value, envp);
	else if (!ft_strcmp("env", token->builtin_info))
		mini_env(envp);
	else if (!ft_strcmp("export", token->builtin_info))
		exe_export(envp, token->file_in_out->value);
	else if (!ft_strcmp("unset", token->builtin_info))
		exe_unset(envp, token->file_in_out->value);
	else if (!ft_strcmp("pwd", token->builtin_info))
		exe_pwd(envp);
	else if (!ft_strcmp("exit", token->builtin_info))
		exe_exit(token->file_in_out->value, envp, token);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
