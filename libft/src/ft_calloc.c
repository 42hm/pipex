/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:44:20 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/15 15:17:26 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t num, size_t size)
{
	void	*buff;

	buff = malloc(size * num);
	if (!buff)
		return (NULL);
	ft_bzero(buff, size * num);
	return (buff);
}
