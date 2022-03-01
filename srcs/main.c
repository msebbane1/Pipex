/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:46:13 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/01 16:26:36 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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


void	parent_process(int fileout, char **argv, char **envp, int *end)
{
	dup2(fileout, STDIN_FILENO); // -> fileout is the stdout
	dup2(end[0], STDOUT_FILENO); // -> end[0] is the stdin
	close(end[1]); // fermeture du pipe qu'on utilise pas
	close(fileout);
	run(argv[3], envp); // execve function for each possible path (see below)
	exit(EXIT_SUCCESS);
}

void	child_process(int filein, char **argv, char **envp, int *end)
{
	dup2(filein, STDIN_FILENO); // -> (l'entree(filein) devient le vrai stdin) // we want filein to be execve() input
	dup2(end[1], STDOUT_FILENO); // -> La sortie standart deviens end[1] // we want end[1] to be execve() stdout
	close(end[0]); // fermeture du pipe qu'on utilise pas
	close(filein);
	run(argv[2], envp); // execve function for each possible path (see below)
	exit(EXIT_SUCCESS);
}

/*fork() divisera notre processus en deux sous-processus : il renvoie 0 pour le processus enfant, un nombre différent de zéro pour le processus parent ou un -1 en cas d'erreur.
Aussi: fork() divise le processus en deux processus parallèles et simultanés, qui se produisent en même temps. Ce sera important pour la section 2.
*/
void	pipex(int filein, int fileout, char **argv, char **envp)
{
	int		end[2];
	int		parent;

	pipe(end); // creation du tuyau
	parent = fork();
	if (pipe(end) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	if (parent == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (!parent) //  ou parent == 0 si fork() returns 0, we are in the child process
	{
		child_process(filein, argv, envp, end);
	}
	else
	{
		waidpid(parent, NULL, 0);
		parent_process(fileout, argv, envp, end);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	filein;
	int	fileout;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("filein failed");
		exit(EXIT_FAILURE);
	}
	fileout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (filein < 0 || fileout < 0)
		return (-1);
	pipex(filein, fileout, argv, envp);
	return (0);
}
