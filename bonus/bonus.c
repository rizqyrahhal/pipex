/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:29:18 by rarahhal          #+#    #+#             */
/*   Updated: 2022/04/05 22:25:35 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	return (*envp + 5);
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

// childe function :
char	*get_cmddd(t_stock bonus)
{
	char	*tmp;
	char	*command;
	int		i;

	if (ft_strnstr(bonus.cmd_argemment[0], "/",
			ft_strlen(bonus.cmd_argemment[0])))
		return (bonus.cmd_argemment[0]);
	i = -1;
	bonus.cmd_paths = ft_split(bonus.paths, ':');
	while (bonus.cmd_paths[++i])
	{
		tmp = ft_strjoin("/", bonus.cmd_argemment[0]);
		command = ft_strjoin(bonus.cmd_paths[i], tmp);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
	}
	return (0);
}

static void duplicat(int zero, int first)
{
    dup2(zero, 0);
    dup2(first, 1);
}

void	child(t_stock bonus, char *argv[], char **envp)
{
	bonus.pid = fork();
	if (bonus.pid < 0)
		return_error("error");
	if (bonus.pid == 0)
	{
	    bonus.cmd_argemment = ft_split(argv[bonus.indx + 2], ' ');
		bonus.cmd = get_cmddd(bonus);
		if (!bonus.cmd)
		{
			cmd_not_found(bonus.cmd_argemment[0]);
			// child_free(bonus.cmd_argemment);
			exit (EXIT_FAILURE);
		}
        if (bonus.indx == 0)
            duplicat(bonus.infile, bonus.pipefd[1]);
        else if (bonus.indx == bonus.cmd_nbr - 1)
            duplicat(bonus.pipefd[2 * bonus.indx - 2], bonus.outfile);
        else
            duplicat(bonus.pipefd[2 * bonus.indx - 2], bonus.pipefd[2 * bonus.indx + 1]);
        close_pipes(bonus);
		if (execve(bonus.cmd, bonus.cmd_argemment, envp) == -1)
			return_error(bonus.cmd);
	}
}

int main(int argc, char *argv[], char **envp)
{
	t_stock	bonus;
	
    // infile
	bonus.infile = open(argv[1], O_RDONLY);
	if (bonus.infile < 0)
		return_error("infile error");
	// outfile
	bonus.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (bonus.outfile < 0)
		return_error("infile error");
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

	return (0);
}