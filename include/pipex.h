/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:57:35 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/15 15:18:04 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"

typedef struct s_exec
{
	char			*data;
	struct	s_exec	*next;
}				t_exec;

typedef struct s_pid
{
	pid_t			data;
	struct	s_pid	*next;
}				t_pid;

# endif
