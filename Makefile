##
## Makefile for  in /home/vincent/rendu/cpp_arcade
## 
## Made by vincent.mesquita@epitech.eu
## Login   <vincent@epitech.net>
## 
## Started on  Tue Apr  4 21:40:11 2017 vincent.mesquita@epitech.eu
## Last update Wed Apr  5 00:24:21 2017 vincent.mesquita@epitech.eu
##

NAME		=	arcade

SRC		    =	src

INTERFACES	=	lib/interfaces

CPP 		= 	g++

RM 		    = 	rm -rf

CPPFLAGS	+=	-std=c++14 -W -Wall -Werror -Wextra -I$(INTERFACES)/ -g3

LDFLAGS     =   -ldl

SRCS		=	$(SRC)/main.cpp\
			$(SRC)/LibraryManager.cpp\

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