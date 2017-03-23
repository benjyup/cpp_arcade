NAME		=	sfml

SRC		=	src

INTERFACES	=	../interfaces

CPP 		= 	g++

RM 		= 	rm -rf

CPPFLAGS	+=	-W -Wall -Werror -Wextra -I$(INTERFACES)/

LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system

SRCS		=	main.cpp \
			$(SRC)/Window.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
