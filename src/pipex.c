/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:57:44 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/29 02:07:36 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <fcntl.h>
#include <stdlib.h>

static char	*path_parse(char *cmd, char **envp)
{
	char	**temp_path;
	char	*temp;
	char	*path;
	size_t	index;

	index = 0;
	while (ft_strnstr(envp[index], "PATH", 4) == 0)
		++index;
	temp_path = ft_split(envp[index] + 5, ':');
	if (temp_path == 0)
		ft_perror_exit("Path parse error", EXIT_FAILURE);
	index = 0;
	while (temp_path[index] != 0)
	{
		temp = ft_strjoin("/", cmd);
		path = ft_strjoin(temp_path[index], temp);
		free(temp);
		if (access(path, X_OK) == 0)
			return (path);
		index++;
		free(path);
		path = NULL;
	}
	return (path);
}

static void	command_excute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (cmd == 0)
		ft_perror_exit("Argv parse error", EXIT_FAILURE);
	path = path_parse(cmd[0], envp);
	if (path == 0)
		ft_perror_exit("Error", EXIT_NOT_COMMAND);
	if (execve(path, cmd, envp) == -1)
		ft_perror_exit("Error", EXIT_NOT_EXECUTE);
}

static void parent_process(pid_t pid, int fd[2], char **argv, char **envp)
{
	int	outfile;
	int	status;

	ft_close(fd[1]);
	waitpid(pid, &status, 0);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		ft_perror_exit("Error", EXIT_FAILURE);
	ft_dup2(fd[0], STDIN_FILENO);
	ft_close(fd[0]);
	ft_dup2(outfile, STDOUT_FILENO);
	ft_close(outfile);
	command_excute(argv[3], envp);
}

static void	child_process(int fd[2], char **argv, char **envp)
{
	int		infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		ft_perror_exit("Error", EXIT_FAILURE);
	ft_dup2(infile, STDIN_FILENO);
	ft_close(infile);
	ft_dup2(fd[1], STDOUT_FILENO);
	ft_close(fd[0]);
	ft_close(fd[1]);
	command_excute(argv[2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Error : Bad Argument\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!ft_pipe(fd))
		exit(EXIT_FAILURE);
	pid = ft_fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		child_process(fd, argv, envp);
	else
		parent_process(pid, fd, argv, envp);
	return (0);
}
