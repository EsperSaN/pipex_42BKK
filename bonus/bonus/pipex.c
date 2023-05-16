#include "pipex.h"

int	is_execute(char *cmd)
{
	return(access(cmd,X_OK));
}

void	run_command(char *cmd, char **envbox, int to_input ,char **ev)
{
	char **cmd_argument;
	char *cmdpath;
	
	cmd_argument = ft_split(cmd,' ');
	cmdpath = get_cmdPath(cmd_argument[0] ,envbox);
	if(to_input != -1)
	{	
		dup2(to_input , 0);
		close(to_input);
	}
	if(-1 == execve(cmdpath, cmd_argument, ev))
		put_errorcmd(cmd_argument[0],errno);
}

int main(int ac, char **av, char **ev)
{
	if(ac != 5)
		put_error("NOT ENOUG ARG",0);
	int pipo[2];
	int process_pid[ac - 3];
	int i = 0;
	char **envbox;
	int in_file = open(av[1], O_RDONLY);
	if(in_file == -1)
		put_error("IN_FILE",errno);
	int out_file = open(av[ac-1], O_RDWR | O_CREAT ,0777);
	if(out_file == -1)
		put_error("OUTFILE",errno);
	
	envbox = get_envpath(ev);
	i = 0;		

	while(i < ac - 3)
	{
		if(-1 == pipe(pipo))
			put_error("PIPE",errno);
		
		process_pid[i] = fork();
		if(process_pid[i] == -1)
			put_error("FORK",errno);

		if(process_pid[i] == 0)
		{
			if(i == ac - 4)
			{
				dup2(out_file ,1);
				close(pipo[0]);
				close(pipo[1]);
			}else{
				dup2(pipo[1] , 1);
				close(pipo[0]);
			}
			run_command(av[i + 2], envbox, in_file, ev);
		}else{
			dup2(pipo[0] , in_file);
			close(pipo[1]);
			i++;
		}
	}
	i = -1;
	while (++i < ac - 3)
		waitpid(process_pid[i] ,NULL,WUNTRACED);
		;
}