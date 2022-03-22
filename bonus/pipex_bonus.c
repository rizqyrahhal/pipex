/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:16:53 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/21 21:09:51 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	return (*envp + 5);
}

// close pipess
void	close_pipes(t_stock bonus)
{
	close(bonus.fdpipe[0]);
	close(bonus.fdpipe[1]);
	close(bonus.fd1pipe[0]);
	close(bonus.fd1pipe[1]);
}

int main(int argc, char *argv[], char **envp)
{
	if (argc < 5)
		use_this("executed as follows: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
	t_stock	bonus;
	
    // infile
	bonus.infile = open(argv[1], O_RDONLY);
	if (bonus.infile < 0)
		return_error("infile error");
	// outfile
	bonus.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (bonus.outfile < 0)
		return_error("infile error");
	// find and assigne PATH to bonus.paths
  	bonus.paths = find_path(envp);
	// open first pipe
  	if (pipe(bonus.fdpipe) == -1)
		return_error("error in opining pipe");
	// child own
	child_own(bonus, argv, envp);
  	// open secend pipe
  	if (pipe(bonus.fd1pipe) == -1)
		return_error("error in opining pipe");
  	// child tow
	child_tow(bonus, argv, envp);
	// child tree
	child_tree(bonus, argv, envp);
	close_pipes(bonus);
  	waitpid(bonus.pid1, NULL, 0);
	waitpid(bonus.pid2, NULL, 0);
	waitpid(bonus.pid3, NULL, 0);

	return (0);
}