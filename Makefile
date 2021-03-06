##
## Makefile for  in /home/vincent/rendu/cpp_arcade
## 
## Made by vincent.mesquita@epitech.eu
## Login   <vincent@epitech.net>
## 
## Started on  Tue Apr  4 21:40:11 2017 vincent.mesquita@epitech.eu
## Last update Sun Apr  9 23:03:25 2017 vincen_s
##

NAME		=	arcade

SRC		=	src

INTERFACES	=	lib/interfaces

CPP 		= 	g++

RM 		= 	rm -rf

NIBBLER		=	./games/snake/

SOLAR		=	./games/SolarFox/

CPPFLAGS	+=	-fpic -std=c++14 -W -Wall -Werror -Wextra -I$(INTERFACES)/ -g3

LDFLAGS     	=   	-ldl

SRCS		=	$(SRC)/main.cpp\
			$(SRC)/LibraryManager.cpp\
			$(SRC)/Menu.cpp\
			$(INTERFACES)/Vector3d.cpp\

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) -o $(NAME) $(OBJS) $(LDFLAGS)
	make -C $(NIBBLER)
	make -C $(SOLAR)

clean:
	$(RM) $(OBJS)
	make clean -C $(NIBBLER)
	make clean -C $(SOLAR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(NIBBLER)
	make fclean -C $(SOLAR)


re: fclean all

.PHONY: all clean fclean re
