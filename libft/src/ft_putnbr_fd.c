/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 02:50:30 by hmoon             #+#    #+#             */
/*   Updated: 2022/01/17 16:52:42 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_putnbr(unsigned int nbr, int fd)
{
	char	n;

	if (nbr >= 10)
		ft_putnbr(nbr / 10, fd);
	n = nbr % 10 + '0';
	write(fd, &n, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	if (n < 0)
		write(fd, "-", 1);
	ft_putnbr(nbr, fd);
}
