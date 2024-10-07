/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:57:36 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/02 13:52:37 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_global_sig = 0;

void	init_mask(struct sigaction *sig)
{
	sigemptyset(&sig->sa_mask);
	sigaddset(&sig->sa_mask, SIGINT);
	sigaddset(&sig->sa_mask, SIGQUIT);
}

void	init_sigaction(struct sigaction *sig)
{
	sig->sa_flags = SA_SIGINFO;
	sig->sa_sigaction = &signal_handler;
	sigaction(SIGINT, sig, NULL);
	sig->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sig, NULL);
}

void	init_signal(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(struct sigaction));
	init_mask(&sig);
	init_sigaction(&sig);
}

void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
		g_global_sig = 130;
	}
}

pid_t	fork_and_execute(char *cmd_path, char **split_args, t_envp *envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		execve_error_handling(cmd_path, split_args, envp);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
