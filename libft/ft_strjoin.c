/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:36:21 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/01 15:17:50 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*ft_strcat(char *dest, char const *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
	return (dest);
}

/** 
 * strjoin crée une chaîne composée de l'élément str1 concaténé avec 
 * l'élément str2. La chaîne renvoyée est allouée à l'extérieur 
 * de la mémoire de travail. 
 * Si l'espace de travail disponible est insuffisant, strjoin ne s'exécute 
 * pas et une erreur est générée.
 **/
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size_s1;
	int		size_s2;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	join = (char *) malloc(sizeof(char) * (size_s1 + size_s2) + 1);
	if (!join)
		return (NULL);
	*join = 0;
	ft_strcat(join, s1);
	ft_strcat(join, s2);
	return (join);
}
