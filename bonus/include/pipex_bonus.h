/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 10:12:43 by hmoon             #+#    #+#             */
/*   Updated: 2022/04/30 23:07:24 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../../libft/include/libft.h"

enum e_exit_status
{
	STOP_SIGNAL = 17,
	CONTINUE_SIGNAL = 19,
	EXIT_NOT_EXECUTE = 126,
	EXIT_NOT_COMMAND = 127,
	EXIT_SIGNAL = 128
};

enum e_mode
{
	READ,
	WRITE,
	APPEND
};

typedef struct s_info
{
	int		heredoc;
	pid_t	pid;
	int		infile;
	int		outfile;
}			t_info;

typedef struct s_pipe
{
	int	prev[2];
	int	curr[2];
}			t_pipe;

// typedef struct s_cmd
// {
// 	char	*cmd;
// 	size_t	len;
// 	size_t	size;
// }			t_cmd;

#endif
