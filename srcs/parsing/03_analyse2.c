/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_analyse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:33:42 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/20 13:58:03 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonctions qui permettent la transformation des chaine de char
 * pour les passer au bon format :
 * 1. fermer les quotes si ce n'a pas été fait.
 * 2. retirer les espaces qui ne devrai pas etre present.
 */

void	check_quotes(const char *str, bool *s_q_open, bool *d_q_open)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			*s_q_open = !*s_q_open;
		else if (str[i] == '"')
			*d_q_open = !*d_q_open;
		i++;
	}
}

char	*close_quotes_if_needed(char *str)
{
	int		len;
	char	*new_str;
	bool	single_quote_open;
	bool	double_quote_open;

	single_quote_open = false;
	double_quote_open = false;
	check_quotes(str, &single_quote_open, &double_quote_open);
	len = ft_strlen(str);
	new_str = safe_malloc(len + 2);
	ft_strcpy(new_str, str);
	if (single_quote_open)
		new_str[len++] = '\'';
	else if (double_quote_open)
		new_str[len++] = '"';
	new_str[len] = '\0';
	return (new_str);
}

char	*clean_whitespace(char *str)
{
	int		i;
	int		j;
	char	*cleaned_str;

	i = 0;
	j = 0;
	cleaned_str = safe_malloc(ft_strlen(str) + 1);
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		cleaned_str[j++] = str[i];
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			while (str[i] == ' ')
				i++;
			continue ;
		}
		i++;
	}
	if (j > 0 && cleaned_str[j - 1] == ' ')
		j--;
	cleaned_str[j] = '\0';
	return (cleaned_str);
}

void	finalize_parsing(t_token *new_node, char **tokenarray)
{
	t_token	*current;

	current = new_node;
	while (current)
	{
		if (current != NULL && current->next == NULL)
			current->is_last_command = 1;
		current = current->next;
	}
	if (tokenarray != NULL)
		free_token_array(tokenarray);
}

int	check_onlyspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32 && str[i] != 9)
			return (0);
		i++;
	}
	return (1);
}
