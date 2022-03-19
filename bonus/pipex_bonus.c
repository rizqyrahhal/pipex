/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:16:53 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/19 16:38:44 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	return (*envp + 5);
}

int main(int argc, char *argv[], char **envp)
{
	if (argc < 5)
		use_this("executed as follows: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
	t_stock bonus;
	
    // infile
	bonus.infile = open(argv[1], O_RDONLY);
	if (bonus.infile < 0)
		return_error("infile error");
	// outfile
	bonus.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (bonus.outfile < 0)
		return_error("infile error");
	// number of command to handel number of pipes
	bonus.cmd_numbrs = argc - 3;
	printf("|%d|\n", bonus.cmd_numbrs); // just pour test numbers

	return (0);
}