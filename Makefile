##
## Makefile for  in /home/vincent/rendu/cpp_arcade
## 
## Made by vincent.mesquita@epitech.eu
## Login   <vincent@epitech.net>
## 
## Started on  Tue Apr  4 21:40:11 2017 vincent.mesquita@epitech.eu
## Last update Sun Apr  9 15:41:15 2017 vincent.mesquita@epitech.eu
##

NAME		=	arcade

SRC		=	src

INTERFACES	=	lib/interfaces

CPP 		= 	g++

RM 		= 	rm -rf

NIBBLER		=	games/snake/

CPPFLAGS	+=	-std=c++14 -W -Wall -Werror -Wextra -I$(INTERFACES)/ -g3

LDFLAGS     	=   -ldl

SRCS		=	$(SRC)/main.cpp\
			$(SRC)/LibraryManager.cpp\
			$(SRC)/Menu.cpp\
			$(SRC)/MainObserver.cpp\
			$(INTERFACES)/Vector3d.cpp\

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) -o $(NAME) $(OBJS) $(LDFLAGS)
	make -C $(NIBBLER) all

clean:
	make -C $(NIBBLER) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(NIBBLER) fclean
	$(RM) $(NAME)


re: fclean all
	make -C $(NIBBLER) re

.PHONY: all clean fclean re
