##
## Makefile for  in /home/vincent.mesquita/rendu/Tek2/S3/cpp_arcade/lib/ncurses
## 
## Made by Vincent Mesquita
## Login   <vincent.mesquita@epitech.net>
## 
## Started on  Sun Mar 19 14:10:03 2017 Vincent Mesquita
## Last update Sun Mar 19 14:36:43 2017 Vincent Mesquita
##

NAME		=	test

SRC			=	src

INTERFACES	=	../interfaces

NCURSES		=	./ncurses

CPP 		= 	g++

RM 		= 	rm -rf

CPPFLAGS	+=	-W -Wall -Werror -Wextra -I$(INTERFACES)/ -I$(NCURSES)/include/ncurses/

LDFLAGS		=	-lncurses -L$(NCURSES)/lib64/

SRCS		=	main.cpp \
				$(SRC)/Window.cpp\

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
