/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:44:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/15 11:22:59 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_stock {
    int     infile;
    int     outfile;
    int     pipefd[2];
    int     pid1;
    int     pid2;
    char    **cmd_argemment;
    // char    **argss;
    // pid_t   pid1;
    // pid_t   pid2;

} t_stock;
// pid_t
#include <sys/types.h>
// open()
# include <fcntl.h>
// perror()
# include <stdio.h>
// write(), fork(), pipe(), close(), dup2(), execve()
# include <unistd.h>
// free(), malloc()
#include <stdlib.h>


char	**ft_split(char const *s, char c);
void    child_own(t_stock pipex, char *argv[],char **envp);
void    child_tow(t_stock pipex, char *argv[], char **envp);


#endif