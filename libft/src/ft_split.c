/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:18:14 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/15 14:52:28 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	cset(char const *s, char c, size_t *count)
{
	size_t	cnt;

	*count = 0;
	cnt = 0;
	while (*s != 0)
	{
		if (*s != c)
		{
			*count += 1;
			cnt++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (cnt);
}

static	char	**split_free(char **ret)
{
	size_t	i;

	i = 0;
	while (ret[i] != 0)
	{
		ft_free(ret[i]);
		i++;
	}
	ft_free(ret);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	size;
	size_t	index;
	size_t	count;

	if (!s)
		return (NULL);
	ret = ft_malloc(sizeof(char *) * (cset(s, c, &count) + 1));
	index = 0;
	while (index < count)
	{
		size = 0;
		while (*s == c && *s != '\0')
			s++;
		while (s[size] != c && s[size] != '\0')
			size++;
		ret[index++] = ft_substr(s, 0, size);
		if (!ret)
			return (split_free(ret));
		s += size;
	}
	ret[index] = 0;
	return (ret);
}
