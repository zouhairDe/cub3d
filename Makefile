CC = cc
FLAGS = -o3 -g  -Wall -Wextra -Werror #-fsanitize=address
LIBS = -framework OpenGL -framework AppKit
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
GNL_DIR = gnl/
GNL = $(GNL_DIR)get_next_line_bonus.c $(GNL_DIR)get_next_line_utils_bonus.c
GNL_HEADER = $(GNL_DIR)get_next_line_bonus.h

NAME = cub3D
CUB3D_HEADER = $(HEADER_DIR)cub3d.h
HEADER_DIR = mandatory/includes/

BONUS_NAME = $(BONUS_DIR)cub3D_bonus
BONUS_DIR = cub3d_bonus/
BONUS_HEADER_DIR = $(BONUS_DIR)includes/
BONUS_HEADER = $(BONUS_HEADER_DIR)cub3d_bonus.h
BONUS_SRC_DIR = $(BONUS_DIR)src/
BONUS_OBJ_DIR = $(BONUS_DIR)obj/
BONUS_FILES = main_bonus.c utils1_bonus.c map_check1_bonus.c simulation_bonus.c math_bonus.c funcs_bonus.c\
	funcs1_bonus.c dda_funcs_bonus.c garbage_collector_bonus.c map_check2_bonus.c utils2_bonus.c\
	utils4_bonus.c utils5_bonus.c map_check3_bonus.c map_check4_bonus.c key_handler_bonus.c\
	map_check5_bonus.c map_check6_bonus.c simulation2_bonus.c utils6_bonus.c

SRC_DIR = mandatory/src/
OBJ_DIR = mandatory/obj/
FILES = main.c utils1.c map_check1.c simulation.c math.c funcs.c dda_funcs.c garbage_collector.c\
	utils2.c map_check2.c utils3.c map_check3.c key_handler.c map_check4.c map_check5.c utils4.c utils5.c

BOBJ = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_FILES:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

MLX = ./mlx/libmlx.a
MLX_DIR = mlx/



RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
BLUE = \033[0;34m
BOLD = \033[1m
RESET = \033[0m
BLACK = \033[30m
WHITE_BG = \033[47m
UP = \033[A

TOTAL_FILES = $(words $(FILES))
COMPILED_COUNT = 0

define update_progress
	@bash -c 'if [ $(COMPILED_COUNT) -eq 0 ]; then echo; fi;'
	$(eval COMPILED_COUNT=$(shell echo $$(($(COMPILED_COUNT) + 1))))
	$(eval PERCENT=$(shell echo $$(($(COMPILED_COUNT) * 100 / $(TOTAL_FILES)))))
	@bash -c 'echo -e "$(UP)\r$(GREEN)$(BOLD)[$(PERCENT)%] Compiling Cub3d...$(RESET)"'
endef

all: $(OBJ_DIR) $(NAME) thanks

$(MLX): ./mlx/mlx.h
	@echo "$(GREEN)$(BOLD)Compiling mlx$(DEFAULT)"
	@make -sC $(MLX_DIR)

thanks:
	@echo "$(BLACK)$(WHITE_BG)$(BOLD)Compilation complete.$(RESET)"
	@rm -rf *.dSYM $(BONUS_DIR)*.dSYM *.vscode 
		
bonus: $(LIBFT) $(BONUS_OBJ_DIR) $(BONUS_NAME) thanks 

$(LIBFT): $(LIBFT_DIR)
	@echo "$(GREEN)$(BOLD)Compiling libft$(DEFAULT)"
	@make -sC $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BONUS_OBJ_DIR):
	@mkdir -p $(BONUS_OBJ_DIR)

$(NAME): $(MLX) $(OBJ) $(LIBFT)
	@$(CC) $(LIBS) $(MLX) $(FLAGS) $(OBJ) $(LIBFT) $(GNL) -o $(NAME)

$(BONUS_NAME): $(MLX) $(BOBJ) $(LIBFT)
	@$(CC) $(LIBS) $(MLX) $(FLAGS) $(BOBJ) $(LIBFT) $(GNL) -o $(BONUS_NAME)


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(CUB3D_HEADER) $(GNL_HEADER) ./mlx/mlx.h
	@$(CC) $(FLAGS) -I $(HEADER_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR) -c $< -o $@
	$(update_progress)

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(BONUS_HEADER) $(GNL_HEADER)
	@$(CC) $(FLAGS) -I $(BONUS_HEADER_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR) -c $< -o $@
	$(update_progress)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BONUS_OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean
	@echo "$(RED)$(BOLD)Cleaning object files...$(DEFAULT)"
	@echo "$(RED)$(BOLD)[$(NAME)] objects Removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@make -sC $(LIBFT_DIR) fclean
	@make -sC $(MLX_DIR) clean
	@echo "$(RED)$(BOLD)Cleaning executables$(DEFAULT)"
	@echo "$(RED)$(BOLD)[$(NAME)] executables Removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus thanks