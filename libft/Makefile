# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 00:50:10 by hmoon             #+#    #+#              #
#    Updated: 2022/04/02 03:12:33 by hmoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a
CFLAGS		:=	-Wall -Wextra -Werror

SRC_DIR		:=	./src/
OBJ_DIR		:=	./obj/
INCLUDE		:=	./include/

SRC_FILE	:=	ft_atoi.c \
			ft_bzero.c ft_calloc.c \
			ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_memccpy.c ft_memchr.c \
			ft_memcmp.c ft_memchr.c ft_memcpy.c \
			ft_memmove.c ft_memset.c \
			ft_strchr.c ft_strdup.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c \
			ft_strncmp.c ft_strnstr.c ft_strrchr.c \
			ft_tolower.c ft_toupper.c \
			ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_split.c \
			ft_itoa.c ft_strmapi.c \
			ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c ft_strcmp.c \
			ft_freearr.c get_next_line.c
OBJ_FILE	:=	$(SRC_FILE:.c=.o)
SRC			:=	$(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ			:=	$(addprefix $(OBJ_DIR), $(OBJ_FILE))

all		:	$(OBJ_DIR) $(NAME)

$(NAME) :	$(OBJ)
		@ar rcs $@ $^
		@echo "\033[36m      LIBFT DONE      \033[0m"
		@echo "----------------------"

$(OBJ_DIR)	:
		@echo "\033[35m      LIBFT MAKE      \033[0m"
		@if [ ! -d $(OBJ_DIR) ]; then \
			mkdir -p $(OBJ_DIR); \
		fi

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
		@cc $(CFLAGS) -I$(INCLUDE) -o $@ -c $<

clean	:
		@rm -rf $(OBJ_DIR)

fclean	:	clean
		@rm -rf $(NAME)

re		:	fclean all

.PHONY	:	clean fclean re all
