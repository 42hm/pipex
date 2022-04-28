/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 03:56:03 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/28 17:16:56 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;

	if (dst == src || !len)
		return (dst);
	dest = dst;
	if ((unsigned char *)src < dest)
	{
		while (len--)
			*(dest + len) = *((unsigned char *)src + len);
	}
	else
	{
		while (len--)
			*dest++ = *(unsigned char *)src++;
	}
	return (dst);
}
