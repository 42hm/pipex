/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_waitpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:43:32 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/29 09:10:34 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t	ft_waitpid(pid_t pid, int *status, int option)
{
	pid_t	ret;

	ret = waitpid(pid, status, option);
	if (ret == -1)
	{
		ft_perror("waitpid", errno);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
