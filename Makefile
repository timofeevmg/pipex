NAME		= pipex

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

LIB			= libft.a
LIB_DIR		= libft/
LIBFT		= $(addprefix $(LIB_DIR), $(LIB))

M_HDR_LIST	= pipex.h
HDR_DIR		= includes/
M_HDR		= $(addprefix $(HDR_DIR), $(M_HDR_LIST))

M_SRC_LIST	=	pipex.c \
				check_open.c \
				env_paths.c \
				child_proc.c \
				clean_close_exit.c
M_SRC_DIR	= mandatory/
M_SRC		= $(addprefix $(M_SRC_DIR), $(M_SRC_LIST))
M_OBJ		= $(M_SRC:.c=.o)


all: $(NAME)

$(NAME): $(M_OBJ) $(LIBFT)
		@echo "$(YELLOW)Linking...$(DEFAULT)"
		$(CC) $(CFLAGS) $(M_OBJ) $(LIBFT) -o $(NAME)
		@echo "$(GREEN)Done.$(DEFAULT)"

%.o: %.c $(M_HDR) Makefile
		@echo "$(YELLOW)Compiling...$(DEFAULT)"
		$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		@echo "$(YELLOW)Compiling $(LIB)...$(DEFAULT)"
		@make -C $(LIB_DIR)
		@make clean -C $(LIB_DIR)
		@echo "$(GREEN)Done.$(DEFAULT)"

bonus:
	$(CC) $(CFLAGS) bonus/pipex_bonus.c libft/libft.a -o pipex

clean:
		@echo "$(RED)Cleaning...$(DEFAULT)"
		@make clean -C $(LIB_DIR)
		$(RM) $(M_OBJ)
		@echo "$(GREEN)Done.$(DEFAULT)"


fclean: clean
		@echo "$(RED)Cleaning all...$(DEFAULT)"
		@make fclean -C $(LIB_DIR)
		$(RM) $(NAME)
		@echo "$(GREEN)Done.$(DEFAULT)"


re: fclean all


.PHONY: all clean fclean re

#coloured output
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
DEFAULT	= \033[0m
