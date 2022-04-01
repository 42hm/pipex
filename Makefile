# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 22:37:29 by hmoon             #+#    #+#              #
#    Updated: 2022/04/02 02:45:48 by hmoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= pipex
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
RM				:= rm -rf

LIBFT			:= ./libft/libft.a
LIBFT_DIR		:= ./libft/
LIBFT_HEADER	:= ./libft/include/

HEADER			:= ./include/
SRC_DIR			:= ./src/
OBJ_DIR			:= ./obj/

HEADER_BONUS	:= ./bonus/include/
SRC_DIR_B		:= ./bonus/src/
OBJ_DIR_B		:= ./bonus/obj/

SRC_FILES		:= test.c
OBJ_FILES		:= $(SRC_FILES:.c=.o)
SRC				:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

SRC_FILES_B		:= test.c
OBJ_FILES_B		:= $(SRC_FILES_B:.c=.o)
SRC_BONUS		:= $(addprefix $(SRC_DIR_B), $(SRC_FILES_B))
OBJ_BONUS		:= $(addprefix $(OBJ_DIR_B), $(OBJ_FILES_B))

ifdef BONUS
		INCLUDE			= $(HEADER_BONUS)
		SRC_FOLDER		= $(SRC_DIR_B)
		OBJ_FOLDER		= $(OBJ_DIR_B)
		OBJS			= $(OBJ_BONUS)
		PRINT			= BONUS
else
		INCLUDE			= $(HEADER)
		SRC_FOLDER		= $(SRC_DIR)
		OBJ_FOLDER		= $(OBJ_DIR)
		OBJS			= $(OBJ)
		PRINT			= PIPEX
endif

.PHONY	: all
all		: $(LIBFT) $(OBJ_FOLDER) $(NAME)

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) $(LIBFT_LIB) $(OBJS) -o $(NAME)
	@echo "\033[01;32m       SUCCESS!      \033[0m"

$(OBJ_FOLDER)	:
	@echo "\033[34m      $(PRINT) MAKE      \033[0m"
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir -p $(OBJ_FOLDER); \
	fi

$(OBJ_FOLDER)%.o : $(SRC_FOLDER)%.c
	@$(CC) $(CFLAGS) -I$(LIBFT_HEADER) -I$(INCLUDE) -o $@ -c $<

$(LIBFT)	:
	@make -C $(LIBFT_DIR) all

.PHONY	: bonus
bonus	:
	@make BONUS=1 all

.PHONY	: clean
clean	:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR) $(OBJ_DIR_B)
	@echo "\033[91m      REMOVE OBJECT      \033[0m"


.PHONY	: fclean
fclean	: clean
	@make -C ./libft fclean
	@$(RM) $(NAME)
	@echo "\033[91m       FCLEAN DONE      \033[0m"

.PHONY	: re
re		: fclean all
