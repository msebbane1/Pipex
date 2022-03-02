/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:33:37 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/02 13:39:56 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


/* int execve(const char *fichier, char *const argv[], char *envp[]); execute le fichier
argv est un tableau de chaînes d'arguments passées au nouveau programme. envp est un tableau de chaînes, 
ayant par convention la forme clé=valeur, qui sont passées au nouveau programme comme environnement. 
argv ainsi que envp doivent se terminer par un pointeur NULL.
*/

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void	run(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;
	char	*path2;
	char	**mypaths;

	i = 0;
	mypaths = ft_split(get_path(envp), ':');
	cmd = ft_split(argv, ' ');
	i = 0;
	while (mypaths[i])
	{
		path = ft_strjoin(mypaths[i], "/");
		path2 = ft_strjoin(path, cmd[0]);
		execve(path2, cmd, envp);
		// if (execve(path2, cmd, envp)) //path
		// {
		// 	perror("command not found");
		// 	//exit(EXIT_FAILURE);
		// 	//free_tab(cmd);
		// }
		free(path2);
		free(path);
		i++;
	}
	
}



/*fonction qui va chercher la ligne du chemin inside de l'environement , 
il va split et tester chaque command du chemin et retourne la bonne*/
/*
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (0);
}*/