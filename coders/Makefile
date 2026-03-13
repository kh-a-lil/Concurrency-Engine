NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c utils.c init.c routine.c monitor.c dongle.c heap.c utils2.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
