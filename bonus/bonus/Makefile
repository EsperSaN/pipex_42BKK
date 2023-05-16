NAME = pipex

SRC = pipe_util.c pipex.c pipex_tool.c error.c
 
CC = gcc

CFLAGS = -Wall -Werror -Wextra 

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	 $(CC) $(OBJ) -o $(NAME)
clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	
re : fclean $(NAME)

.PHONY : clean fclean re all