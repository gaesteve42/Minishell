/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_mini_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:51 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:51 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * permet de recuperer le path 
 * sans passer par l'env car utilisation de la fonction 'getcwd'
 */
int	exe_pwd(t_envp *envp)
{
	char	temp[1024];

	if (getcwd(temp, sizeof(temp)) == NULL)
		return (error_flag(envp), 1);
	printf("%s\n", temp);
	envp->status_cmd = 0;
	return (0);
}
