/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:29:48 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/14 12:32:49 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim, char **saveptr)
{
	char	*start;
	char	*token;

	if (str)
		*saveptr = str;
	if (!*saveptr)
		return (NULL);
	start = *saveptr + ft_strspn(*saveptr, delim);
	if (*start == '\0')
	{
		*saveptr = NULL;
		return (NULL);
	}
	token = start;
	*saveptr = ft_strpbrk(start, delim);
	if (*saveptr)
		*(*saveptr)++ = '\0';
	return (token);
}
