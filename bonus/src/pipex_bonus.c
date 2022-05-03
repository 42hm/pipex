/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 09:10:11 by hmoon             #+#    #+#             */
/*   Updated: 2022/05/04 07:13:50 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <stdlib.h>
#include <errno.h>

static void	close_out(t_info *info)
{
	ft_dup2(info->outfile, STDOUT_FILENO);
	ft_close(info->outfile);
	if (info->heredoc == TRUE)
	{
		if (access("temp", F_OK) == 0)
			unlink("temp");
		else
			putstr_error("Error", "temp", EXIT_FAILURE);
	}
}

static void	here_doc(t_info *info, char *limiter)
{
	char	*line;

	write(STDOUT_FILENO, "> ", 2);
	while (get_next_line(STDIN_FILENO, &line))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(STDOUT_FILENO, "> ", 2);
		write(info->infile, line, ft_strlen(line));
		write(info->infile, "\n", 1);
		free(line);
	}
	ft_close(info->infile);
	info->infile = ft_open("temp", READ);
}

static void	open_in_out(t_info *info, int ac, char **av)
{
	if (info->heredoc == FALSE)
	{
		info->outfile = ft_open(av[ac - 1], WRITE);
		info->infile = ft_open(av[info->index], READ);
	}
	else
	{
		info->outfile = ft_open(av[ac - 1], APPEND);
		info->infile = ft_open("temp", WRITE);
		here_doc(info, av[++info->index]);
	}
	if (info->infile != -1)
	{
		ft_dup2(info->infile, STDIN_FILENO);
		ft_close(info->infile);
	}
}

static void	init_info(t_info *info, char *av)
{
	info->index = 1;
	info->infile = -1;
	info->outfile = -1;
	info->pipe[0] = -1;
	info->pipe[1] = -1;
	if (ft_strncmp(av, "here_doc", 8) == 0)
		info->heredoc = TRUE;
	else
		info->heredoc = FALSE;
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	if (argc < 5)
		putstr_error("Error: Bad argument\n", NULL, EXIT_FAILURE);
	init_info(&info, argv[1]);
	open_in_out(&info, argc, argv);
	while (++info.index < argc - 2)
		make_process(&info, argv[info.index], envp);
	close_out(&info);
	command_excute(argv[argc - 2], envp);
	return (0);
}
