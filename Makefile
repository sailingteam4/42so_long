NAME        := so_long
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -g

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

SRCS        :=    		  src/check_map.c \
                          src/data_clear.c \
                          src/end.c \
                          src/init_data.c \
                          src/init_map.c \
                          src/keyboard_event.c \
                          src/move_player.c \
                          src/move_player_utils.c \
                          src/parsing.c \
                          src/put_img_to_window.c \
                          src/read_map.c \
                          src/so_long.c \
                          src/utils.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

$(NAME): ${OBJS}
			@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@ $(MAKE) -C $(LIBFT_DIR)
			@chmod 777 mlx_linux/configure
			@ $(MAKE) -C mlx_linux all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ $(MAKE) -C mlx_linux clean
			@ $(MAKE) -C $(LIBFT_DIR) clean
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean 
			@ $(MAKE) -C $(LIBFT_DIR) fclean
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re