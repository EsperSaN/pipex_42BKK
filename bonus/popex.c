#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct pipe_var {
	int	fd_in;
	int	fd_out;
	char	**env;
	int	pipo[2];
}	t_pipe;

void	free_2d(char **t_array)
{
	int	i = 0;

	if(t_array)
	{
		while(t_array[i])
		{
			free(t_array[i]);
			i++;
		}
		free(t_array);
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

int	str_n_compare(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if (*s1 != *s2)
			return (0);
		if (*s1 == 0)
			return (0);
		n--;
		s1++;
		s2++;
	}
	return (1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subbstr;
	size_t	i;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s + start);
	subbstr = malloc(len + 1);
	if (!subbstr)
		return (0);
	i = 0;
	while (len - i && start + i < ft_strlen(s))
	{
		*(subbstr + i) = *(s + (start + i));
		i++;
	}
	*(subbstr + i) = '\0';
	return (subbstr);
}

size_t	count_on_me(char const *s, char c)
{
	int	word;
	int	skip;

	skip = 0;
	word = 0;
	while (*s)
	{
		if (*s == c && skip == 1)
			skip = 0;
		if (*s != c && skip == 0)
		{
			word++;
			skip = 1;
		}
		s++;
	}
	return (word);
}

size_t	how_long(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			return (count);
		count++;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**resplit;
	size_t	i;
	size_t	big_i;

	if (!s)
		return (0);
	i = 0;
	big_i = 0;
	resplit = (char **)malloc((sizeof(char *)) * (count_on_me(s, c) + 1));
	if (!resplit)
		return (0);
	while (s[i] && i <= ft_strlen(s))
	{
		if (s[i] != c)
		{
			resplit[big_i] = ft_substr(s, i, how_long(&s[i], c));
			i = i + how_long(&s[i], c);
			big_i++;
		}
		if (s[i] == c)
			i++;
	}
	resplit[big_i] = NULL;
	return (resplit);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*j_str;
	char	*str_joined;

	if (!s1 || !s2)
		return (0);
	j_str = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!j_str)
		return (0);
	str_joined = j_str;
	while (*s1)
	{
		*j_str = *s1;
		s1++;
		j_str++;
	}
	while (*s2)
	{
		*j_str = *s2;
		s2++;
		j_str++;
	}
	*j_str = '\0';
	return (str_joined);
}

void	print_customerror(char *str)
{
	int	stderr = 2;
	while (*str)
	{
		write(stderr, str, 1);
		str++;
	}
	write(stderr, "\n", 1);
	exit(1);
}

void	error_exit(char	*error_str)
{
	perror(error_str);
	printf("erro_exit with %d",errno);
	exit(errno);
}

void	open_file_inout(t_pipe *var, char *filein, char *fileout)
{
	var->fd_in = open(filein, O_RDONLY);
	if (var->fd_in == -1)
		error_exit("ERROR_FILE_IN");

	var->fd_out = open(fileout, O_RDWR | O_CREAT, 0666);
	if (var->fd_out == -1)
		error_exit("ERROR_FILE_OUT");
}

void	split_env_path(char ***envbox, char **ev)
{
	while(*ev)
	{
		if(str_n_compare(*ev, "PATH=", 5))
			*envbox = ft_split((*ev) + 5, ':');
		ev++;
	}
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*cmd_path;
	char	*env_prepath;
	int	i = 0;

	if(0 == access(cmd, X_OK))
		return(ft_substr(cmd, 0 ,ft_strlen(cmd)));
	// if cmd already ok just return the cmd
	while(envp[i])
	{

		write(2, "IN CMD\n", 7);
		env_prepath = ft_strjoin(envp[i] , "/");
		cmd_path = ft_strjoin(env_prepath , cmd);
		free(env_prepath);
		if(0 == access(cmd_path, X_OK))
			return(cmd_path);
		free(cmd_path);
		i++;
	}
	return(ft_substr(cmd, 0 ,ft_strlen(cmd)));
}

void	run_command(char *cmd ,char **splited_ev, char **ev)
{
	char	**cmd_arg;
	char	*cmd_path;

	cmd_arg = ft_split(cmd ,' ');
	dprintf(2, ">>> cmd_Arg \n %s\n", cmd_arg[0]);
	cmd_path = get_cmd_path(cmd_arg[0], splited_ev);
	dprintf(2,">>>>>>>>>>>>> DEBUG <<<<<<<<<<<\n cmd_path = %s \n", cmd_path);
	execve(cmd_path, cmd_arg, ev);
	free_2d(cmd_arg);
	free(cmd_path);
	error_exit("error when exe command");
}
#include <sys/wait.h>
int main(int ac ,char **av , char **ev)
{
	t_pipe	var;
	int 	i = 0;

//	if (ac != 5)
//		print_customerror("the argument must be 4!!!");
	//printf("error before %d",errno);
	open_file_inout(&var, av[1], av[ac-1]);
	split_env_path(&var.env, ev); //check $PATH and split them into var.env if no path NULL
	

	dup2(var.fd_in, 0);
	int	mpid = fork();

	if(ac > 4 && mpid == 0)
	{
		if(-1 == pipe(var.pipo))
			error_exit("pope not found");
		pid = fork();
		if(pid == -1)
			error_exit("only spoon");
		if(pid == 0)
		{
			dup2(var.pipo[1], 1);
			run_command();
		}
		if(pid > 0)
		{
			wait(NULL);
			dup2(var.pipo[0], 0);
			exit();
		}
	}

	if(mpid > 0)
	{
		wait(NULL);
		dup2(1, var.fd_out);
		runcommand(var.env_box);
	}
}
