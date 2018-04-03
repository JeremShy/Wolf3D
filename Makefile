SRC_NAME = main.c

OBJ_PATH = ./obj/

INC_PATH = ./include ./libsrcs/libft/includes/ ./libsrcs/minilibx

SRC_PATH = ./srcs/

NAME = wolf3d

CC = gcc
CFLAGS =  -Wextra -Wall -g
LFLAGS = -lft -framework OpenGL -framework AppKit -lm -lmlx
LIB_DIR = ./lib/

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ_NAME = $(SRC_NAME:.c=.o)

INC = $(addprefix -I,$(INC_PATH))

all : $(NAME)

$(LIB_DIR)libmlx.a:
	@mkdir -p $(LIB_DIR)
	@make -C libsrcs/minilibx

$(LIB_DIR)libft.a:
	@mkdir -p $(LIB_DIR)
	@make -C libsrcs/libft

$(NAME) : $(LIB_DIR)libmlx.a $(LIB_DIR)libft.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) $(LFLAGS) -o $@ 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rmdir -p $(OBJ_PATH) 2> /dev/null || true
	@make -C libsrcs/libft clean
	@make -C libsrcs/minilibx clean

fclean: clean
	@rm -fv $(NAME)
	@make -C libsrcs/libft fclean
	@make -C libsrcs/minilibx fclean

re: fclean all

.PHONY : all clean fclean re
