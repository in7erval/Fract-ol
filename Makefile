.PHONY: all clean fclean re

NAME = fractol
CC = gcc
FLAGS = -Wall -Werror -Wextra -O3 -O0 -g
LIBRARIES = -lmlx -lft -L$(LIBFT_DIRECTORY) -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(MINILIBX_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./minilibx_macos/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

HEADERS_LIST = fractol.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = main.c \
 			utils.c \
 			drawing.c \
 			primitive_draw.c \
 			mouse.c \
 			ctrls.c \
 			init.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS
GREEN = \033[0;32m
BOLD_GREEN = \033[1;32m
RED = \033[0;31m
BOLD_RED = \033[1;31m
YELLOW = \033[0;33m
BOLD_YELLOW = \033[1;33m
BLUE = \033[0;34m
BOLD_BLUE = \033[1;34m
MAGENTA = \033[0;35m
BOLD_MAGENTA = \033[1;35m
CYAN = \033[0;36m
BOLD_CYAN = \033[1;36m
RESET = \033[0m
CLEAR_LINE = \033[0K
BEGIN_LINE = \033[0A

ALL_FILES = $(shell find sources/*.c | wc -l | sed -E "s/ //g")
NUM_FI = $(shell find objects/*.o | wc -l | sed -E "s/ //g")
NUM_FILES = $(shell bc <<< $(NUM_FI)+1)

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n$(CLEAR_LINE)$(BOLD_RED)\tFract'ol is ready!$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@echo "$(CLEAR_LINE)$(MAGENTA)Creating object file $(BOLD_CYAN)$<$(RESET) $(MAGENTA)[$(NUM_FILES) : $(ALL_FILES)]in $(OBJECTS_DIRECTORY)$(RESET)$(BEGIN_LINE)"
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "$(BOLD_CYAN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(MINILIBX):
	@echo "$(BOLD_YELLOW)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(GREEN)object files $(BOLD_RED)deleted$(RESET)"
	@echo "$(GREEN)$(OBJECTS_DIRECTORY) $(BOLD_RED)deleted$(RESET)"

fclean: clean
	@rm -f $(MINILIBX)
	@echo "$(GREEN)$(MINILIBX) $(BOLD_RED)deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(GREEN)$(LIBFT) $(BOLD_RED)deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME) $(BOLD_RED)deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all