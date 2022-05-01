/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:05:58 by hmoon             #+#    #+#             */
/*   Updated: 2022/05/01 15:08:01 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void	putstr_error(char *str, char *target, int exit_status)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (target)
	{
		if (exit_status != EXIT_NOT_COMMAND)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	exit(exit_status);
}

static char	**get_path(char **ev)
{
	size_t	index;

	index = 0;
	if (!(*ev))
		return (0);
	while (*ev && (ft_strnstr(ev[index], "PATH", 4) == 0))
		++index;
	if (ev[index] == 0)
		return (0);
	return (ft_split(ev[index] + 5, ':'));
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

void	command_excute(char *str, char **ev)
{
	char	**cmd;
	char	**paths;
	char	*path;

	cmd = ft_split(str, ' ');
	if (cmd == 0)
		putstr_error("Error: Bad cmd split\n", NULL, EXIT_FAILURE);
	paths = get_path(ev);
	if (paths == 0 && access(cmd[0], X_OK) == -1)
		putstr_error("Error: command not found: ", cmd[0], EXIT_NOT_COMMAND);
	path = cmd_parse(cmd[0], paths);
	if (execve(path, cmd, ev) == -1)
		exit(EXIT_NOT_EXECUTE);
}

void	make_process(t_info *info, char *str, char **ev)
{
	ft_pipe(info->pipe);
	info->pid = ft_fork();
	if (info->pid == 0)
	{
	// 	if (info->infile == -1 && info->index == 4)
	// 	{
	// 		ft_dup2(info->pipe[0], STDIN_FILENO);
	// 		ft_close(info->pipe[0]);
	// 	}
		// ft_dup2(info->pipe[0], STDIN_FILENO);
		ft_close(info->pipe[0]);
		ft_dup2(info->pipe[1], STDOUT_FILENO);
		ft_close(info->pipe[1]);
		command_excute(str, ev);
	}
	else
	{
		ft_dup2(info->pipe[0], STDIN_FILENO);
		ft_close(info->pipe[1]);
		ft_close(info->pipe[0]);
		ft_waitpid(info->pid, NULL, 0);
	}
}
