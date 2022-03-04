/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:33:37 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/03 11:40:58 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* int execve(const char *fichier, char *const argv[], char *envp[]); 
execute le fichier argv est un tableau de chaînes d'arguments passées 
au nouveau programme. envp est un tableau de chaînes, 
ayant par convention la forme clé=valeur, qui sont passées au nouveau 
programme comme environnement.
*/

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*get_p(char *p, char *cmd)
{
	char	*path;

	path = ft_strjoin(p, cmd);
	free(p);
	return (path);
}

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void	run(char *argv, char **envp)
{
	char	**cmd;
	char	**mypaths;
	char	*path;
	int		i;
	int		exec;

	mypaths = ft_split(get_path(envp), ':');
	cmd = ft_split(argv, ' ');
	i = 0;
	exec = 0;
	while (mypaths[i])
	{
		path = get_p(ft_strjoin(mypaths[i], "/"), cmd[0]);
		if (execve(path, cmd, envp) == 0)
			exec = 1;
		free(path);
		i++;
	}
	free_tab(mypaths);
	free_tab(cmd);
	if (exec == 0)
	{
		perror("Error bad commands");
		exit(EXIT_FAILURE);
	}
}
