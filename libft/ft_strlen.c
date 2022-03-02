/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:08:37 by marvin            #+#    #+#             */
/*   Updated: 2022/03/02 15:56:17 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)big;
	if (little[0] == '\0')
		return (str);
	while (str[j] && little[i] && j < len)
	{
		if (little[i] == str[j])
			i++;
		else
		{
			j = j - i;
			i = 0;
		}
		j++;
	}
	if (little[i] == '\0')
		return (str + j - i);
	return (0);
}

/** 
 * Calcule la longueur d'une chaîne de caractères.
 **/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
