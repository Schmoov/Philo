CC := cc -g3
CFLAGS := -Wall -Wextra #-Werror
LIB := -pthread

NAME := philo_bonus

SRC_DIR := src/
SRC := $(wildcard $(SRC_DIR)*.c)

OBJ_DIR := .obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LIB) $(CFLAGS) $^ -o $@ 

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)
	$(CC) $(LIB) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

:PHONY all clean fclean re
