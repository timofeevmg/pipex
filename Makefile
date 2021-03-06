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

B_HDR_LIST	= pipex_bonus.h
B_HDR		= $(addprefix $(HDR_DIR), $(B_HDR_LIST))

B_SRC_LIST	=	pipex_bonus.c\
				prepare_bonus.c\
				heredoc_bonus.c\
				env_paths_bonus.c\
				clean_exit_bonus.c
B_SRC_DIR	= bonus/
B_SRC		= $(addprefix $(B_SRC_DIR), $(B_SRC_LIST))
B_OBJ		= $(B_SRC:.c=.o)
GNL_LIST	=	get_next_line.c\
				get_next_line_utils.c
GNL_DIR		= bonus/gnl/
GNL_SRC		= $(addprefix $(GNL_DIR), $(GNL_LIST))
GNL_OBJ		= $(GNL_SRC:.c=.o)



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

bonus: $(B_OBJ) $(GNL_OBJ) $(M_HDR = $(B_HDR))
		$(RM) $(NAME)
		$(CC) $(CFLAGS) $^ $(LIBFT) -o $(NAME)

debug: $(B_SRC) $(GNL_SRC)
		$(CC) $(B_SRC) $(GNL_SRC) $(LIBFT) -g

clean:
		@echo "$(RED)Cleaning...$(DEFAULT)"
		@make clean -C $(LIB_DIR)
		$(RM) $(M_OBJ)
		$(RM) $(GNL_OBJ)
		$(RM) $(B_OBJ)
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
