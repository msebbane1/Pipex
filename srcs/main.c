/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:46:13 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/03 11:12:48 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
/*
fork() divisera notre processus en deux sous-processus : il renvoie 0 pour 
le processus enfant, un nombre différent de zéro pour le processus parent 
ou un -1 en cas d'erreur. Aussi: fork() divise le processus en deux processus
parallèles et simultanés, qui se produisent en même temps.
Le programme suivant crée un tube puis se dédouble pour créer un processus 
fils. 
Le processus fils hérite d'un ensemble dupliqué de descripteurs de fichier 
qui font référence au même tube. Après le fork(2), chaque processus ferme 
les descripteurs dont il n'a pas besoin pour le tube.
Le père écrit alors la chaîne contenue dans l'argument de la ligne 
de commande du programme et le fils lit cette chaîne, 
un octet à la fois, qu'il affiche sur sa sortie standard.
*/
void	parent_process(int fileout, char **argv, char **envp, int *end)
{
	dup2(end[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(end[1]);
	run(argv[3], envp);
}

void	child_process(int filein, char **argv, char **envp, int *end)
{
	dup2(end[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(end[0]);
	run(argv[2], envp);
}

void	pipex(int filein, int fileout, char **argv, char **envp)
{
	int		end[2];
	int		parent;

	if (pipe(end) == -1)
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
	parent = fork();
	if (parent == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (parent == 0)
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
