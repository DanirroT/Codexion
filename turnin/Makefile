# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/18 17:59:26 by dmota-ri          #+#    #+#              #
#    Updated: 2026/07/22 14:36:44 by dmota-ri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

SRC_DIR = src/

SRC =	$(SRC_DIR)main.c\
		$(SRC_DIR)inputs.c\
		$(SRC_DIR)ft_split_space.c\
		$(SRC_DIR)coder_functs.c\
		$(SRC_DIR)coder_to_dongle.c\
		$(SRC_DIR)dongle_n_burnout_functs.c\
		$(SRC_DIR)lst_functs.c\
		$(SRC_DIR)queue_man.c\
		$(SRC_DIR)ft_trashs.c\
		$(SRC_DIR)time.c\
		$(SRC_DIR)safe_utils.c\
		$(SRC_DIR)utils_lib.c\
		$(SRC_DIR)misc_utils.c\
		$(SRC_DIR)ft_out.c\

OBJ_DIR = obj/

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC_DIR = inc/

INC = $(INC_DIR)codexion.h

CFLAGS = -Wall -Wextra -Werror -g -pthread
CC = cc $(CFLAGS)

RM = rm -fdr

VALGRIND = valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all

HELGRIND = valgrind --tool=helgrind

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(INC)
	$(CC) -I $(INC_DIR) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) -I $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)


fclean: clean
	$(RM) $(NAME)
	$(RM) db/ dbm/

re: fclean all

# valid
#       nb bout com deb ref nbc dcd sk
INPUTS = 200 200 200 200 200 3 100 edf
# INPUTS = 100 8000 200 200 200 3 1000 fifo
# invalid
#       nb bout com deb ref nbc dcd sk
# INPUTS = 3 100 200 200 200 3 100 fifo

test: $(NAME) db/
	@echo "          nb bout com deb ref nbc dcd sk"
	-./$(NAME) $(INPUTS) 2> db/debugging.txt

memtest: $(NAME) db/
	-$(VALGRIND) ./$(NAME) $(INPUTS) 2> db/debugging_mem.txt

helgrind: $(NAME) db/
	-$(HELGRIND) ./$(NAME) $(INPUTS) 2> db/debugging_hell.txt

# no extras
# TESTING =

# Memory leaks
# TESTING = valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all

# Threading issues
TESTING = valgrind --tool=helgrind

# search for pattern "----- (\d+) 1 " must total 13

test_many: $(NAME)
	@rm -fdr dbm/
	@mkdir -p dbm
	@echo "\nTesting NULL\n"
	-$(TESTING) ./$(NAME) 2> dbm/debugging_NULL.txt

	@echo "\nTesting with 1 Coder\n"
	$(TESTING) ./$(NAME) 1 1000 200 200 200 3 100 fifo 2> dbm/debugging_one.txt

	@echo "\nTesting with 2 Coders, no Burnout FIFO\n"
	$(TESTING) ./$(NAME) 2 8000 200 200 200 3 100 fifo 2> dbm/debugging_2sf.txt
	@echo "\nTesting with 2 Coders, no Burnout EDF\n"
	$(TESTING) ./$(NAME) 2 8000 200 200 200 3 100 edf 2> dbm/debugging_2se.txt

	@echo "\nTesting with 2 Coders, no Burnout FIFO, long cooldown\n"
	$(TESTING) ./$(NAME) 2 8000 200 200 200 3 1000 fifo 2> dbm/debugging_2lf.txt
	@echo "\nTesting with 2 Coders, no Burnout EDF, long cooldown\n"
	$(TESTING) ./$(NAME) 2 8000 200 200 200 3 1000 edf 2> dbm/debugging_2le.txt

	@echo "\nTesting with 2 Coders, Burnout! FIFO\n"
	$(TESTING) ./$(NAME) 2 100 200 200 200 3 100 fifo 2> dbm/debugging_2bf.txt
	@echo "\nTesting with 2 Coders, Burnout! EDF\n"
	$(TESTING) ./$(NAME) 2 100 200 200 200 3 100 edf 2> dbm/debugging_2be.txt

	@echo "\nTesting with 3 Coders, no Burnout FIFO\n"
	$(TESTING) ./$(NAME) 3 8000 200 200 200 3 100 fifo 2> dbm/debugging_3sf.txt
	@echo "\nTesting with 3 Coders, no Burnout EDF\n"
	$(TESTING) ./$(NAME) 3 8000 200 200 200 3 100 edf 2> dbm/debugging_3se.txt

	@echo "\nTesting with 3 Coders, no Burnout FIFO, long cooldown\n"
	$(TESTING) ./$(NAME) 3 8000 200 200 200 3 1000 fifo 2> dbm/debugging_3lf.txt
	@echo "\nTesting with 3 Coders, no Burnout EDF, long cooldown\n"
	$(TESTING) ./$(NAME) 3 8000 200 200 200 3 1000 edf 2> dbm/debugging_3le.txt

	@echo "\nTesting with 3 Coders, Burnout! FIFO\n"
	$(TESTING) ./$(NAME) 3 100 200 200 200 3 100 fifo 2> dbm/debugging_3bf.txt
	@echo "\nTesting with 3 Coders, Burnout! EDF\n"
	$(TESTING) ./$(NAME) 3 100 200 200 200 3 100 edf 2> dbm/debugging_3be.txt

# 	@echo "\nTesting with 10 Coders, no Burnout FIFO\n"
# 	$(TESTING) ./$(NAME) 10 8000 200 200 200 3 100 fifo 2> dbm/debugging_10sf.txt
# 	@echo "\nTesting with 10 Coders, no Burnout EDF\n"
# 	$(TESTING) ./$(NAME) 10 10000 200 200 200 3 100 edf 2> dbm/debugging_10se.txt

# 	@echo "\nTesting with 10 Coders, no Burnout FIFO, long cooldown\n"
# 	$(TESTING) ./$(NAME) 10 8000 200 200 200 3 1000 fifo 2> dbm/debugging_10lf.txt
# 	@echo "\nTesting with 10 Coders, no Burnout EDF, long cooldown\n"
# 	$(TESTING) ./$(NAME) 10 8000 200 200 200 3 1000 edf 2> dbm/debugging_10le.txt

# 	@echo "\nTesting with 10 Coders, Burnout! FIFO\n"
# 	$(TESTING) ./$(NAME) 10 100 200 200 200 3 100 fifo 2> dbm/debugging_10bf.txt
# 	@echo "\nTesting with 10 Coders, Burnout! EDF\n"
# 	$(TESTING) ./$(NAME) 10 100 200 200 200 3 100 edf 2> dbm/debugging_10be.txt

	@echo "\nTesting with 50 Coders, no Burnout FIFO\n"
	$(TESTING) ./$(NAME) 50 12000 200 200 200 3 100 fifo 2> dbm/debugging_50sf.txt
	@echo "\nTesting with 50 Coders, no Burnout EDF\n"
	$(TESTING) ./$(NAME) 50 12000 200 200 200 3 100 edf 2> dbm/debugging_50se.txt

	@echo "\nTesting with 50 Coders, no Burnout FIFO, long cooldown\n"
	$(TESTING) ./$(NAME) 50 12000 200 200 200 3 1000 fifo 2> dbm/debugging_50lf.txt
	@echo "\nTesting with 50 Coders, no Burnout EDF, long cooldown\n"
	$(TESTING) ./$(NAME) 50 12000 200 200 200 3 1000 edf 2> dbm/debugging_50le.txt

	@echo "\nTesting with 50 Coders, Burnout! FIFO\n"
	$(TESTING) ./$(NAME) 50 100 200 200 200 3 100 fifo 2> dbm/debugging_50bf.txt
	@echo "\nTesting with 50 Coders, Burnout! EDF\n"
	$(TESTING) ./$(NAME) 50 100 200 200 200 3 100 edf 2> dbm/debugging_50be.txt

	@echo "\nTesting with 100 Coders, no Burnout FIFO\n"
	$(TESTING) ./$(NAME) 100 12000 200 200 200 3 100 fifo 2> dbm/debugging_100sf.txt
	@echo "\nTesting with 100 Coders, no Burnout EDF\n"
	$(TESTING) ./$(NAME) 100 12000 200 200 200 3 100 edf 2> dbm/debugging_100se.txt

	@echo "\nTesting with 100 Coders, no Burnout FIFO, long cooldown\n"
	$(TESTING) ./$(NAME) 100 12000 200 200 200 3 1000 fifo 2> dbm/debugging_100lf.txt
	@echo "\nTesting with 100 Coders, no Burnout EDF, long cooldown\n"
	$(TESTING) ./$(NAME) 100 12000 200 200 200 3 1000 edf 2> dbm/debugging_100le.txt

	@echo "\nTesting with 100 Coders, Burnout! FIFO\n"
	$(TESTING) ./$(NAME) 100 100 200 200 200 3 100 fifo 2> dbm/debugging_100bf.txt
	@echo "\nTesting with 100 Coders, Burnout! EDF\n"
	$(TESTING) ./$(NAME) 100 100 200 200 200 3 100 edf 2> dbm/debugging_100be.txt

	@echo "\nTesting with 200 Coders, no Burnout FIFO\n"
	$(TESTING) ./$(NAME) 200 20000 200 200 200 3 100 fifo 2> dbm/debugging_200sf.txt
	@echo "\nTesting with 200 Coders, no Burnout EDF\n"
	$(TESTING) ./$(NAME) 200 20000 200 200 200 3 100 edf 2> dbm/debugging_200se.txt

	@echo "\nTesting with 200 Coders, no Burnout FIFO, long cooldown\n"
	$(TESTING) ./$(NAME) 200 20000 200 200 200 3 1000 fifo 2> dbm/debugging_200lf.txt
	@echo "\nTesting with 200 Coders, no Burnout EDF, long cooldown\n"
	$(TESTING) ./$(NAME) 200 20000 200 200 200 3 1000 edf 2> dbm/debugging_200le.txt

	@echo "\nTesting with 200 Coders, Burnout! FIFO\n"
	$(TESTING) ./$(NAME) 200 100 200 200 200 3 100 fifo 2> dbm/debugging_200bf.txt
	@echo "\nTesting with 200 Coders, Burnout! EDF\n"
	$(TESTING) ./$(NAME) 200 100 200 200 200 3 100 edf 2> dbm/debugging_200be.txt

db/:
	@mkdir -p db

dbm/:
	@mkdir -p dbm

retest: fclean test

# number_of_coders
# time_to_burnout
# time_to_compile
# time_to_debug
# time_to_refactor
# number_of_compiles_required
# dongle_cooldown
# scheduler

lint:
	norminette $(SRC) $(INC)
