#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct t_stock{
	int indx;
  int     infile;
  int     outfile;
  int     fdpipe[2];
  int     fd1pipe[2];
  pid_t   pid1;
  pid_t   pid2;
  pid_t   pid3;
  char	**cmd_argemment;
	char	*paths;
	char	*cmd;
	char	**cmd_paths;
} t_stock;

// functoin
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
size_t	ft_strlcpy(char *dist, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dist[i] = src[i];
			i++;
		}
		dist[i] = '\0';
	}
	return (ft_strlen(src));
}

char	**ft_malloc_error(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

int	num_of_words(const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

char	*next_str(char const *s, char c)
{
	int		i;
	char	*tab;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	tab = (char *)malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s, i + 1);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		strs_len;
	char	**tab;

	if (!s)
		return (NULL);
	strs_len = num_of_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (strs_len + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < strs_len)
	{
		while (s[0] == c)
			s++;
		tab[i] = next_str(s, c);
		if (!tab[i])
			return (ft_malloc_error(tab));
		s = s + ft_strlen(tab[i]);
	}
	tab[i] = 0;
	return (tab);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		k;
	int		lentgh;
	char	*newstring;

	i = -1;
	j = -1;
	k = 0;
	lentgh = ft_strlen(s1) + ft_strlen(s2);
	newstring = (char *)malloc(sizeof(char) * (lentgh + 1));
	if (!newstring)
		return (NULL);
	while (s1[++i])
	{
		newstring[k] = s1[i];
		k++;
	}
	while (s2[++j])
	{
		newstring[k] = s2[j];
		k++;
	}	
	newstring[k] = 0;
	return (newstring);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (n && s1[i] && s1[i] == s2[i])
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
// end function ..
// error
void	use_this(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit (EXIT_FAILURE);
}

void	return_error(char *world)
{
	perror(world);
	exit (EXIT_FAILURE);
}

void	cmd_not_nound(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}
// get PATH
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	return (*envp + 5);
}
// get_cmd
char	*get_cmd(t_stock bonus)
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
		if (!access(command, F_OK))
			return (command);
		free(command);
	}
	return (0);
}
// child own
void	child_own(t_stock bonus, char *argv[], char **envp)
{
	bonus.pid1 = fork();
	if (bonus.pid1 < 0)
		return_error("error");
	if (bonus.pid1 == 0)
	{
	  bonus.cmd_argemment = ft_split(argv[2], ' ');
		bonus.cmd = get_cmd(bonus);
		if (!bonus.cmd)
		{
			cmd_not_nound(bonus.cmd_argemment[0]);
			// child_free(bonus.cmd_argemment);
			exit (EXIT_FAILURE);
		}
		close(bonus.fdpipe[0]);
		dup2(bonus.fdpipe[1], 1);
		close(bonus.fdpipe[1]);
		dup2(bonus.infile, 0);
		close(bonus.infile);
		if (execve(bonus.cmd, bonus.cmd_argemment, envp) == -1)
			return_error(bonus.cmd);
	}
}
// child tow
void	child_tow(t_stock bonus, char *argv[], char **envp)
{
	bonus.pid2 = fork();
	if (bonus.pid2 < 0)
		return_error("error");
	if (bonus.pid2 == 0)
	{
	  bonus.cmd_argemment = ft_split(argv[3], ' ');
		bonus.cmd = get_cmd(bonus);
		if (!bonus.cmd)
		{
			cmd_not_nound(bonus.cmd_argemment[0]);
			// child_free(bonus.cmd_argemment);
			exit (EXIT_FAILURE);
		}
		close(bonus.fdpipe[1]);
		close(bonus.fd1pipe[0]);
		dup2(bonus.fdpipe[0], 0);
		// dup2(bonus.fd, 1);
		dup2(bonus.fd1pipe[1], 1);
		if (execve(bonus.cmd, bonus.cmd_argemment, envp) == -1)
			return_error(bonus.cmd);
	}
}
// child tree
void	child_tree(t_stock bonus, char *argv[], char **envp)
{
	bonus.pid3 = fork();
	if (bonus.pid3 < 0)
		return_error("error");
	if (bonus.pid3 == 0)
	{
	  bonus.cmd_argemment = ft_split(argv[4], ' ');
		bonus.cmd = get_cmd(bonus);
		if (!bonus.cmd)
		{
			cmd_not_nound(bonus.cmd_argemment[0]);
			// child_free(bonus.cmd_argemment);
			exit (EXIT_FAILURE);
		}		
		close(bonus.fd1pipe[1]);
		dup2(bonus.fd1pipe[0], 0);
		dup2(bonus.outfile, 1);
		if (execve(bonus.cmd, bonus.cmd_argemment, envp) == -1)
			return_error(bonus.cmd);
	}
}

// close pipess
void	close_pipes(t_stock *bonus)
{
	close(bonus->fdpipe[0]);
	close(bonus->fdpipe[1]);
  close(bonus->fd1pipe[0]);
  close(bonus->fd1pipe[1]);
}

int main(int argc, char *argv[], char **envp)
{
	t_stock	bonus;

	if (argc != 6)
	    use_this("executed as follows: ./pipex file1 cmd1 cmd2 cmd3 file2\n");
  	bonus.infile = open(argv[1], O_RDONLY);
  	if (bonus.infile < 0)
		return_error("infile error");
	bonus.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (bonus.outfile < 0)
		return_error("infile error");
  	// open first pipe
  	if (pipe(bonus.fdpipe) == -1)
		return_error("error in opining pipe");
  	bonus.paths = find_path(envp);
  	child_own(bonus, argv, envp);
  	// open secend pipe
  	if (pipe(bonus.fd1pipe) == -1)
		return_error("error in opining pipe");
  	child_tow(bonus, argv, envp);
	child_tree(bonus, argv, envp);
	close_pipes(&bonus);
  	waitpid(bonus.pid1, NULL, 0);
	waitpid(bonus.pid2, NULL, 0);
	waitpid(bonus.pid3, NULL, 0);

	// system("leaks pipex");

  	return (0);
}