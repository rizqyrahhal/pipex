/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:44:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/18 22:41:32 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct s_stock {
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd_argemment;
	char	*env_path;
	char	*cmd;
	char	**cmd_paths;
}	t_stock;

// childs
void	child_own(t_stock pipex, char *argv[], char **envp);
void	child_tow(t_stock pipex, char *argv[], char **envp);

//error
void	use_this(char *msg);
void	infile_error(char *world);
void	return_error(char *world);
void	cmd_not_found(char *cmd);

// small libft
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif
