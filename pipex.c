#include "./pipex.h"

int main(int ac, char** av, char **ep)
{
	t_var pipe_var;

	if(ac != 5)
		exit_due_error("Not enough ARG", -1, &pipe_var);
	struct_init(&pipe_var);
	pipe_var.int_fdin = open(av[1], O_RDONLY);
	if (pipe_var.int_fdin < 0)
		exit_due_error("Error when open the input file", 0, &pipe_var);
	get_envpath(ep,&pipe_var.tstr_envpath);
	split_the_command_and_assign(av, &pipe_var);
	pipe_var.str_CmdPath_1 = get_CmdPath_slash(pipe_var.tstr_Command1[0],pipe_var.tstr_envpath);
	if(pipe_var.str_CmdPath_1 == NULL)
		error_cmd(pipe_var.tstr_Command1[0], &pipe_var);
	pipe_var.str_CmdPath_2 = get_CmdPath_slash(pipe_var.tstr_Command2[0],pipe_var.tstr_envpath);
	if(pipe_var.str_CmdPath_2 == NULL)
		error_cmd(pipe_var.tstr_Command2[0], &pipe_var);
	pipe_var.int_fdout = open(av[4], O_RDWR|O_CREAT, 0777);
	if(pipe_var.int_fdout == -1)
		exit_due_error("Error when open the output or create output", 0, &pipe_var);
	if (-1 == pipe(pipe_var.pipe))
		exit_due_error("Error when Create PIPE", 0, &pipe_var);
	int id = fork();
	if(id == 0)
		exev_child(&pipe_var, ep);
	else
	{
		wait(NULL);
		exev_parent(&pipe_var, ep);
	}
	free_close_var_in_pipe_var(&pipe_var);
}	
