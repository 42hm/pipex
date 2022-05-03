/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 09:10:11 by hmoon             #+#    #+#             */
/*   Updated: 2022/05/04 07:12:45 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdlib.h>
#include <errno.h>

static void	close_out(t_info *info)
{
	ft_dup2(info->outfile, STDOUT_FILENO);
	ft_close(info->outfile);
}

static void	open_in_out(t_info *info, int ac, char **av)
{
	info->outfile = ft_open(av[ac - 1], WRITE);
	info->infile = ft_open(av[info->index], READ);
	if (info->infile != -1)
	{
		ft_dup2(info->infile, STDIN_FILENO);
		ft_close(info->infile);
	}
}

static void	init_info(t_info *info)
{
	info->index = 1;
	info->infile = -1;
	info->outfile = -1;
	info->pipe[0] = -1;
	info->pipe[1] = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	if (argc < 5)
		putstr_error("Error: Bad argument\n", NULL, EXIT_FAILURE);
	init_info(&info);
	open_in_out(&info, argc, argv);
	while (++info.index < argc - 2)
		make_process(&info, argv[info.index], envp);
	close_out(&info);
	command_excute(argv[argc - 2], envp);
	return (0);
}
