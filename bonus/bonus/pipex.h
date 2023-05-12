#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
void	run_command(char *cmd, char **envbox, int to_input ,char **ev);
int     is_execute(char *cmd);
void	put_run_error(char *cmd ,int errnum);
void	putstr_fd(char *str, int fd);
char    **get_envpath(char **ep);
char	*get_cmdPath(char *command, char **env);

size_t	ft_strlen(const char *s);
int	str_n_compare(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	count_on_me(char const *s, char c);
size_t	how_long(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
#endif