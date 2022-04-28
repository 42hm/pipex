/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 21:03:45 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/28 17:16:59 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	len_s;

	if (!s || !len || ft_strlen(s) <= start)
		return (ft_strdup(""));
	len_s = ft_strlen(s);
	if (len_s + start < len)
		len = len_s - start;
	ret = ft_malloc((len + 1) * sizeof(char));
	if (len_s > start)
		ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
