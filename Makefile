NAME = pipex

SRC = pipex.c
 
CC = gcc

CFLAGS = -Wall -Werror -Wextra 

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	 $(CC) $(SRC) -o $(NAME)
clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	
re : fclean $(NAME)

.PHONY : clean fclean re all
