#include "pipex.h"

void	putstr_fd(char *str, int fd)
{
	while(*str)
	{
		write(fd, str, 1);
		str++;
	}
}

void    put_error(char *str ,int errornum)
{
    dprintf(2 ,"[%s] ", str);
    perror("Error: ");
    //exit(errornum);
    (void)errornum;
}
void    put_errorcmd(char *str ,int errornum)
{
    dprintf(2,"Error: ");
    if(str_n_compare(str , "/", 1))
        dprintf(2 ,"no such file or directory");
    else
        dprintf(2, "command not found");
    dprintf(2 ,": %s", str);
    exit(errornum);
}