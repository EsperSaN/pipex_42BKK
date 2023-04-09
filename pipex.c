#include "./pipex.h"

void getenvpath(char **ep, t_var *pipe_var)
{
//	int i = 0;
	while(*ep)
	{
		while(*ep)
		{
			if(str_n_compare(*ep, "PATH=", 5))
			{
				pipe_var->tstr_envpath = ft_split((*ep) + 5, ':');
//				printf("en is at index %d is %s \n",i,*ep);
			}
//			i++;
			ep++;
		}
	}
}

char	*get_CmdPath(char *command, t_var pipe_var)
{
	int	i;
	char *prepath;
	char *path_and_command;
	i = 0;
	while(pipe_var.tstr_envpath[i])
	{
		//prepath command acquire
		prepath = ft_strjoin(pipe_var.tstr_envpath[i],"/");
		path_and_command = ft_strjoin(pipe_var.tstr_envpath[i], command);
		free(prepath);
		printf("the pH is %s \n",path_and_command);
		if(0 == access(path_and_command, X_OK))
			return(path_and_command);
		free(path_and_command);
		i++;
	}
	return(0);
}

int main(int ac, char** av, char **ep)
{
	t_var pipe_var;
	if(ac != 5)
	{
		printf("not enought arg");
		return (-1);
	}
	// check the FILE IN CAN HE OPEN IT!!!
	int fd_inflie = open(av[1], O_RDONLY);//<< the av[1] is the input file and must be valid

	printf("infile is %d\n", fd_inflie);

	if (fd_inflie < 0)
	{
		printf("error with INflie\n");
	}
	//check the env path
	getenvpath(ep,&pipe_var);

	if(pipe_var.tstr_envpath == NULL)
	{
		printf("error with path\n");
		return(1);
	}
	//debug path
	printf("out of the getend\n");	
	int i=0;
	while(pipe_var.tstr_envpath[i])
	{
		printf("IN");
		printf("env %d is %s \n", i,pipe_var.tstr_envpath[i]);
		i++;
	}
	//end

	//check the command on av[2] and av [3]
	pipe_var.str_CmdPath_1 = get_CmdPath(av[2],pipe_var);
//	if(access(av[3],X_OK) == -1)

	//check the output file
	int fd_outfile = open(av[4], O_RDWR|O_CREAT, 0666);

	if(fd_outfile < 0)
	{
		printf("error with outfile fd\n");
	}
	free(pipe_var.str_CmdPath_1);	
}
