SRC_NAME = main.c \
			mlx_general_func.c \
			utils.c \
			mlx_img_func.c \
			mlx_loop_hook.c \
			mlx_key_hook.c \
			misc_hooks.c \
			parse.c \
			debug.c

OBJ_PATH = ./obj/

INC_PATH = ./includes ./libsrcs/libft/includes/ ./libsrcs/minilibx ./libsrcs/ft_printf/includes ./libsrcs/libftmatrices/includes

SRC_PATH = ./srcs/

NAME = wolf3d

CC = gcc
CFLAGS =  -Wextra -Wall -g
LFLAGS = -lft -framework OpenGL -framework AppKit -lm -lmlx -lftprintf -lftmatrices
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

$(LIB_DIR)libftprintf.a:
	@mkdir -p $(LIB_DIR)
	@make -C libsrcs/ft_printf

$(LIB_DIR)libftmatrices.a:
	@mkdir -p $(LIB_DIR)
	@make -C libsrcs/libftmatrices

$(NAME) : $(LIB_DIR)libmlx.a $(LIB_DIR)libft.a $(LIB_DIR)libftprintf.a $(LIB_DIR)libftmatrices.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) $(LFLAGS) -o $@ 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

partial_clean:
	@rm -fv $(OBJ)

clean:
	@rm -fv $(OBJ)
	@rmdir -p $(OBJ_PATH) 2> /dev/null || true
	@make -C libsrcs/libft clean
	@make -C libsrcs/minilibx clean
	@make -C libsrcs/ft_printf clean
	@make -C libsrcs/libftmatrices clean

fclean: clean
	@rm -fv $(NAME)
	@make -C libsrcs/libft fclean
	@make -C libsrcs/minilibx fclean
	@make -C libsrcs/ft_printf fclean
	@make -C libsrcs/libftmatrices fclean

re: fclean all

.PHONY : all clean fclean re
