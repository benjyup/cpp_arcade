##
## Makefile for  in /home/vincent.mesquita/rendu/Tek2/S3/cpp_arcade/lib/ncurses
## 
## Made by Vincent Mesquita
## Login   <vincent.mesquita@epitech.net>
## 
## Started on  Sun Mar 19 14:10:03 2017 Vincent Mesquita
## Last update Fri Apr  7 01:04:05 2017 vincen_s
##

NAME		=	../lib_arcade_opengl.so

SRC			=	src

INTERFACES	=	../interfaces

NCURSES		=	./openGL

CPP 		= 	g++

RM 		= 	rm -rf

CPPFLAGS	+=	-std=c++14 -W -Wall -Werror -Wextra -I$(INTERFACES)/ -I./src -fPIC -g3

LDFLAGS		=	-lGL -lGLEW -lSDL2 -lSDL_image -lSDL_ttf -std=c++11 -shared

SRCS		=	$(SRC)/OpenGltools.cpp\
			$(SRC)/Windows.cpp\
			$(SRC)/Label.cpp\
			$(SRC)/Evenement.cpp\
			$(INTERFACES)/Vector3d.cpp\
			$(SRC)/openglLib.cpp\
			$(SRC)/Object.cpp\

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
