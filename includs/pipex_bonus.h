/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:18:27 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/21 21:33:56 by rarahhal         ###   ########.fr       */
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
    int     indx;
    int     infile;
    int     outfile;
    int     fdpipe[2];
    int     fd1pipe[2];
    pid_t   pid1;
    pid_t   pid2;
    pid_t   pid3;
    char	**cmd_argemment;
    char	*paths;
    char	*cmd;
    char	**cmd_paths;
}t_stock;

// errors
void	return_error(char *world);
void	use_this(char *msg);
void	cmd_not_nound(char *cmd);

// childs
void	child_own(t_stock bonus, char *argv[], char **envp);
void	child_tow(t_stock bonus, char *argv[], char **envp);
void	child_tree(t_stock bonus, char *argv[], char **envp);

// small libft
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);



#endif