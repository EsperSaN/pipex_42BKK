#include "./pipex.h"
void split_the_command_and_assign(char **av, t_var *pipe_var)
{
    pipe_var->tstr_Command1 = ft_split(av[2],' ');
    pipe_var->tstr_Command2 = ft_split(av[3], ' ');
}

void get_envpath(char **ep, char ***envbox)
{
	while(*ep)
	{
		if(str_n_compare(*ep, "PATH=", 5))
			*envbox = ft_split((*ep) + 5, ':');
		printf("current env var is %s\n",*ep);
		ep++;
	}
}

char	*get_CmdPath_slash(char *command, char **env)
{
	int	i;
	char *prepath;
	char *path_and_command;
	char *ready_cmd;
	i = 0;
	if(0 == access(command, X_OK) || env == NULL)
	{
		ready_cmd = ft_substr(command,0,ft_strlen(command));
		printf("str in CMDPATH is %s\n",ready_cmd);
		return(ready_cmd);
	}
	while(env[i])
	{
		prepath = ft_strjoin(env[i],"/");
		path_and_command = ft_strjoin(prepath, command);
		free(prepath);
		if(0 == access(path_and_command, X_OK))
			return(path_and_command);
		free(path_and_command);
		i++;
	}
	return(0);
}