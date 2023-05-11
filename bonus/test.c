
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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

void	run_command(char *cmd, char **envbox)
{
	char **cmd_argument;
	char *cmdpath;
	
	cmd_argument = ft_split(cmd);

	if(-1 == is_execute(cmd[0]))
		cmdpath = get_cmdpath(cmd[0] ,envbox);

	execve(cmdpath, cmd_argument, ev);

	put_run_error(cmd, errno);
}

int main(int ac, char **av)
{
	int pipo[ac - 4][2];
	int process_pid[ac - 3];
	int i = 0;
	char **envbox;

	printf("create process slot = %d\npipe slot = %d\n", (ac-3), (ac-4));

	envbox = get_envpath(ev);


	while(i < (ac-4))
	{
		if(-1 == pipe(pipo[i]))
			printf("error pipe");
		printf("pipe %d create\n", i);
		i++;
	}
	
	i = 0;
	printf("<<<<<<<<<<<< the loop process >>>>>>>>>>>\n");
	while(i < ac - 3)
	{
		process_pid[i] = fork();
		if(process_pid[i] == 0)
		{
			run_command(av[i + 2], envbox);
		}else
		{
			printf("do the i++ in %d process\n", process_pid[i]);
			i++;
		}
	}


	//whyyyyyyyyyyyyyyyyyyyy v-----v
	i = 0;
	while(i++ < (ac - 3))
	{
		put_str_fd("<<<<<< wait >>>>>>\n", 2);
		waitpid(process_pid[i],NULL,0);
	}
}
