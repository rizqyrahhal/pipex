/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:30:03 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/19 22:09:12 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

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
	int		heredoc;
	int		indx;
	int		infile;
	int		outfile;
	int		*pipefd;
	int		cmd_nbr;
	int		pipe_nbr;
	pid_t	pid;
	char	**cmd_argemment;
	char	*env_path;
	char	*cmd;
	char	**cmd_paths;
}t_stock;

// errors
void	return_error(char *world);
void	infile_error(char *world);
void	use_this(char *msg);
void	cmd_not_found(char *cmd);

// child
void	child(t_stock bonus, char *argv[], char **envp);
void	close_pipes(t_stock *bonus);

// files
void	get_infile(char **argv, t_stock *bonus);
void	get_outfile(char *argv, t_stock *bonus);
void	close_files(t_stock *bonus);

// here_doc
void	here_doc(char *argv, t_stock *bonus);
int		chek_hedredoc(char *argv, t_stock *bonus);

// small libft
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

// get_next_line
char	*get_next_line(int fd);

#endif
