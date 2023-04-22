NAME = pipex

SRC = debug.c error.c free.c tool.c util.c process.c pipex.c
 
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
