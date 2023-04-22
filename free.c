#include "./pipex.h"
void free_2D(char **str)
{
	int i = 0;
	if (str)
	{
		while(str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void free_close_var_in_pipe_var(t_var *pipe_var)
{
	if(pipe_var->int_fdin > 2)
		close(pipe_var->int_fdin);
	if(pipe_var->int_fdout > 2)
		close(pipe_var->int_fdout);
	if(pipe_var->str_CmdPath_1)
		free(pipe_var->str_CmdPath_1);
	if(pipe_var->str_CmdPath_2)
		free(pipe_var->str_CmdPath_2);
	if(pipe_var->tstr_Command1)
		free_2D(pipe_var->tstr_Command1);
	if(pipe_var->tstr_Command2)
		free_2D(pipe_var->tstr_Command2);
	if(pipe_var->tstr_envpath)
		free_2D(pipe_var->tstr_envpath);
}