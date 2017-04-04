
NAME		=	sfml

SRCS		=	main.cpp

OBJS		=	$(SRCS:.cpp=.o)

CC		=	g++

CFLAGS		=	-W -Wall -Werror 

RM		=	rm -f


all: $(NAME)


$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system 

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
