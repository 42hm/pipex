/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:59:16 by hmoon             #+#    #+#             */
/*   Updated: 2022/01/17 16:46:57 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_num(int n)
{
	int	cnt;

	if (n <= 0)
		cnt = 1;
	else
		cnt = 0;
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	int				count;
	char			*ret;

	if (n > 0)
		num = n;
	else
		num = -n;
	count = count_num(n);
	ret = (char *)malloc(sizeof(char) * (count + 1));
	if (!ret)
		return (NULL);
	ret[count] = '\0';
	while (count > 0)
	{
		ret[count - 1] = (num % 10) + '0';
		num /= 10;
		count--;
	}
	if (n < 0)
		ret[0] = '-';
	return (ret);
}
