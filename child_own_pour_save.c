void	child_own(t_stock pipex, char *argv[], char **envp)
{
	pipex.pid1 = fork();
    if (pipex.pid1 < 0)
        return_error("error");
	if (pipex.pid1 == 0)
	{
		pipex.cmd_argemment = ft_split(argv[2], ' ');
		pipex.cmd = get_cmd(pipex);
		close(pipex.pipefd[0]);
		dup2(pipex.pipefd[1], 1);
		close(pipex.pipefd[1]);
		dup2(pipex.infile, 0);
		close(pipex.infile);
		if (!pipex.cmd)
		{
			child_free(&pipex);
			error_msg("command not found!\n");
			exit (1);
		}
		execve(pipex.cmd, pipex.cmd_argemment, envp);
		// if (execve(pipex.cmd, pipex.cmd_argemment, envp) == -1)
		// {
		// 	return_error("error");
		// }
	}
}