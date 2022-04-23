/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:06:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/22 17:27:36 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/bonus.h"

void	parent_free(t_stock *bonus)
{
	int	i;

	i = -1;
	while (bonus->cmd_paths[++i])
		free(bonus->cmd_paths[i]);
	free(bonus->cmd_paths);
	free(bonus->pipefd);
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

void	creat_pipes(t_stock *bonus)
{
	int	i;

	i = -1;
	while (++i < bonus->cmd_nbr - 1)
		if (pipe(bonus->pipefd + 2 * i) < 0)
			return_error("error in opining pipe");
}

void	close_pipes(t_stock *bonus)
{
	int	i;

	i = -1;
	while (++i < bonus->pipe_nbr)
		close(bonus->pipefd[i]);
}

int	main(int argc, char *argv[], char **envp)
{
	t_stock	bonus;
 
	if (argc < chek_hedredoc(argv[1], &bonus))
		use_this("Input Format Invalid\n");
	get_outfile(argv[argc - 1], &bonus);
	bonus.cmd_nbr = argc - 3 - bonus.heredoc;
	bonus.pipe_nbr = 2 * (bonus.cmd_nbr - 1);
	bonus.pipefd = (int *)malloc(bonus.pipe_nbr * sizeof(int));
	if (!bonus.pipefd)
		return_error("error allocation");
	creat_pipes(&bonus);
	bonus.env_path = find_path(envp);
	bonus.cmd_paths = ft_split(bonus.env_path, ':');
	bonus.indx = -1;
	while (++bonus.indx < bonus.cmd_nbr)
		child(bonus, argv, envp);
	close_pipes(&bonus);
	while (bonus.indx-- > 0)
		waitpid(-1, NULL, 0);
	close_files(&bonus);
	parent_free(&bonus);
	return (0);
}
