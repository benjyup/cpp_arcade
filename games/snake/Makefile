##
## Makefile for  in /home/vincent.mesquita/rendu/Tek2/S3/cpp_arcade/lib/ncurses
##
## Made by Vincent Mesquita
## Login   <vincent.mesquita@epitech.net>
##
## Started on  Sun Mar 19 14:10:03 2017 Vincent Mesquita
## Last update Sun Apr  9 15:46:15 2017 vincent.mesquita@epitech.eu
##

NAME		=	../lib_arcade_nibbler.so

SRC			=	src

INTERFACES	=	../../lib/interfaces

CPP 		= 	g++

RM 		    = 	rm -rf

CPPFLAGS	+=	-fPIC -shared -std=c++14 -W -Wall -Werror -Wextra -I$(INTERFACES)/ -I./src -g3

LDFLAGS		=	-shared

SRCS		=	$(SRC)/Snake.cpp\
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
