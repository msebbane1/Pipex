/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:33:37 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/01 16:26:47 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// parsing (somewhere in your code)
/*
char *PATH_from_envp;
char **mypaths;
char **mycmdargs;
// recuperer the line PATH from envp
PATH_from_envp = ft_substr(envp ....);
mypaths = ft_split(PATH_from_envp, ":"); // see section 4 for a
                                            small note[0]
mycmdargs = ft_split(ag[2], " ");
// in your child or parent process
int  i;
char *cmd;
i = -1;
while (mypaths[++i])
{
    cmd = ft_join(mypaths[i], ag[2]); // protect your ft_join
    execve(cmd, mycmdargs, envp); // if execve succeeds, it exits
    // perror("Error"); <- add perror to debug
    free(cmd) // if execve fails, we free and we try a new path
}
return (EXIT_FAILURE);*/
/*Fonction excuve*/
/*
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}*/

/*fonction qui va chercher la ligne du chemin inside de l'environement , 
il va split et tester chaque command du chemin et retourne la bonne*/
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
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}
/* int execve(const char *fichier, char *const argv[], char *envp[]); execute le fichier
argv est un tableau de chaînes d'arguments passées au nouveau programme. envp est un tableau de chaînes, 
ayant par convention la forme clé=valeur, qui sont passées au nouveau programme comme environnement. 
argv ainsi que envp doivent se terminer par un pointeur NULL.
*/
void	run(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		perror("cmd error");
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("execve error");
		exit(EXIT_FAILURE);
	}
}
// parsing (somewhere in your code)
/*
char *PATH_from_envp;
char **mypaths;
char **mycmdargs;
// recuperer the line PATH from envp
PATH_from_envp = ft_substr(envp ....);
mypaths = ft_split(PATH_from_envp, ":"); // see section 4 for a
                                            small note[0]
mycmdargs = ft_split(ag[2], " ");
// in your child or parent process
int  i;
char *cmd;
i = -1;
while (mypaths[++i])
{
    cmd = ft_join(mypaths[i], ag[2]); // protect your ft_join
    execve(cmd, mycmdargs, envp); // if execve succeeds, it exits
    // perror("Error"); <- add perror to debug
    free(cmd) // if execve fails, we free and we try a new path
}
return (EXIT_FAILURE);*/


//Fonction qui prend la command et l'envoi a find_path avant de l'executer
/*
void	execute(char *argv, char **envp)
{
	char	*PATH_from_envp;
	char	**mypaths;
	char	**mycmdargs
	int		i;
	char	*cmd;
	// recuperer the line PATH from envp
	PATH_from_envp = ft_substr(envp ....);
	mypaths = ft_split(PATH_from_envp, ":");
	mycmdargs = ft_split(ag[2], " ");
	i = -1;
	while (mypaths[++i])
	{
    	cmd = ft_join(mypaths[i], ag[2]); // protect your ft_join
    	execve(cmd, mycmdargs, envp); // if execve succeeds, it exits
    	// perror("Error"); <- add perror to debug
    	free(cmd); // if execve fails, we free and we try a new path
	}
}*/