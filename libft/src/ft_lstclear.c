/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 05:04:51 by hmoon             #+#    #+#             */
/*   Updated: 2022/01/17 16:47:48 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst && *lst)
	{
		while (*lst)
		{
			del((*lst)->content);
			tmp = *lst;
			*lst = (*lst)->next;
			free(tmp);
		}
	}
	*lst = NULL;
}
