NAME = pipex

NAME_BONUS = pipex

SRC = pipe_util.c pipex.c pipex_tool.c error.c

SRC_B = pipe_util.c pipex_bonus.c pipex_tool.c error.c

CC = gcc

CFLAGS = -Wall -Werror -Wextra 

OBJ = $(SRC:.c=.o)

BOBJ = $(SRC:.c=.o)

all : $(NAME)

bonus : $(BOBJ)
	$(CC) $(BOBJ) -o $(NAME_BONUS)

$(NAME) : $(OBJ)
	 $(CC) $(OBJ) -o $(NAME)
clean :
	rm -rf $(OBJ) $(BOBJ)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)
	
re : fclean $(NAME)

.PHONY : clean fclean re all