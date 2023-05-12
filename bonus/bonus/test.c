#include "pipex.h"

void	putstr_fd(char *str, int fd)
{
	while(*str)
	{
		write(fd, str, 1);
		str++;
	}
}

void	put_run_error(char *cmd ,int errnum)
{
	putstr_fd(cmd ,2);
	(void)errnum;
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
	int i = 0;
	while(i < 3)
	{
		dprintf(2, "in %d %s \n", i, cmd_argument[i]);
		i++;
	}

	dprintf(2, "in command path %s \n", cmdpath);
	if(-1 == execve(cmdpath, cmd_argument, ev))
		dprintf(2, "eroo %s", cmd);
}

int main(int ac, char **av, char **ev)
{
	int pipo[2];
	int process_pid[ac - 3];
	int i = 0;
	char **envbox;
	
	int in_file = open(av[1], O_RDONLY);
	int out_file = open(av[ac-1], O_RDWR | O_CREAT ,0777);

	envbox = get_envpath(ev);
	i = 0;		

	while(i < ac - 3)
	{
		if (i != ac - 4)
		{
			if(-1 == pipe(pipo))
				return(0);
			dprintf(2, "hello %d\n", i);
		}
		process_pid[i] = fork();
		if(process_pid[i] == 0)
		{
			dup2(in_file, 0);
			dprintf(2, "child %d\n", i);
			if (i == 0)
			{
				close(pipo[0]);
	
				close(in_file);
				dup2(pipo[1], 1);
				close(pipo[1]);
				dprintf(2, "first cmd %d\n", i);

			}
			else if (i == ac - 4)
			{
				dprintf(2, "last cmd %d\n", i);
				
				dup2(in_file, 0);
			
				dup2(out_file, 1);
				close(out_file);

			}else
			{
				dup2(in_file, 0);
				close(in_file);
				dup2(pipo[1], 1);
				close(pipo[1]);
				dprintf(2, "cmd %d\n", i);
			}
			run_command(av[i + 2],envbox , in_file, ev);
		}else{
			dprintf(2, "mom %d\n", i);
			close(pipo[1]);
			dprintf(2, "old infile %d nad pipo is %d\n",in_file,pipo[0]);
			close(in_file);
		
			in_file = dup(pipo[0]);
			//close(pipo[0]);
			dprintf(2, "new infile %d in loop %d i\n",in_file,i);
			// close(in_file); //cuz it doesn use it any more <already use in the run command>
			//close(pipo[0]);
			i++;
		}
	}
			close(pipo[0]);


	//whyyyyyyyyyyyyyyyyyyyy v-----v
	i = -1;
	while(++i < (ac - 3))
	{
		dprintf(2, "------------------i = %d\n", i);
		putstr_fd("\n<<<<<< wait >>>>>>\n", 2);
		waitpid(process_pid[i],NULL,0);
	}
}
