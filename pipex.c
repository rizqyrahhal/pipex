/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:42:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/14 17:06:57 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int main(int argc, char *argv[], char **envp)
{
    if (argc != 5)
        retrun ("executed as follows: ./pipex file1 cmd1 cmd2 file2");
    int infile = open(argv[1], O_RDONLY);
    if (infile < 0)
    {
        perror("infile error");
        return (1);
    }
        
    int outfile = open(argc - 1, O_CREAT | O_RDWR | O_TRUNC, 644);
    if (outfile < 0)
    {
        perror("infile error");
        return (2);
    }
    int fd[2];
    
}