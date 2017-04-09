
NAME		=	../lib_arcade_solar_fox.so

SRC			=	src

INTERFACES	=	../../lib/interfaces

CPP 		= 	g++

RM 		    = 	rm -rf

CPPFLAGS	+=	-fPIC -std=c++14 -W -Wall -Werror -Wextra -I$(INTERFACES)/ -I./src -g3

LDFLAGS		=	-shared

SRCS		=	$(SRC)/Solar_Fox.cpp\
			../EvenementGame.cpp \
		 	$(INTERFACES)/Vector3d.cpp

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
