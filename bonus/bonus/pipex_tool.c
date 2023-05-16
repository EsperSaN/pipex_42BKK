#include "pipex.h"

char    **get_envpath(char **ep)
{
	while(*ep)
	{
		if(str_n_compare(*ep, "PATH=", 5))
			return (ft_split((*ep) + 5, ':'));
		ep++;
	}
    return(NULL);
}

char	*get_cmdPath(char *command, char **env)
{
	int     i;
	char    *prepath;
	char    *path_and_command;
	char    *ready_cmd;
	i = 0;
	if(0 == access(command, X_OK) || env == NULL)
	{
		ready_cmd = ft_substr(command,0,ft_strlen(command));
		dprintf(2,"\n%s, is accessable", ready_cmd);
		return(ready_cmd);
	}
	while(env[i])
	{
		prepath = ft_strjoin(env[i],"/");
		path_and_command = ft_strjoin(prepath, command);
		free(prepath);
		if(0 == access(path_and_command, X_OK))
		{
			dprintf(2, "the command is [%s]\n", path_and_command);
			return(path_and_command);
		}
		free(path_and_command);
		i++;
	}
	return(0);
}