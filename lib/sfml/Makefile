NAME		=	sfml.so

SRC		=	src

INTERFACES	=	../interfaces

CPP 		= 	g++

RM 		= 	rm -rf

CPPFLAGS	+=	-fPIC -W -Wall -Werror -Wextra -I$(INTERFACES)/

LDFLAGS		=	-shared -lsfml-graphics -lsfml-window -lsfml-system

SRCS		=	$(SRC)/Window.cpp \
			$(INTERFACES)/Vector3d.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) -o $(NAME) $(OBJS) $(LDFLAGS)
	g++ -o sfml main.cpp ./src/Window.cpp ../interfaces/Vector3d.cpp ./src/Object.cpp -g3 -ldl -lsfml-graphics -lsfml-window -lsfml-system -I../interfaces/ -I./src/
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
