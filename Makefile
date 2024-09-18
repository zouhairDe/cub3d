CC = cc
FLAGS = -g -fsanitize=address#-Wall -Wextra -Werror
LIBS =   -lmlx -framework OpenGL -framework AppKit
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
GNL_DIR = gnl/
GNL = $(GNL_DIR)get_next_line_bonus.c $(GNL_DIR)get_next_line_utils_bonus.c
GNL_HEADER = $(GNL_DIR)get_next_line_bonus.h

NAME = cub3d
CUB3D_HEADER = $(HEADER_DIR)cub3d.h
HEADER_DIR = includes/

SRC_DIR = mandatory/src/
OBJ_DIR = mandatory/obj/
FILES = main.c utils1.c map_check1.c

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

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

all: $(LIBFT) $(OBJ_DIR) $(NAME) thanks

thanks:
	@echo "$(BLACK)$(WHITE_BG)$(BOLD)Compilation complete.$(RESET)"

$(LIBFT): $(LIBFT_DIR)
	@echo "$(GREEN)$(BOLD)Compiling libft$(DEFAULT)"
	@make -sC $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(LIBS) $(FLAGS) $(OBJ) $(LIBFT) $(GNL) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(CUB3D_HEADER) $(GNL_HEADER)
	@$(CC) -Imlx $(FLAGS) -I $(HEADER_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR) -c $< -o $@
	$(update_progress)

clean:
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean
	@echo "$(RED)$(BOLD)Cleaning libft Object files...$(DEFAULT)"
	@echo "$(RED)$(BOLD)[$(NAME)] object Removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@echo "$(RED)$(BOLD)Cleaning libft$(DEFAULT)"
	@echo "$(RED)$(BOLD)[$(NAME)] executable Removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re thanks

