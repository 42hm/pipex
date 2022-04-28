/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:39:55 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/28 20:31:00 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <errno.h>
#include <stdlib.h>

void	ft_close(int fd)
{
	if (fd == 0 || fd == 1 || fd == 2 || fd < 0)
		return ;
	if (close(fd) == -1)
	{
		ft_perror("close", errno);
		exit(EXIT_FAILURE);
	}
	return ;
}
