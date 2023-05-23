#include "pipex.h"

void	dup_write_pipe_to_out(int *pipe)
{
	dup2(pipe[1],1);
	close(pipe[1]);
}

void	change_read_pipe_to_in(int *in_file, int *pipe)
{
	close(*in_file);
	*in_file = dup(pipe[0]);
	close(pipe[0]);
	close(pipe[1]);
}

int	open_in_file(char	**argv)
{
	int fd;
	//if(str_n_compare(argv[1], "doctype", 7))
	//	return(do_doctype(argv));

	fd = open(argv[1], O_RDONLY);
	if(-1 == fd)
		put_error("INPUT", errno);
	return(fd);
}

void open_outfile_to_pipe(char *out_path, int *pipe)
{
	int fd;

	fd = open(out_path, O_RDWR | O_CREAT | O_TRUNC , 0664);
	if(-1 == fd)
		put_error("OUTFILE", errno);
	dup2(fd, 1);
	close(fd);
	close(pipe[0]);
	close(pipe[1]);
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
	close(to_input);
	if(-1 == execve(cmdpath, cmd_argument, ev))
		put_errorcmd(cmd_argument[0],errno);
}

int main(int ac, char **av, char **ev)
{
	int pipo[2];
	int process_pid[ac - 3];
	int i = 0;
	char **envbox;
	int in_file;
	
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
				in_file = open_in_file(av);
			if(i == ac - 4)
				open_outfile_to_pipe(av[ac-1], pipo);
			else
				dup_write_pipe_to_out(pipo);
			run_command(av[i + 2], envbox, in_file, ev);
		}else if(process_pid[i] > 0)
		{
			change_read_pipe_to_in(&in_file, pipo);
			i++;
		}	
		else
			put_error("EXIT", errno);
	}
	i = -1;
	while(wait(NULL) != -1)
		;
	return(0);
}