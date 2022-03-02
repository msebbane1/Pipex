/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:50:15 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/02 11:36:19 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*dest;

	i = 0;
	size = ft_strlen(s);
	dest = (char *) malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/** 
 * Alloue avec malloc et retourne une chaine de caractères 
 * issue de la chaine ’s’. Cette nouvelle chaine commence à l’index ’start’ et
 * a pour taille maximale ’len’ La fonction substr renvoie une partie 
 * d'une chaîne.
 **/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size_s;

	i = 0;
	size_s = ft_strlen(s);
	if (!s)
		return (NULL);
	if (size_s <= start)
		return (ft_strdup(""));
	if (size_s < len)
		len = size_s;
	str = (char *) malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (start < size_s && i < len && i + start < size_s)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
