/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:19:58 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/15 15:16:32 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	read_buff(int fd, char **save)
{
	char	*buff;
	char	*temp;
	int		ret;

	buff = ft_malloc(sizeof(char) * (BUFFER_SIZE));
	ret = read(fd, buff, BUFFER_SIZE);
	if (ret < 0 || buff == NULL)
	{
		ft_free(buff);
		return (-1);
	}
	buff[ret] = '\0';
	temp = ft_strjoin(*save, buff);
	ft_free(*save);
	ft_free(buff);
	*save = temp;
	if (ret > 0)
		return (1);
	else
		return (ret);
}

static void	division(char **save, char **line, int ret)
{
	char	*backup;
	char	*output;
	int		i;

	i = 0;
	if (ret == 0)
	{
		*line = ft_strdup(*save);
		ft_free(*save);
	}
	else if (ret > 0)
	{
		while ((*save[i] != '\n'))
			i++;
		output = ft_substr(*save, 0, i);
		*line = output;
		backup = ft_strdup(*save + i + 1);
		ft_free(*save);
		*save = backup;
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*save[OPEN_MAX];
	int			ret;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (save[fd] == NULL)
		save[fd] = ft_strdup("");
	ret = 1;
	while (ret > 0 && (ft_strchr(save[fd], '\n') == 0))
		ret = read_buff(fd, &save[fd]);
	division(&save[fd], line, ret);
	return (ret);
}
