/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:41:29 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/28 20:27:48 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <errno.h>
#include <stdlib.h>

int	ft_dup2(int fd1, int fd2)
{
	if (fd1 == fd2)
		return (1);
	if (dup2(fd1, fd2) == -1)
	{
		ft_perror("dup2", errno);
		exit(EXIT_FAILURE);
	}
	return (1);
}
