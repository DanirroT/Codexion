# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/25 19:11:53 by dmota-ri          #+#    #+#              #
#    Updated: 2026/04/02 20:51:22 by dmota-ri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Codexion

SRC =	main.c\
		utils_lib.c\
		inputs.c\
		ft_trim.c\
		ft_trashs.c\
		ft_split.c\
		ft_split_space.c

OBJ = $(SRC:.c=.o)

#BONUS = ft_lists_1_bonus.c ft_lists_2_bonus.c

#B_OBJ = $(BONUS:.c=.o)

INC = codexion.h

CFLAGS = -Wall -Wextra -Werror
CC = cc $(CFLAGS)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) -I . $(OBJ) -o $(NAME)

%.o: %.c $(INC)
	$(CC) -I . -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

#bonus: $(B_OBJ) $(NAME)
#	$(CC) -I . $(OBJ) -o $(B_OBJ)
#	ranlib $(NAME)
