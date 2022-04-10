/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:29:18 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/10 14:23:33 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	return (*envp + 5);
}

int		nbr_argc(char *argv, t_stock bonus)
{
	if (!ft_strncmp("here_doc", argv, 9))
	{
		bonus.heredoc = 1;
		return (6);
	}
	else
	{
		bonus.heredoc = 0;
		return (5);
	}
}

//  creat pipes :
void    creat_pipes(t_stock bonus)
{
    int i;

    i = -1;
    while (++i < bonus.cmd_nbr - 1)
        if (pipe(bonus.pipefd + 2 * i) < 0)
            return_error("error in opining pipe");
}

// close pipes :
void    close_pipes(t_stock bonus)
{
    int i;
    
    i = -1;
    while (++i < bonus.pipe_nbr)
        close(bonus.pipefd[i]);
}

int main(int argc, char *argv[], char **envp)
{
	t_stock	bonus;
	
	if (argc < nbr_argc(argv[1], bonus))
		return_error("input_error");
    // infile
	get_infile(argv, bonus);
	// outfile
	get_outfile(argv[argc - 1], bonus);
    // calcule number of commands :
    bonus.cmd_nbr = argc - 3;
    // calcule number of pipes :
    bonus.pipe_nbr = 2 * (bonus.cmd_nbr - 1);
	// allocate pipefd:
	bonus.pipefd = (int*)malloc((bonus.pipe_nbr * 2) * sizeof(int));
    // open pipes :
  	creat_pipes(bonus);
 	// find and assigne PATH to bonus.paths
  	bonus.paths = find_path(envp);
	// child
    bonus.indx = -1;
    while (++bonus.indx < bonus.cmd_nbr)
        child(bonus, argv, envp);
	close_pipes(bonus);
	
	// system("leaks pipex");

	return (0);
}