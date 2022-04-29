/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:57:44 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/29 10:53:06 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

// static int	get_exit_status(int status)
// {
// 	if (ft_wifexited(status))
// 		return (ft_wexitstatus(status));
// 	if (ft_wifsignaled(status))
// 		return (ft_wtermsig(status) + EXIT_SIGNAL);
// 	if (ft_wifstopped(status))
// 		return (STOP_SIGNAL + EXIT_SIGNAL);
// 	return (CONTINUE_SIGNAL + EXIT_SIGNAL);
// }

static void	putstr_error(char *str, char *argv, int exit_status)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (argv)
	{
		if (exit_status != EXIT_NOT_COMMAND)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	exit(exit_status);
}

static char **get_path(char **envp)
{
	size_t	index;

	index = 0;
	while (*envp && (ft_strnstr(envp[index], "PATH", 4) == 0))
		++index;
	if (!(*envp))
		putstr_error("Error : No Path\n", NULL, 127);
	return (ft_split(envp[index] + 5, ':'));
}

static char	*cmd_parse(char *cmd, char **paths)
{
	char	*temp;
	char	*path;
	int		err;
	size_t	index;

	index = -1;
	err = access(cmd, X_OK);
	if (err == 0)
		return (cmd);
	temp = ft_strjoin("/", cmd);
	while (paths[++index] != 0)
	{
		path = ft_strjoin(paths[index], temp);
		err = access(path, X_OK);
		if (err == 0)
		{
			free(temp);
			return (path);
		}
		free(path);
	}
	free(temp);
	putstr_error("Error: command not found: ", cmd, EXIT_NOT_COMMAND);
	return (NULL);
}

static void	command_excute(char *argv, char **envp)
{
	char	**cmd;
	char	**paths;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (cmd == 0)
		putstr_error("Error: Bad cmd split\n", NULL, EXIT_FAILURE);
	paths = get_path(envp);
	if (paths == 0)
		putstr_error("Error: Bad path split\n", NULL, EXIT_FAILURE);
	path = cmd_parse(cmd[0], paths);
	if (execve(path, cmd, envp) == -1)
		exit(EXIT_NOT_EXECUTE);
}

static void parent_process(pid_t pid, int fd[2], char **argv, char **envp)
{
	int	outfile;
	// int	status;

	ft_close(fd[1]);
	ft_waitpid(pid, NULL, 0);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		// ft_perror_exit("Error", EXIT_FAILURE);
		putstr_error("Error", argv[4], EXIT_FAILURE);
	ft_dup2(fd[0], STDIN_FILENO);
	ft_dup2(outfile, STDOUT_FILENO);
	ft_close(fd[0]);
	ft_close(outfile);
	command_excute(argv[3], envp);
}

static void	child_process(int fd[2], char **argv, char **envp)
{
	int		infile;

	ft_close(fd[0]);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		// ft_perror_exit("Error", EXIT_FAILURE);
		putstr_error("Error", argv[1], EXIT_FAILURE);
	ft_dup2(infile, STDIN_FILENO);
	ft_close(infile);
	ft_dup2(fd[1], STDOUT_FILENO);
	ft_close(fd[1]);
	command_excute(argv[2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		putstr_error("Error: Bad argument\n", NULL, EXIT_FAILURE);
	ft_pipe(fd);
	pid = ft_fork();
	if (pid == 0)
		child_process(fd, argv, envp);
	else
		parent_process(pid, fd, argv, envp);
	return (0);
}
