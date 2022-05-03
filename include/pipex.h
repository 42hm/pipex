/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 10:12:43 by hmoon             #+#    #+#             */
/*   Updated: 2022/05/04 07:12:55 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"

enum e_exit_status
{
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
	pid_t	pid;
	int		index;
	int		infile;
	int		outfile;
	int		pipe[2];
}			t_info;

void	make_process(t_info *info, char *str, char **ev);
void	command_excute(char *str, char **ev);
void	putstr_error(char *str, char *target, int exit_status);

#endif
