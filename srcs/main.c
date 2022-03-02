/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:46:13 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/02 16:21:38 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parent_process(int fileout, char **argv, char **envp, int *end)
{
	dup2(end[0], STDIN_FILENO); // -> end[0] is the stdin
	dup2(fileout, STDOUT_FILENO); // -> fileout is the stdout
	close(end[1]); // fermeture du pipe qu'on utilise pas
	run(argv[3], envp); // execve function for each possible path (see below)
}

void	child_process(int filein, char **argv, char **envp, int *end)
{
	dup2(end[1], STDOUT_FILENO); // -> (l'entree(filein) devient le vrai stdin) // we want filein to be execve() input
	dup2(filein, STDIN_FILENO); // -> La sortie standart deviens end[1] // we want end[1] to be execve() stdout
	close(end[0]);
	run(argv[2], envp);// execve function for each possible path (see below)
}

/*fork() divisera notre processus en deux sous-processus : il renvoie 0 pour le processus enfant, un nombre différent de zéro pour le processus parent ou un -1 en cas d'erreur.
Aussi: fork() divise le processus en deux processus parallèles et simultanés, qui se produisent en même temps. Ce sera important pour la section 2.
*/
void	pipex(int filein, int fileout, char **argv, char **envp)
{
	int		end[2];
	int		parent;

	//pipe(end); // creation du tuyau
	//parent = fork();
	if (pipe(end) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	parent = fork();
	if (parent == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (parent == 0) //  ou !parent == 0 si fork() returns 0, we are in the child process
		child_process(filein, argv, envp, end);
	else
	{
		waitpid(parent, NULL, 0);
		parent_process(fileout, argv, envp, end);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	filein;
	int	fileout;

	if (argc == 5)
	{
		filein = open(argv[1], O_RDONLY, 0777);
		if (filein == -1)
		{
			perror("filein failed");
			exit(EXIT_FAILURE);
		}
		fileout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fileout == -1)
		{
			perror("fileout failed");
			exit(EXIT_FAILURE);
		}
		pipex(filein, fileout, argv, envp);
	}
	else
		ft_putstr_fd("Missing arguments or files", 2);
	return (0);
}
