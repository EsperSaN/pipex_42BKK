#include "pipex.h"

int	open_filefd(char *name, char **av , char *mode)
{
	int fd;

	dprintf(2, "\nthe output fd on the %s file is [%d]\n",av[ac-1], out_file);
	if(-1 == fd)
		put_error("OUTFILE",errno);
	dup2(out_file, 1);
	close(out_file);
	close(pipo[0]);
	close(pipo[1]);
}

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
	if(to_input == -1)
		to_input = dup(STDOUT_FILENO);
	dup2(to_input , 0);
	dprintf(2, "\n------------ in_file is %d----------\n",to_input);
	close(to_input);
	if(-1 == execve(cmdpath, cmd_argument, ev))
		put_errorcmd(cmd_argument[0],errno);
}

int main(int ac, char **av, char **ev)
{
	if(ac <= 4)
		put_error("NOT ENOUG ARG",0);
	int pipo[2];
	int process_pid[ac - 3];
	int i = 0;
	char **envbox;
	int in_file;
	int out_file;
	
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
			if(i == 0)
			{
				in_file = open(av[1], O_RDONLY);
				if(in_file == -1)
					put_error("INFILE",errno);
			}
			if(i == ac - 4)
				out_file = open_file("OUTFILE", av );
			else{
				dup2(pipo[1],1);
				close(pipo[1]);
			}
			dprintf(2,"\n-------------- [%d] ---------------\nfork with PID == %d \nand pipo[0] == [%d]\npipo[1] == [%d]\ninfile == [%d]\n", i,process_pid[i],pipo[0], pipo[1], in_file);
			dprintf(2,"\n {command = %s} [infile == %d]\n", av[i + 3], in_file);
			run_command(av[i + 2], envbox, in_file, ev);
		}else if(process_pid[i] > 0)
		{
			dprintf(2,"\n\n----before dup [%d]---\n infile[%d] \n pipe[0] = [%d]",i,in_file, pipo[0]);
			in_file = dup(pipo[0]);
			dup2(pipo[0], in_file);
			dprintf(2,"\n----after dup [%d]------\n infile[%d] \n pipe[0] = [%d]\n",i,in_file, pipo[0]);
			close(pipo[0]);
			close(pipo[1]);
			i++;
		}	
		else
			put_error("EXIT", errno);
	}
	i = -1;
	while (++i < ac - 3)
		waitpid(process_pid[i] ,NULL,WUNTRACED);
		;
}