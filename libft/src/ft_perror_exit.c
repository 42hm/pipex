/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:15:06 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/28 17:43:00 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <errno.h>
#include <stdlib.h>

void	ft_perror_exit(const char *str, unsigned int exit_status)
{
	ft_perror(str, errno);
	exit(exit_status);
}
