/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:19:58 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/30 11:22:08 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdlib.h>

static int	read_buff(int fd, char **save)
{
	char	*buff;
	char	*temp;
	int		ret;

	buff = ft_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		buff = NULL;
	ret = read(fd, buff, BUFFER_SIZE);
	if (ret < 0 || buff == NULL)
	{
		free(buff);
		buff = NULL;
		return (-1);
	}
	buff[ret] = '\0';
	temp = ft_strjoin(*save, buff);
	free(*save);
	free(buff);
	*save = NULL;
	buff = NULL;
	*save = temp;
	if (ret > 0)
		return (1);
	else
		return (ret);
}

static void	division(char **save, char **line, int ret)
{
	char	*output;
	char	*backup;
	int		i;

	i = 0;
	if (ret == 0)
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
	}
	else if (ret > 0)
	{
		while ((*save)[i] != '\n')
			i++;
		output = ft_substr(*save, 0, i);
		*line = output;
		backup = ft_strdup(*save + i + 1);
		free(*save);
		*save = NULL;
		*save = backup;
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*save[OPEN_MAX];
	int			ret;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (save [fd] == NULL)
		save[fd] = ft_strdup("");
	ret = 1;
	while (ret > 0 && (ft_strchr(save[fd], '\n') == 0))
		ret = read_buff(fd, &save[fd]);
	division(&save[fd], line, ret);
	return (ret);
}
