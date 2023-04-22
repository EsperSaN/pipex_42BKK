#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
// for the [write, read, close , access, dup ,dup2] 
// to write in FD
// ssize_t write(int fd, const void *buf, size_t count);
// to read the FD
// ssize_t read(int fd, void *buf, size_t count);
// to close the FD
// int close(int fd);
// check user's permissions for a file
// int access(const char *pathname, int mode);
// allocate the new lowest avalable fd to the oldfd like open(2) 
// int dup (int oldfd)
// like dup but auto close and point into the newfd if newfd already opening
// int dup2 (int oldfd, int newfd)
//Note the following points:
//*  If oldfd is not a valid file descriptor, then the call fails,
//     and newfd is not closed.
//*  If oldfd is a valid file descriptor, and newfd has the same
//      value as oldfd, then dup2() does nothing, and returns newfd.
// unlink - delete a name and possibly the file it refers to
// int unlink(const char *pathname);
// int pipe(int pipefd[2]); <<-- create pipe
// pid_t fork(void); <<--create a child process
// const char *pathname, char *const argv[],char *const envp[]; <<-- execute program
// int execve(const char *pathname, char *const argv[], char *const envp[]);

#include <fcntl.h>
//for [open] 
// to open the file and point with FD
// int open(const char *pathname, int flags, mode_t mode);

#include <stdlib.h>
// for [malloc, free]
// allocate the heap mem to pointer
//void *malloc(size_t size);
//void free(void *ptr);
// exit - cause normal process termination
//  noreturn void exit(int status);

#include <stdio.h>
// perror - print a system error message
// void perror(const char *s);

#include <string.h>
//return string describing error number
// char *strerror(int errnum);

#include <sys/wait.h>
// wait for process to change state
// pid_t wait(int *wstatus);
// pid_t waitpid(pid_t pid, int *wstatus, int options);

typedef struct s_pipevar{
	int		int_fdin ;
	int 	int_fdout ;
	int		pipe[2];

	int 	pipe_readwrite[2];

	char	**tstr_envpath ;

	char	*str_CmdPath_1 ;
	char	*str_CmdPath_2 ;

	char	**tstr_Command1 ;
	char	**tstr_Command2 ;

}	t_var;


void 	get_envpath(char **ep, char ***envbox);
char	*get_CmdPath_slash(char *command, char** env);
void 	split_the_command_and_assign(char **av, t_var *pipe_var);
//free command free.c
void free_close_var_in_pipe_var(t_var *pipe_var);
void free_2D(char **str);

//set the var in st to null PREVENT THE LEAKE
void 	struct_init(t_var *var);

//error
void 	exit_due_error(char *str, int errornum, t_var *var);
void error_cmd(char* command ,t_var *var);

//free
void 	free_close_var_in_pipe_var(t_var *pipe_var);\
void 	free_2D(char **str);

// for debug by print var in struct
void 	printcheck(t_var pipe_var);

// tool 
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	how_long(char const *s, char c);
size_t	count_on_me(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		str_n_compare(const char *s1, const char *s2, size_t n); //< modify for the split
void 	exev_child(t_var *pipe_var, char** ep);
void 	exev_parent(t_var *pipe_var, char** ep);
#endif
