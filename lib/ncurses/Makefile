##
## Makefile for  in /home/vincent.mesquita/rendu/Tek2/S3/cpp_arcade/lib/ncurses
## 
## Made by Vincent Mesquita
## Login   <vincent.mesquita@epitech.net>
## 
## Started on  Sun Mar 19 14:10:03 2017 Vincent Mesquita
## Last update Fri Mar 24 14:25:05 2017 vincent.mesquita@epitech.eu
##

NAME		=	libtest.so

SRC			=	src

INTERFACES	=	../interfaces

NCURSES		=	./ncurses

CPP 		= 	g++

RM 		= 	rm -rf

CPPFLAGS	+=	-W -Wall -Werror -Wextra -I$(INTERFACES)/ -fPIC

LDFLAGS		=	-lncurses -shared

SRCS		=	$(SRC)/Window.cpp\
			$(SRC)/NcursesLib.cpp\
			$(SRC)/NcursesTools.cpp\

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
