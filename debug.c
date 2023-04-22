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

