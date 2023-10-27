##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	systeme_de_gestion
compil = 	-l csfml-graphics -l csfml-system -l csfml-window -l csfml-audio

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(SRC) $(compil)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f *~
	rm -f *#
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean re
