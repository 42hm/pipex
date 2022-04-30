/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 10:32:58 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/30 21:32:40 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static void	putstr_error(const char *str, const char *argv, int exit_status)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (argv)
	{
		if (exit_status != 127)
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

int	4ft_open(const char *file, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		putstr_error("Error", file, 1);
	return (fd);
}
