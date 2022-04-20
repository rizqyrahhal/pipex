/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:42:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/20 18:19:10 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/pipex.h"

void	parent_free(t_stock *pipex)
{
	int	i;

	i = -1;
	while (pipex->cmd_paths[++i])
		free(pipex->cmd_paths[i]);
	free(pipex->cmd_paths);
}

void	close_pipes(t_stock *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
}

char	*find_path(char **envp)
{
	int	i;

	i = -1;
	while (ft_strncmp("PATH", *envp, 4) != 0 && envp[++i])
		envp++;
	if (ft_strnstr(*envp, "PATH", 4))
		return (*envp + 5);
	else
		return ("PATH NOT EXISTE..");
}

int	main(int argc, char *argv[], char **envp)
{
	t_stock		pipex;

	if (argc != 5)
		use_this("executed as follows: ./pipex file1 cmd1 cmd2 file2\n");
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.outfile < 0)
		return_error("infile error");
	if (pipe(pipex.pipefd) == -1)
		return_error("error in opining pipe");
	pipex.env_path = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.env_path, ':');
	child_own(pipex, argv, envp);
	child_tow(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	close(pipex.infile);
	close(pipex.outfile);
	parent_free(&pipex);
	return (0);
}
