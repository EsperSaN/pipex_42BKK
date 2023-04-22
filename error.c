#include "./pipex.h"

void exit_due_error(char *str, int errornum, t_var *var)
{
	printf("ERROR CODE %d '%s'\n",errornum ,str);
	if(errornum != -1)
		free_close_var_in_pipe_var(var);
	exit(errornum);
}

void error_cmd(char* command ,t_var *var)
{
	printf("The '%s' not found or not excutable\n", command);
	free_close_var_in_pipe_var(var);
	exit(-2);
}