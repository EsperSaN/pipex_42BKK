#include "./pipex.h"

void exev_child(t_var *pipe_var, char** ep)
{
		dup2(pipe_var->pipe[1], 1);
		dup2(pipe_var->int_fdin, 0);
		close(pipe_var->pipe[0]);
		execve(pipe_var->str_CmdPath_1,pipe_var->tstr_Command1,ep);
		exit_due_error("Error when try to run command 1", 0, pipe_var);
}
void exev_parent(t_var *pipe_var, char** ep)
{
		dup2(pipe_var->pipe[0], 0);
		close(pipe_var->pipe[1]);
		dup2(pipe_var->int_fdout, 1);
		execve(pipe_var->str_CmdPath_2,pipe_var->tstr_Command2,ep);
		exit_due_error("Error when try to run command 2", 0, pipe_var);
}