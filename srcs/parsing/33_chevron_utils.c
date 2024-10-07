/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_chevron_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:09:38 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/02 16:01:42 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_chevron_type_str(t_chevron_type type)
{
	if (type == IN)
		return ("IN");
	else if (type == DOUBLE_IN)
		return ("DOUBLE_IN");
	else if (type == OUT)
		return ("OUT");
	else if (type == DOUBLE_OUT)
		return ("DOUBLE_OUT");
	else
		return ("COMMAND");
}

void	print_chevron_node(t_token *token)
{
	t_chevron	*current_chevron;
	int			i;

	current_chevron = token->file_in_out;
	i = 1;
	while (current_chevron)
	{
		printf("\n	Node n°%d\n", i);
		printf("	Type : %s\n", get_chevron_type_str(current_chevron->type));
		printf("	Value: %s\n", current_chevron->value);
		printf("	-------------\n");
		current_chevron = current_chevron->next;
		i++;
	}
}

// Fonction pour vérifier si le caractère est une quote
static bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

// Fonction pour vérifier si le caractère est un chevron
static bool	is_chevron(char c)
{
	return (c == '<' || c == '>');
}

// Fonction pour vérifier si les chevrons sont présents en dehors des quotes
int	contains_chevrons(const char *str)
{
	bool	in_quotes;
	char	current_quote;

	in_quotes = false;
	current_quote = '\0';
	while (*str)
	{
		if (is_quote(*str))
		{
			if (in_quotes && *str == current_quote)
			{
				in_quotes = false;
				current_quote = '\0';
			}
			else if (!in_quotes)
			{
				in_quotes = true;
				current_quote = *str;
			}
		}
		else if (is_chevron(*str) && !in_quotes)
			return (1);
		str++;
	}
	return (0);
}
