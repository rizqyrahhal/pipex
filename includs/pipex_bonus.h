/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:18:27 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/19 14:58:39 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

// pid_t
# include <sys/types.h>
// open()
# include <fcntl.h>
// perror()
# include <stdio.h>
// write(), fork(), pipe(), close(), dup2(), execve(), access()
# include <unistd.h>
// free(), malloc()
# include <stdlib.h>
/* waitpid, wait */
# include <sys/wait.h>

typedef struct stock {
    int infile;
    int outfile;
    int cmd_numbrs;
    int *fd;
}t_stock;

// errors
void	return_error(char *world);
void	use_this(char *msg);

// libft
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);



#endif