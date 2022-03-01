/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:46:27 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/01 14:49:59 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_sep(char c, char sep)
{
	if (c == sep || c == '\0')
		return (1);
	return (0);
}

int	ft_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (!(ft_sep(s[i], c)) && ft_sep(s[i + 1], c))
			word++;
		i++;
	}
	return (word);
}

int	ft_count_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (!ft_sep(s[i], c))
		i++;
	return (i);
}

char	*ft_wordcpy(char const *s, int start, int size)
{
	char	*str;
	int		i;

	str = (char *) malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * Alloue (avec malloc) et retourne un tableau
 * de chaines de caracteres obtenu en séparant ’s’ à
 * l’aide du caractère ’c’, utilisé comme délimiteur.
 * Le tableau doit être terminé par NULL. 
**/
char	**ft_split(char const *s, char c)
{
	char	**str;
	int		index_s;
	int		size_word;
	int		i;

	str = (char **) malloc(sizeof(char *) * ft_word(s, c) + 1);
	if (!str)
		return (NULL);
	index_s = 0;
	i = 0;
	while (s[index_s])
	{
		if (ft_sep(s[index_s], c))
			index_s++;
		else
		{
			size_word = ft_count_word(s + index_s, c);
			str[i++] = ft_wordcpy(s, index_s, size_word);
			index_s += size_word;
		}
	}
	str[i] = NULL;
	return (str);
}
