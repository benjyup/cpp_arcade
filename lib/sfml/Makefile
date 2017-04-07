
NAME		=	../lib_arcade_sfml.so

SRC		=	src

INTERFACES	=	../interfaces

CPP 		= 	g++

RM 		= 	rm -rf

CPPFLAGS	+=	 -std=c++14 -W -Wall -Werror -Wextra -I$(INTERFACES)/ -fPIC

LDFLAGS		=	-shared -lsfml-graphics -lsfml-window -lsfml-system

SRCS		=	$(SRC)/Window.cpp \
                $(SRC)/Object.cpp \
                $(SRC)/Evenement.cpp \
                $(SRC)/SfmlLib.cpp \
                $(SRC)/Label.cpp \
                $(SRC)/Sprite.cpp \
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
