GREEN_B = "\033[1;32m"
RED_BI = "\033[1;3;31m"
BLUE_I = "\033[3;34m"
YELLOW = "\033[0;33m"
RESET = "\033[0m"

CC = cc 
CFLAGS = -Wall -Wextra -Werror -I/Users/mbamatra/homebrew/opt/readline/include -g3
LDFLAGS = -L/Users/mbamatra/homebrew/opt/readline/lib -lreadline

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCDIR = SRC
OBJDIR = BOBJ
NAME = minishell
SOURCES = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)
	@echo $(GREEN_B)"\n$(NAME) is Compiled.🐢 \n"$(RESET)

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L$(LIBFT_DIR) -lft $(LDFLAGS)
	@echo $(BLUE_I)"$(NAME) has been linked successfully."$(RESET)

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo $(YELLOW)".\c"$(RESET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(YELLOW)".\c"$(RESET)

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean
	@echo $(YELLOW)"Cleaned"$(RESET)

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo $(YELLOW)"Fully cleaned"$(RESET)

re: fclean all

.PHONY: all bonus clean fclean re

valgrind : all
	./check_leaks.sh
# GREEN_B = "\033[1;32m"
# RED_BI = "\033[1;3;31m"
# BLUE_I = "\033[3;34m"
# YELLOW = "\033[0;33m"
# RESET = "\033[0m"

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -I/Users/mbamatra/homebrew/opt/readline/include -L/Users/mbamatra/homebrew/opt/readline/lib

# LIBFT_DIR = ./libft
# LIBFT = $(LIBFT_DIR)/libft.a

# SRCDIR = SRC
# OBJDIR = BOBJ
# NAME = minishell
# SOURCES = $(shell find $(SRCDIR) -type f -name '*.c')
# OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# all: $(NAME)
# 	@echo $(GREEN_B)"\n$(NAME) is Compiled.🐢 \n"$(RESET)

# $(NAME): $(OBJECTS) $(LIBFT)
# 	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L$(LIBFT_DIR) -lft  -lreadline

# $(LIBFT):
# 	@make -C $(LIBFT_DIR)
# 	@echo $(YELLOW)".\c"$(RESET)
	
# $(OBJDIR)/%.o: $(SRCDIR)/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	@rm -rf $(OBJDIR)
# 	@make -C $(LIBFT_DIR) clean
# 	@echo $(YELLOW)"Cleaned"$(RESET)

# fclean: clean
# 	@rm -rf $(NAME)
# 	@make -C $(LIBFT_DIR) fclean
# 	@echo $(YELLOW)"Fully cleaned"$(RESET)
	
# re: fclean all

# .PHONY: all bonus clean fclean re
