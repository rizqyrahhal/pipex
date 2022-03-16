/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:44:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/16 12:06:24 by rarahhal         ###   ########.fr       */
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
    char    *paths;
    char    *cmd;
    char    **cmd_paths;
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
// write(), fork(), pipe(), close(), dup2(), execve(), access()
# include <unistd.h>
// free(), malloc()
#include <stdlib.h>


char	**ft_split(char const *s, char c);
void    child_own(t_stock pipex, char *argv[],char **envp);
void    child_tow(t_stock pipex, char *argv[], char **envp);
size_t	ft_strlen(const char *s);
void    return_error(char *world);
void    use_this(char *msg);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void    cmd_not_nound(char *cmd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

void	child_free(t_stock *pipex);


#endif