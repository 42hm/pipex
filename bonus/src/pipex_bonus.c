/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 09:10:11 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/30 23:17:30 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
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
	if (!(*envp))
		return (0);
		// putstr_error("Error : No Path\n", NULL, EXIT_);
	while (*envp && (ft_strnstr(envp[index], "PATH", 4) == 0))
		++index;
	if (envp[index] == 0)
		return (0);
	return (ft_split(envp[index] + 5, ':'));
}

static char	*cmd_parse(char *cmd, char **paths)
{
	char	*temp;
	char	*path;
	int		err;
	size_t	index;

	index = -1;
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
	err = access(cmd, X_OK);
	if (err == 0)
		return (cmd);
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
	if (paths == 0 && access(cmd[0], X_OK) == -1)
		putstr_error("Error: command not found: ", cmd[0], EXIT_NOT_COMMAND);
	path = cmd_parse(cmd[0], paths);
	if (execve(path, cmd, envp) == -1)
		exit(EXIT_NOT_EXECUTE);
}

// static void	move_next_pipe(t_pipe *pipe)
// {
// 	if (pipe->prev[0] == -1)
// 		ft_close(pipe->prev[0]);
// 	if (pipe->prev[1] == -1)
// 		ft_close(pipe->prev[1]);
// 	pipe->prev[0] = pipe->curr[0];
// 	pipe->prev[1] = pipe->curr[1];
// 	ft_pipe(pipe->curr);
// }

static void	child_process(t_pipe *pipe, t_info *info, char *argv, char **envp)
{
	ft_pipe(pipe->prev);
	info->pid = ft_fork();
	if (info->pid == 0)
	{
		ft_close(pipe->prev[0]);
		ft_dup2(pipe->prev[1], STDOUT_FILENO);
		ft_close(pipe->prev[1]);
		command_excute(argv, envp);
	}
}

static void	parent_process(t_pipe *pipe, t_info *info)
{
	// int	status;

	ft_close(pipe->prev[1]);
	ft_waitpid(info->pid, 0, 0);
	ft_dup2(pipe->prev[0], STDIN_FILENO);
	ft_close(pipe->prev[0]);
	// status = get_exit_status(status);
	// if (status)

}

static void	here_doc(t_info *info, char *limiter)
{
	char *line;

	ft_putstr_fd("pipe heredoc>", info->infile);
	while (get_next_line(STDIN_FILENO, &line))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break;
		}
		ft_putstr_fd("pipe heredoc>", info->infile);
		ft_putstr_fd(line, info->infile);
		free(line);
	}
	ft_close(info->infile);
	info->infile = ft_open("temp", READ);
}

static void	initialize(t_pipe *pipe, t_info *info, char *argv)
{
	pipe->prev[0] = -1;
	pipe->prev[1] = -1;
	pipe->curr[0] = -1;
	pipe->curr[1] = -1;
	info->heredoc = -1;
	info->infile = -1;
	info->outfile = -1;
	ft_pipe(pipe->prev);
	ft_pipe(pipe->curr);
	if (ft_strncmp(argv, "here_doc", 8) == 0)
		info->heredoc = 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipe;
	t_info	info;
	int		index;

	index = 1;

	if (argc < 5)
		putstr_error("Error: Bad argument\n", NULL, EXIT_FAILURE);
	initialize(&pipe, &info, argv[index]);
	if (info.heredoc != 1)
	{
		info.infile = ft_open(argv[index++], READ);
		info.outfile = ft_open(argv[argc - 1], WRITE);
	}
	else
	{
		info.infile = ft_open("temp", WRITE);
		info.outfile = ft_open(argv[argc - 1], APPEND);
		here_doc(&info, argv[++index]);
	}
	ft_dup2(info.infile, STDIN_FILENO);
	ft_close(info.infile);
	while (index++ < argc - 2)
	{
		child_process(&pipe, &info, argv[index], envp);
	}
	index = 3;
	while (index++ < argc - 2)
		parent_process(&pipe, &info);
	ft_dup2(info.outfile, STDOUT_FILENO);
	ft_close(info.outfile);
	if (access("temp", F_OK) == 0)
		unlink("temp");
	command_excute(argv[argc - 2], envp);
	return (0);
}
