/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/02 13:52:59 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_exec(t_token *token, t_envp *envp, t_signal *handler)
{
	t_token	*current;
	int		pipe;
	int		redirection;

	current = token;
	pipe = 0;
	redirection = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			pipe = 1;
			break ;
		}
		if (current->file_in_out != NULL)
			redirection = 1;
		current = current->next;
	}
	if (pipe == 1)
		execute_pipes(token, envp, handler);
	else if (redirection == 1)
		main_command_chevron(token, envp, handler);
	else
		main_command(token, envp, handler);
}

void	main_command(t_token *token, t_envp *envp, t_signal *handler)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			if (builtin_check(current))
				builtin_selector(current, envp);
			else
			{
				execute_execve(current, envp, handler);
			}
		}
		current = current->next;
	}
}

void	main_command_chevron(t_token *token, t_envp *envp, t_signal *handler)
{
	t_token			*current;
	int				saved_stdin;
	int				saved_stdout;
	t_process_data	args;

	current = token;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			args.token = current;
			args.envp = envp;
			args.handler = handler;
			args.in = saved_stdin;
			args.out = saved_stdout;
			create_child_process(&args);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		current = current->next;
	}
	close(saved_stdin);
	close(saved_stdout);
}
