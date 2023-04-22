#include "./pipex.h"
void printcheck(t_var pipe_var)
{
	printf("\n---------------- checker -------------");
	printf("\n fdin %d \n fdout %d\n CMDP 1 %s\n CMDP2 %s\n",pipe_var.int_fdin,pipe_var.int_fdout,pipe_var.str_CmdPath_1,pipe_var.str_CmdPath_2);
	int i = 0;
	printf("---------------- env -----------------\n");
	while(pipe_var.tstr_envpath != NULL && pipe_var.tstr_envpath[i]  )
	{
		printf("%s\n",pipe_var.tstr_envpath[i]);
		i++;
	}
	printf("--------------------------------------\n");
	i = 0;
	printf("---------------- CMD1 -----------------\n");
	while(pipe_var.tstr_Command1[i])
	{
		printf("%s \n", pipe_var.tstr_Command1[i]);
		i++;
	}
	printf("---------------- CMD2 -----------------\n");
	i = 0;
	while(pipe_var.tstr_Command2[i])
	{
		printf("%s \n", pipe_var.tstr_Command2[i]);
		i++;
	}
}

void free_2D(char **str)
{
	int i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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

int main(int ac, char** av, char **ep)
{
	t_var pipe_var;

	if(ac != 5)
	{
		printf("not enought arg");
		return (-1);
	}
	struct_init(&pipe_var);
	pipe_var.int_fdin = open(av[1], O_RDONLY);//<< the av[1] is the input file and must be valid
	if (pipe_var.int_fdin < 0)
		exit_due_error("Error when open the input file", 0, &pipe_var);
	get_envpath(ep,&pipe_var.tstr_envpath);
	//  <---- if no path should run any ways
	split_the_command_and_assign(av, &pipe_var);
	pipe_var.str_CmdPath_1 = get_CmdPath_slash(pipe_var.tstr_Command1[0],pipe_var.tstr_envpath);
	if(pipe_var.str_CmdPath_1 == NULL)
		exit_due_error("the first command is not found or not excutable", 0, &pipe_var);
	pipe_var.str_CmdPath_2 = get_CmdPath_slash(pipe_var.tstr_Command2[0],pipe_var.tstr_envpath);
	if(pipe_var.str_CmdPath_2 == NULL)
		exit_due_error("the second command is not found or not excutable", 0, &pipe_var);
	pipe_var.int_fdout = open(av[4], O_RDWR|O_CREAT, 0777);
	if(pipe_var.int_fdout == -1)
		exit_due_error("Error when open the output or create output", 0, &pipe_var);
		
	printcheck(pipe_var);
	pipe(pipe_var.pipe);
	int id = fork();
	if(id == 0)
	{
		dup2(pipe_var.pipe[1], 1);
		dup2(pipe_var.int_fdin, 0);
		close(pipe_var.pipe[0]);
		execve(pipe_var.str_CmdPath_1,pipe_var.tstr_Command1,ep);
		printf("error exe1");
	}
	else
	{
		wait(NULL);
		dup2(pipe_var.pipe[0], 0);
		close(pipe_var.pipe[1]);
		dup2(pipe_var.int_fdout, 1);
		execve(pipe_var.str_CmdPath_2,pipe_var.tstr_Command2,ep);
		printf("error exe2");
	}
	
	free_close_var_in_pipe_var(&pipe_var);
}	
