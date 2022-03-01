/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:46:13 by msebbane          #+#    #+#             */
/*   Updated: 2022/03/01 15:25:38 by msebbane         ###   ########.fr       */
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
}

void	parent_process(int fileout, char *cmd2, int *end)
{
	dup2(fileout, STDIN_FILENO); // -> // fileout is the stdout
	dup2(end[0], STDOUT_FILENO); // -> end[0] is the stdin
	close(end[1]); // fermeture du pipe qu'on utilise pas
	close(fileout);
	//execute(argv[3], cmd1); // execve function for each possible path (see below)
}

void	child_process(int filein, char *cmd1, int *end)
{
	dup2(filein, STDIN_FILENO); // -> (l'entree(filein) devient le vrai stdin) // we want filein to be execve() input
	dup2(end[1], STDOUT_FILENO); // -> La sortie standart deviens end[1] // we want end[1] to be execve() stdout
	close(end[0]); // fermeture du pipe qu'on utilise pas
	close(filein);
	//execute(argv[2], cmd1); // execve function for each possible path (see below)
}

/*fork() divisera notre processus en deux sous-processus : il renvoie 0 pour le processus enfant, un nombre différent de zéro pour le processus parent ou un -1 en cas d'erreur.
Aussi: fork() divise le processus en deux processus parallèles et simultanés, qui se produisent en même temps. Ce sera important pour la section 2.
*/
void	pipex(int filein, int fileout, char *cmd1, char *cmd2)
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
		child_process(filein, cmd1, end);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waidpid(parent, NULL, 0);
		parent_process(fileout, cmd2, end);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	filein;
	int	fileout;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("filein");
		exit(EXIT_FAILURE);
	}
	fileout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (filein < 0 || fileout < 0)
		return (-1);
	pipex(filein, fileout, argv, envp);
	return (0);
}