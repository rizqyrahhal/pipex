/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:06:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/14 21:17:11 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/bonus.h"

int	chek_hedredoc(char *argv, t_stock *bonus)
{
	if (argv && !ft_strncmp("here_doc", argv, 9))
	{
		bonus->heredoc = 1;
		return (6);
	}
	else
	{
		bonus->heredoc = 0;
		return (5);
	}
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	return (*envp + 5);
}

void	creat_pipes(t_stock bonus)
{
	int	i;

	i = -1;
	while (++i < bonus.cmd_nbr - 1)
		if (pipe(bonus.pipefd + 2 * i) < 0)
			return_error("error in opining pipe");
}

void	close_pipes(t_stock bonus)
{
	int	i;

	i = -1;
	while (++i < bonus.pipe_nbr)
		close(bonus.pipefd[i]);
}

int	main(int argc, char *argv[], char **envp)
{
	t_stock	bonus;

	if (argc < chek_hedredoc(argv[1], &bonus))
		use_this("Input Format Invalid\n");
	get_infile(argv, bonus);
	get_outfile(argv[argc - 1], &bonus);
	bonus.cmd_nbr = argc - 3 - bonus.heredoc;
	bonus.pipe_nbr = 2 * (bonus.cmd_nbr - 1);
	bonus.pipefd = (int *)malloc(bonus.pipe_nbr * sizeof(int));
	if (!bonus.pipefd)
		return_error("error allocation");
	creat_pipes(bonus);
	bonus.paths = find_path(envp);
	bonus.indx = -1;
	while (++bonus.indx < bonus.cmd_nbr)
	{
		child(bonus, argv, envp);
		waitpid(bonus.pid, NULL, 0);
	}
	close_pipes(bonus);
	close(bonus.infile);
	close(bonus.outfile);
	free(bonus.cmd);
	return (0);
}
