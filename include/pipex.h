/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:57:35 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/30 10:54:36 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"

# define EXIT_NOT_EXECUTE 126
# define EXIT_NOT_COMMAND 127

enum e_mode
{
	READ,
	WRITE,
	APPEND
};

# endif
